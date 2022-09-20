#include <trade.h>
#include <ostream>

Trade::Trade(const Request& request) : count(request.count) {
    if (request.type == RequestType::BUY) {
        type = TradeType::LONG_UNCLOSED;
        buy_price = request.price;
        buy_request_id = request.id;
    } else {
        type = TradeType::SHORT_UNCLOSED;
        sell_price = request.price;
        sell_request_id = request.id;
    }
}


Trade::Trade(int count, int buy_price, int buy_request_id, int sell_price, int sell_request_id)
    : count(count), buy_price(buy_price), buy_request_id(buy_request_id),
    sell_price(sell_price), sell_request_id(sell_request_id)
{
    type = buy_request_id < sell_request_id ? TradeType::LONG : TradeType::SHORT;
}


std::ostream& operator<< (std::ostream& out, const Trade& t) {
    out << t.count << ' ';
    switch (t.type) {
        case TradeType::LONG:
            out << t.buy_price << ' ' << t.sell_price << ' '
                << ((t.sell_price - t.buy_price) * t.count)
                << " long " << t.buy_request_id << ' ' << t.sell_request_id;
            break;
        case TradeType::SHORT:
            out << t.sell_price << ' ' << t.buy_price << ' '
            << ((t.sell_price - t.buy_price) * t.count)
            << " short " << t.sell_request_id << ' ' << t.buy_request_id;
            break;
        case TradeType::LONG_UNCLOSED:
            out << t.buy_price << " - - long " << t.buy_request_id;
            break;
        case TradeType::SHORT_UNCLOSED:
            out << t.sell_price << " - - short " << t.sell_request_id;
            break;
    }

    return out;
}
