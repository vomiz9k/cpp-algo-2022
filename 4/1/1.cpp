#include <iostream>
#include <ranges>
#include <string>
#include <string.h>

int main() {
    const auto sqr = [](int x) { return x * x; };
    const auto div5 = [](int x) { return x % 5 != 0; };
    const auto to_str = [](int x) { return std::to_string(x); };
    auto result =
        std::ranges::views::iota(10, 100)
        | std::ranges::views::transform(sqr)
        | std::ranges::views::filter(div5)
        | std::ranges::views::transform(to_str);

    for (std::string& s: result) {
        std::cout << s << '\n';
    }
}