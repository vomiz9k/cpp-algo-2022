#include <map>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

#include <exchange.h>
#include <request.h>
#include <trade.h>

void Exchange::process(const std::string& in_filename, const std::string& out_filename, bool last_mode) {
    std::ifstream in(in_filename);
    std::unordered_map<std::string, std::deque<Request>> buy_requests;
    std::unordered_map<std::string, std::deque<Request>> sell_requests;
    std::map<std::string, std::vector<Trade>> trades;
    Request request;
    while (in >> request) {
        if (request.type == RequestType::BUY) {
            processRequest(request,
                           buy_requests[request.company],
                           sell_requests[request.company],
                           trades[request.company],
                           last_mode);
        }  else {
            processRequest(request,
                           sell_requests[request.company],
                           buy_requests[request.company],
                           trades[request.company],
                           last_mode);
        }
    }
    for (const auto& requests: {buy_requests, sell_requests}) {
        for (const auto& [company, data]: requests) {
            for (const auto& request: data) {
                trades[company].push_back(request);
            }
        }
    }
    std::ofstream out(out_filename);
    for (const auto& [company, trades_by_company] : trades) {
        for (const auto& trade: trades_by_company) {
            out << company << ' ' << trade << '\n';
        }
    }
}

void Exchange::processRequest(Request& request,
                              std::deque<Request>& same_typed_requests,
                              std::deque<Request>& another_typed_requests,
                              std::vector<Trade>& trades,
                              bool last_mode)
{
    while (!another_typed_requests.empty() && request.count > 0) {
        Request& curr = last_mode ? *another_typed_requests.rbegin() : *another_typed_requests.begin();
        int count = std::min(curr.count, request.count);
        request.count -= count;
        curr.count -= count;

        int buy_request_id = curr.id, sell_request_id = request.id;
        int buy_price = curr.price, sell_price = request.price;
        if (request.type == RequestType::BUY) {
            buy_request_id = request.id;
            buy_price = request.price;
            sell_request_id = curr.id;
            sell_price = curr.price;
        }

        trades.emplace_back(Trade(count, buy_price, buy_request_id, sell_price, sell_request_id));

        if (curr.count == 0) {
            if (last_mode) {
                another_typed_requests.pop_back();
            } else {
                another_typed_requests.pop_front();
            }
        }
    }
    if (request.count > 0) {
        same_typed_requests.emplace_back(request);
    }
}