#include <string>
#include <ranges>
#include <iostream>
#include <vector>
 #include <numeric>

struct Person {
    std::string name;
    std::string surname;

    friend std::ostream& operator<<(std::ostream& stream, Person person) {
        return stream << person.name << ' ' << person.surname;
    }
};

template < typename InputIter , typename OutputIter >
void myCopy ( InputIter begin , InputIter end , OutputIter target )
{
    for ( auto iter { begin }; iter != end ; ++ iter , ++ target ) { * target = * iter ; }
}


int main() {
std::vector<std::pair<Person, int>> v {
        {{"Imya", "Familiya"}, 1},
        {{"Name", "Surname"}, 18},
        {{"Dima", "Ivanov"}, 12},
        {{"Dmitry", "Ivanovich"}, 68},
        {{"djeki", "chan"}, 33},
        {{"ilon", "mask"}, 21},
        {{"Elon", "Twitterov"}, 55},
        {{"Natasha", "Romanoff"}, 120}
    };

    auto pers = [](const std::pair<Person, int>& p) { return p.first; };
    int cnt = 0;
    auto filter_age = [&cnt](int age) { return age >= 12 && age <= 65 ? ++cnt : false; };

    auto range = v | std::ranges::views::transform(pers) | std::ranges::views::take(4);
    myCopy(range.begin(), range.end(), std::ostream_iterator<Person>(std::cout, "\n"));

    auto surname = [](const Person& pers) { return pers.surname; };
    auto range2 = range | std::ranges::views::transform(surname);
    myCopy(range2.begin(), range2.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}