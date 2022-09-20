#include <request.h>
#include <istream>

std::istream& operator>> (std::istream& in, Request& r)
{
    std::string type;
    in >> r.id >> type >> r.company >> r.count >> r.price;
    r.type = type == "buy" ? RequestType::BUY : RequestType::SELL;
    return in;
}