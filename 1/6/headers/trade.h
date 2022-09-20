#pragma once

#include <request.h>

enum class TradeType {
    SHORT,
    LONG,
    SHORT_UNCLOSED,
    LONG_UNCLOSED
};

class Trade {
    Trade(int count, int buy_price, int buy_request_id, int sell_price, int sell_request_id);
    Trade(const Request& request);
    int count;
    int buy_price;
    int buy_request_id;
    int sell_price;
    int sell_request_id;
    TradeType type;

    friend class Exchange;
    friend std::ostream& operator<< (std::ostream& out, const Trade& r);
};
