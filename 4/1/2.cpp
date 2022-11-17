#include <string>
#include <ranges>
#include <iostream>
#include <vector>
 #include <numeric>

struct Person {
    std::string name;
    std::string surname;
};


int main() {
    std::vector<std::pair<Person, int>> v {
        {{"Imya", "Familiya"}, 1},
        {{"Name", "Surname"}, 18},
        {{"Dima", "Ivanov"}, 12},
        {{"Dmitry", "Ivanovich"}, 68}
    };

    auto age = [](const std::pair<Person, int>& p) { return p.second; };
    int cnt = 0;
    auto filter_age = [&cnt](int age) { return age >= 12 && age <= 65 ? ++cnt : false; };
    auto range = v | std::ranges::views::transform(age) | std::ranges::views::filter(filter_age);
    std::cout << ((float)std::accumulate(range.begin(), range.end(), 0)) / cnt << '\n';
}