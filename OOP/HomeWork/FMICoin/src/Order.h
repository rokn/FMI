#ifndef FMICOIN_ORDER_H
#define FMICOIN_ORDER_H

struct Order {
    enum Type { SELL, BUY } type;
    unsigned walletId;
    double fmiCoins;
};

extern const char *const ORDERS_FILE;

enum OrderStatus {
    ORDER_SUCCESS,
    ORDER_DATABASE_ERROR,
    NOT_ENOUGH_COINS,
    NOT_ENOUGH_MONEY,
    WALLET_NOT_FOUND,
};


OrderStatus makeOrder(Order::Type type, unsigned walletId, double amount);

#endif //FMICOIN_ORDER_H
