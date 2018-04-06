#include "Order.h"
#include "Transaction.h"
#include "Wallet.h"
#include <fstream>
#include <cmath>
#include <cstring>

using std::fstream;
using std::ios;
using std::abs;

const char *const ORDERS_FILE = "orders.dat";
static const char *const ORDERS_FILE_TMP = "ordersTmp.dat";
static const char *const TEXT_EXT = ".txt";
static const int MAX_FILE_NAME = 256;
const double EPS = 0.00001;

static OrderStatus checkFundsAvailable(const Wallet& wallet, Order::Type type, double amount);
static double onOrderAmount(unsigned walletId, Order::Type type);
static const char *generateResultFileName(unsigned walletId);
static void toString(long long int numb, char *str);
static void finishUpOrder(Wallet &current, Wallet &other, Order::Type type, double transferAmount);
static void writeToResultFile(const Wallet &wallet, const Wallet &other, Order::Type type, double amount, fstream &resultFile);
static void finishResultsFile(unsigned count, double transferred, fstream &resultFile);
static void reverse(char *beg);


OrderStatus makeOrder(Order::Type type, unsigned walletId, double amount) {
    Wallet wallet;
    wallet.id = walletId;
    if(!loadWallet(wallet)) {
        return OrderStatus::WALLET_NOT_FOUND;
    }

    OrderStatus status = checkFundsAvailable(wallet, type, amount);
    if(status != ORDER_SUCCESS) {
        return status;
    }

    fstream ordersFile;
    fstream tmpOrdersFile;
    fstream resultFile;
    ordersFile.open(ORDERS_FILE, ios::binary | ios::in);
    tmpOrdersFile.open(ORDERS_FILE_TMP, ios::binary | ios::out | ios::trunc);
    const char * resultFileName = generateResultFileName(walletId);
    resultFile.open(resultFileName, ios::out);
    delete[] resultFileName;

    if(!(ordersFile && tmpOrdersFile && resultFile)) {
        return OrderStatus::ORDER_DATABASE_ERROR;
    }

    Order tmp;
    Wallet other;
    unsigned transactionCount = 0;
    double moneyTransferred = 0;
    while(ordersFile.read((char*)&tmp, sizeof(Order))) {
        bool keepOrder = true;
        if(tmp.type != type && amount > 0) {
            other.id = tmp.walletId;
            if(!loadWallet(other)) {
                return OrderStatus::WALLET_NOT_FOUND;
            }

            keepOrder = false;

            double transferAmount = std::min(tmp.fmiCoins, amount);


            if (abs(tmp.fmiCoins - amount) < EPS) {
                amount = -1; // Just some negative value so that the other checks fail
            } else if(tmp.fmiCoins > amount) {
                tmp.fmiCoins -= amount;
                amount = -1;
                keepOrder = true;
            } else {
                amount -= tmp.fmiCoins;
            }


            finishUpOrder(wallet, other, type, transferAmount);
            writeToResultFile(wallet, other, type, transferAmount, resultFile);
            saveWallet(wallet);
            saveWallet(other);

            moneyTransferred += transferAmount * COIN_TO_MONEY_RATIO;
            transactionCount++;
        }

        if(keepOrder) {
            tmpOrdersFile.write((char*)&tmp, sizeof(Order));
        }
    }

    if(amount > 0) {
        Order newOrder;
        newOrder.type = type;
        newOrder.fmiCoins = amount;
        newOrder.walletId = walletId;
        tmpOrdersFile.write((char*)&newOrder, sizeof(Order));
    }

    ordersFile.close();
    tmpOrdersFile.close();
    finishResultsFile(transactionCount, moneyTransferred, resultFile);


    if(rename(ORDERS_FILE_TMP, ORDERS_FILE) != 0) {
        return OrderStatus::ORDER_DATABASE_ERROR;
    }

    return OrderStatus::ORDER_SUCCESS;
}

void finishResultsFile(unsigned count, double transferred, fstream &resultFile) {
    resultFile << "Transactions: " << count << "; Money transferred: " << transferred << std::endl;
}

void writeToResultFile(const Wallet &wallet, const Wallet &other, Order::Type type, double amount, fstream &resultFile) {
    const char *senderName = nullptr;
    const char *receiverName = nullptr;

    switch(type) {
        case Order::SELL:
            senderName = wallet.owner;
            receiverName = other.owner;
            break;
        case Order::BUY:
            senderName = other.owner;
            receiverName = wallet.owner;
            break;
    }

    resultFile << "Sender: " << senderName << "; Receiver: " << receiverName << "; Amount: " << amount << std::endl;
}

void finishUpOrder(Wallet &current, Wallet &other, Order::Type type, double transferAmount) {
    unsigned senderId = 0, receiverId = 0;
    double moneyTransfer = transferAmount * COIN_TO_MONEY_RATIO;

    switch(type){
        case Order::SELL:
            senderId = current.id;
            receiverId = other.id;

            current.fiatMoney += moneyTransfer;
            other.fiatMoney -= moneyTransfer;
            break;
        case Order::BUY:
            senderId = other.id;
            receiverId = current.id;

            current.fiatMoney -= moneyTransfer;
            other.fiatMoney += moneyTransfer;
            break;
    }

    makeTransaction(senderId, receiverId, transferAmount);
}

const char *generateResultFileName(unsigned walletId) {
    char* name = new char[MAX_FILE_NAME];
    toString(walletId, name);
    toString(time(nullptr), name + strlen(name));
    strcat(name, TEXT_EXT);
    return name;
}

void toString(long long numb, char *str) {
    char * beg = str;
    while(numb > 0) {
        *str = (char)(numb % 10 + '0');
        str++;
        numb /= 10;
    }

    *str = '\0';
    reverse(beg);
}

void reverse(char *beg) {
    size_t len = strlen(beg);
    for (int i = 0; i < len/2; ++i) {
        char tmp = beg[i];
        beg[i] = beg[len-i-1];
        beg[len-i-1] = tmp;
    }
}

OrderStatus checkFundsAvailable(const Wallet& wallet, Order::Type type, double amount) {
    double onOrder = onOrderAmount(wallet.id, type);
    double currency;

    switch(type) {
        case Order::SELL:
            currency = calculateCoins(wallet.id) - onOrder;
            if(currency < amount) {
                return OrderStatus::NOT_ENOUGH_COINS;
            }
            break;

        case Order::BUY:
            currency = wallet.fiatMoney - onOrder;
            if(currency < amount*COIN_TO_MONEY_RATIO) {
                return OrderStatus::NOT_ENOUGH_MONEY;
            }
            break;
    }

    return OrderStatus::ORDER_SUCCESS;
}

double onOrderAmount(unsigned walletId, Order::Type type) {
    fstream ordersFile;
    ordersFile.open(ORDERS_FILE, ios::binary | ios::in);
    if(!ordersFile) {
        return 0.0;
    }

    Order tmp;
    double amount = 0.0;
    while(ordersFile.read((char*)&tmp, sizeof(Order))) {
        if(tmp.walletId == walletId && tmp.type == type) {
            if(type == Order::BUY) {
                amount += tmp.fmiCoins * COIN_TO_MONEY_RATIO;
            } else {
                amount += tmp.fmiCoins;
            }
        }
    }

    ordersFile.close();

    return amount;
}
