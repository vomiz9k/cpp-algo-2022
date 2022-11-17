#include <ranges>
#include <iostream>
#include <vector>

int main() {
    auto view = std::ranges::istream_view<int>(std::cin);
    for (const auto num: view) {
        if (num == -1) {
            break;
        }
        std::cout << num << ' ';
    }
    std::cout << '\n';

    auto range2 = view
                  | std::ranges::views::take_while([](int x) { return x != -1; });
                //   | std::ranges::views::join_with(' '); C++23, enough python for today

    // std::ranges::copy(view,
    //     std::ostream_iterator<int>(std::cout, " ")); is not working too, gcc&clang
}