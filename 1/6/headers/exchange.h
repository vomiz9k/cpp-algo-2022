#pragma once

#include <string>
#include <deque>
#include <vector>
#include <request.h>
#include <trade.h>

class Exchange {
public:
    static void process(const std::string& in_filename, const std::string& out_filename, bool last_mode);
private:
    static void processRequest(Request& request,
                               std::deque<Request>& same_typed_requests,
                               std::deque<Request>& another_typed_requests,
                               std::vector<Trade>& trades, bool last_mode);
};