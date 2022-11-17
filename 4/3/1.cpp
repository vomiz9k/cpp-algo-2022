#include <concepts>
#include <string>
#include <vector>

template<typename T>
concept ConvertibleToString = requires (T t) {
    std::to_string(t);
};

template<typename T>
concept Number = std::floating_point<T> || std::integral<T>;

template<typename T, typename U>
requires (ConvertibleToString<T> && Number<T> &&
          ConvertibleToString<U> && Number<U>)
std::string concat(const T& t, const U& u) {
    return std::to_string(t) + std::to_string(u);
}
