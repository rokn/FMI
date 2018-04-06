#ifndef FMICOIN_WALLET_H
#define FMICOIN_WALLET_H

const unsigned MAX_OWNER_NAME = 256;

struct Wallet {
    char owner[MAX_OWNER_NAME];
    unsigned id;
    double fiatMoney;
};

struct WalletCreateResult {
    enum Status {
        SUCCESS,
        EMPTY_NAME,
        INVALID_STARTING_MONEY,
        DATABASE_ERROR,
    } status;
    Wallet wallet;
};

extern const Wallet SYSTEM_WALLET;
extern const double COIN_TO_MONEY_RATIO;
extern const char *WALLETS_FILE;

WalletCreateResult createWallet(double investment, const char* name);
void printWallet(const Wallet &wallet, bool includeCoins = false);

unsigned getNewWalletId();
bool saveWallet(const Wallet& wallet, bool isNew = false);
bool loadWallet(Wallet& wallet);


#endif //FMICOIN_WALLET_H
