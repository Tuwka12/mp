#include "pch.hpp"

// * TASK 6 //

// Алгоритм быстрой сортировки
template<typename T>
void quick_sort_recursive(T begin, T end) {
    int size = std::distance(begin, end);
    if (size < 1) return;
    std::swap(*begin, *std::next(begin, size / 2));
    int i = 1, p = size - 1;
    auto left = std::next(begin, i), right = std::prev(end);
    while (true) {
        while (i < p && *left <= *begin) {
            ++i; ++left;
        }
        while (p >= i && *right > *begin) {
            --p; --right;
        }
        if (i < p) {
            std::swap(*left++, *right--);
            ++i; --p;
        }
        else break;
    }
    std::swap(*begin, *right);
    quick_sort_recursive(begin, right);
    quick_sort_recursive(std::next(right), end);
}

// Алгоритм быстрой сортировки (нерекурсивная реализация)
template<typename T>
void quick_sort(T begin, T end) {
    std::stack<std::pair<T,T>> bounds;
    bounds.push(std::make_pair(begin, end));
    while (!bounds.empty()) {
        auto [b, e] = bounds.top();
        bounds.pop();
        int size = std::distance(b, e);
        if (size < 2) continue;
        std::swap(*b, *std::next(b, size / 2));
        int i = 1, p = size - 1;
        auto left = std::next(b, i), right = std::prev(e);
        while (true) {
            while (i < p && *left <= *b) {
                ++i; ++left;
            }
            while (p >= i && *right > *b) {
                --p; --right;
            }
            if (i < p) {
                std::swap(*left++, *right--);
                ++i; --p;
            }
            else break;
        }
        std::swap(*b, *right);
        bounds.push(std::make_pair(b, right));
        bounds.push(std::make_pair(std::next(right), e));
    }
}

// Алгоритм быстрой соритровки (голландский флаг)
template<typename T>
void holland_flag_sort(T begin, T end) {
    int size = std::distance(begin, end);
    if (size < 2) return;
    std::swap(*begin, *std::next(begin, size / 2));
    int i = 1, p = size - 1, leqv = 1, reqv = size - 1;
    auto left = std::next(begin, i), right = std::prev(end);
    while (true) {
        while (i < p && *left <= *begin) {
            if (*left == *begin)
                std::swap(*std::next(begin, leqv++), *left);
            ++i; ++left;
        }
        while (p >= i && *right >= *begin) {
            if (*right == *begin)
                std::swap(*std::next(begin, reqv--), *right);
            --p; --right;
        }
        if (i < p) {
            std::swap(*left++, *right--);
            ++i; --p;
        }
        else break;
    }
    i = 0; p = size - 1; left = std::next(right);
    auto new_begin = begin, new_end = std::prev(end);
    while (i++ < leqv) std::swap(*new_begin++, *right--);
    while (p-- > reqv) std::swap(*new_end--, *left++);
        
    holland_flag_sort(begin, std::next(right));
    holland_flag_sort(left, end);
}
