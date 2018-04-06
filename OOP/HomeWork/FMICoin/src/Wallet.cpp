#include "Wallet.h"
#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

const Wallet SYSTEM_WALLET{"SYSTEM", 0xffffffff, 0.};
const double COIN_TO_MONEY_RATIO = 375;
const char *WALLETS_FILE = "wallets.dat";

void printWallet(const Wallet &wallet, bool includeCoins) {
    cout.precision(2);
    cout << wallet.owner << "'s wallet:\n";
    cout << "ID: " << wallet.id << endl;
    cout << "FiatMoney: " << std::fixed << wallet.fiatMoney << endl;

    if (includeCoins) {
        cout << "Current coins: " << std::fixed << calculateCoins(wallet.id) << endl;
    }
}

WalletCreateResult createWallet(double investment, const char *name) {
    WalletCreateResult result = {WalletCreateResult::SUCCESS};

    if (!(*name)) {
        result.status = WalletCreateResult::EMPTY_NAME;
    }
    if (investment <= 0.0) {
        result.status = WalletCreateResult::INVALID_STARTING_MONEY;
    }
    if (result.status != WalletCreateResult::SUCCESS) {
        return result;
    }

    result.wallet.fiatMoney = investment;
    strcpy(result.wallet.owner, name);
    result.wallet.id = getNewWalletId();

    if (saveWallet(result.wallet, true)) {
        makeTransaction(SYSTEM_WALLET.id, result.wallet.id, investment / COIN_TO_MONEY_RATIO);
    } else {
        result.status = WalletCreateResult::DATABASE_ERROR;
    }


    return result;
}

bool saveWallet(const Wallet &wallet, bool isNew) {
    fstream walletsFile;
    walletsFile.open(WALLETS_FILE, ios::binary | ios::in | ios::out | ios::ate);

    if (walletsFile.is_open()) {
        if(!isNew) {
            walletsFile.seekp(sizeof(Wallet) * wallet.id, ios::beg);
        };

        walletsFile.write((char *) (&wallet), sizeof(Wallet));

        walletsFile.close();
        return true;
    }

    return false;
}

bool loadWallet(Wallet &wallet) {
    ifstream walletsFile;
    Wallet tmp;
    bool found = false;

    walletsFile.open(WALLETS_FILE, ios::binary | ios::in);

    if (walletsFile.is_open()) {
        while (walletsFile.read((char *) &tmp, sizeof(Wallet)) && !found) {
            if (tmp.id == wallet.id) {
                wallet = tmp;
                found = true;
            }
        }

        walletsFile.close();
    }
    return found;
}

unsigned getNewWalletId() {
    ifstream walletsFile;
    Wallet tmp;
    unsigned id = 0;

    walletsFile.open(WALLETS_FILE, ios::binary | ios::in);
    if (walletsFile.is_open()) {
        walletsFile.seekg(0, ios::end);
        if (!walletsFile.tellg()) { // check for empty
            return 1;
        }

        walletsFile.seekg(-sizeof(Wallet), ios::cur);
        walletsFile.read((char *) &tmp, sizeof(Wallet));
        id = tmp.id + 1;

        walletsFile.close();
    }

    return id;
}



