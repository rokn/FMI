
#include <iostream>
#include <fstream>
#include <cstring>

#include "System.h"
#include "Wallet.h"
#include "Order.h"
#include "Transaction.h"

using std::cin;
using std::cout;
using std::endl;

enum Command {
    ADD_WALLET = 0,
    MAKE_ORDER,
    WALLET_INFO,
    ATTRACT_INVESTORS,
    QUIT,
    UNKNOWN,
};

static const char *COMMANDS[] = {"add-wallet", "make-order", "wallet-info", "attract-investors", "quit"};
static const int COMMAND_COUNT = 5;
static const int MAX_COMMAND_LENGTH = 18;


static Command readCommand();

static Order::Type readOrderType();

static void addWallet();

static void makeOrder();

static void walletInfo();

void handleWalletCreateResult(const WalletCreateResult &result);

void initializeDatabase() {
    std::ofstream wallets(WALLETS_FILE, std::ios::app);
    std::ofstream transactions(TRANSACTIONS_FILE, std::ios::app);
    std::ofstream orders(ORDERS_FILE, std::ios::app);

    wallets.close();
    transactions.close();
    orders.close();
}

void launchProgram() {
    bool running = true;
    double amount;
    Wallet wallet;
    Order::Type type;

    while (running) {
        cout << "\nFMI_BANK> ";
        switch (readCommand()) {
            case ADD_WALLET:
                addWallet();
                break;

            case MAKE_ORDER:
                makeOrder();
                break;

            case WALLET_INFO:
                walletInfo();
                break;

            case ATTRACT_INVESTORS:
                break;

            case QUIT:
                cout << "Bye!" << endl;
                running = false;
                break;

            default:
                cout << "Unknown command" << endl;
        }
    }
}

Order::Type readOrderType() {
    char typeStr[5];
    cin >> typeStr;
    if (!strcmp(typeStr, "SELL")) {
        return Order::SELL;
    }

    return Order::BUY;
}

Command readCommand() {
    char command[MAX_COMMAND_LENGTH];
    cin >> command;

    for (int i = 0; i < COMMAND_COUNT; ++i) {
        if (!strcmp(command, COMMANDS[i])) {
            return (Command) i;
        }
    }

    return Command::UNKNOWN;
}

void addWallet() {
    double amount;
    char name[MAX_OWNER_NAME];

    cin >> amount;
    cin.ignore();
    cin.getline(name, MAX_OWNER_NAME);
    auto result = createWallet(amount, name);
    handleWalletCreateResult(result);
}

void handleWalletCreateResult(const WalletCreateResult &result) {
    switch (result.status) {
        case WalletCreateResult::SUCCESS:
            cout << "Successfully created wallet!" << endl;
            printWallet(result.wallet);
            break;
        case WalletCreateResult::EMPTY_NAME:
            cout << "Error: Empty name" << endl;
            break;
        case WalletCreateResult::INVALID_STARTING_MONEY:
            cout << "Error: Invalid starting money" << endl;
            break;
        case WalletCreateResult::DATABASE_ERROR:
            cout << "Error: Couldn't open file" << endl;
            break;
    }
}

void makeOrder() {
    Order::Type type;
    unsigned id;
    double amount;

    type = readOrderType();
    cin >> amount;
    cin >> id;
    makeOrder(type, id, amount);
}

void walletInfo() {
    Wallet wallet;
    cin >> wallet.id;
    loadWallet(wallet);
    printWallet(wallet, true);
}

void printWallets() {
    std::ifstream in;
    Wallet wallet;
    in.open("wallets.dat", std::ios_base::binary | std::ios_base::in);
    while (in.read((char *) &wallet, sizeof(Wallet))) {
        printWallet(wallet, true);
        cout << endl;
    }

    in.close();
}
