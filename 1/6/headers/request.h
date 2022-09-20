#pragma once

#include <string>

enum class RequestType {
    BUY,
    SELL
};

class Request {
    int id;
    RequestType type;
    std::string company;
    int count;
    int price;

    friend std::istream& operator>> (std::istream& in, Request& dt);
    friend class Exchange;
    friend class Trade;

public:
    Request() = default;
};