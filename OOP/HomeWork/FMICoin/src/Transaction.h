#ifndef FMICOIN_TRANSACTION_H
#define FMICOIN_TRANSACTION_H

struct Transaction {
    long long time;
    unsigned senderId;
    unsigned receiverId;
    double fmiCoins;
};

enum TransactionStatus {
    TRANSACTION_SUCCESS,
    TRANSACTION_DATABASE_ERROR,
};

extern const char *TRANSACTIONS_FILE;

TransactionStatus makeTransaction(unsigned senderId, unsigned receiverId, double amount);
double calculateCoins(unsigned walletId);


#endif //FMICOIN_TRANSACTION_H
