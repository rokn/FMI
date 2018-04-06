//
// Created by rokner on 3/2/18.
//

#include "Transaction.h"
#include <fstream>
#include <ctime>

using std::ofstream;
using std::ifstream;
using std::ios;

const char *TRANSACTIONS_FILE = "transactions.dat";

TransactionStatus makeTransaction(unsigned senderId, unsigned receiverId, double amount) {
    TransactionStatus status;
    ofstream transactionsFile;
    transactionsFile.open(TRANSACTIONS_FILE, ios::binary | ios::out | ios::app);

    if(transactionsFile.is_open()) {
        Transaction transaction { time(nullptr), senderId, receiverId, amount };

        transactionsFile.write((char *)(&transaction), sizeof(Transaction));
        transactionsFile.close();
        status = TRANSACTION_SUCCESS;
    } else {
        status = TRANSACTION_DATABASE_ERROR;
    }

    return status;
}

double calculateCoins(unsigned walletId) {
    ifstream transactionsFile;
    Transaction tmp;
    double amount = 0;

    transactionsFile.open(TRANSACTIONS_FILE, ios::binary | ios::in);

    if(transactionsFile.is_open()) {
        while(transactionsFile.read((char*)&tmp, sizeof(Transaction))) {
            if(tmp.senderId == walletId) {
                amount -= tmp.fmiCoins;
            } else if (tmp.receiverId == walletId) {
                amount += tmp.fmiCoins;
            }
        }

        transactionsFile.close();
    }

    return amount;
}
