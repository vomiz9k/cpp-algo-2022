cmake_minimum_required(VERSION 3.16)

project(exchange)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(
    exchange
    ${exchange_SOURCE_DIR}/src/trade.cpp
    ${exchange_SOURCE_DIR}/src/request.cpp
    ${exchange_SOURCE_DIR}/src/exchange.cpp
    ${exchange_SOURCE_DIR}/main.cpp
)


target_include_directories(
    exchange
    PRIVATE
    ${exchange_SOURCE_DIR}/headers
)

set_target_properties(exchange PROPERTIES OUTPUT_NAME "exchange.out")