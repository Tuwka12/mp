#include "pch.hpp"

// * TASK 5 //

// Восстановление свойства кучи
template<typename T>
void heap_down(T begin, int size, int i) { 
    int j; 
    while (2 * i + 1 < size) {
        j = 2 * i + 1;
        auto child = std::next(begin, j);
        auto parent = std::next(begin, i);
        if ((j + 1) < size && *child < *std::next(child)) {
            ++child; ++j;
        }
        if (*parent < *child) {
            std::swap(*child, *parent);
            i = j;
        }
        else return;
    }
}

// Алгоритм пирамидальной сортировки
template <typename T>
void heap_sort(T begin, T end) {
    int j, size = std::distance(begin, end);
    for (j = (size - 1)/2; j >= 0; --j)
        heap_down(begin, size, j);
    while (size > 1) {
        std::swap(*begin, *std::next(begin, size - 1));
        heap_down(begin, --size, 0);
    }
}

template<typename T>
void sort_heap_wrap(T begin, T end) {
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}
