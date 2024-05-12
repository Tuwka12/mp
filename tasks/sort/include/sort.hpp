#include "pch.hpp"

// template<typename T>
// concept Iter = requires (T it) {
//     { std::next(it) } -> std::same_as<T>;
//     { std::prev(it) } -> std::same_as<T>;
// }

template<typename T>
void print_iterable(T begin, T end) {
    for (auto it = begin; it != end; ++it)
        std::cout << *it << '\t';
    std::cout << '\n';
}

std::vector<std::string> generateRandomStrings(const size_t size, const size_t length) {
    const char alphabet[] = 
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t alphabet_size = sizeof(alphabet) - 1;
    std::srand(0);
    std::vector<std::string> randomStrings(size);
    for (size_t i = 0; i < size; ++i) {
        std::string str;
        for (size_t j = 0; j < length; ++j)
            str += alphabet[std::rand() % alphabet_size];
        randomStrings[i] = str;
    }
    return randomStrings;
}