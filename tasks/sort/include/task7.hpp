#include "pch.hpp"

// * TASK 7 //

// Слияние составных частей массива для рекурсивной сортировки
template<typename T>
void merge_recursive(T begin, T middle, T end) {
    int size = std::distance(begin, end), i = 0;
    using valueType = typename std::iterator_traits<T>::value_type;
    valueType* temp = new valueType[size]{};
    auto left = begin, right = middle;
    while (left != middle && right != end) {
        if (*left < *right) temp[i++] = *left++;
        else temp[i++] = *right++;
    }
    while (left != middle) temp[i++] = *left++;
    while (right != end) temp[i++] = *right++;
    std::copy(temp, temp + size, begin);
}

// Нисходящий рекурсивный алгоритм сортировки слиянием
template<typename T>
void merge_sort_recursive(T begin, T end) {
    int size = std::distance(begin, end);
    if (size < 2) return;
    auto middle = std::next(begin, size / 2);
    merge_sort_recursive(begin, middle);
    merge_sort_recursive(middle, end);
    merge_recursive(begin, middle, end);
}

// Слияние составных частей массива заданной длины
template<typename T>
void merge(T** work, int size, int count, int length) {
    for (int i = 0; i < size; i += 2 * length) {
        int size_1 = i + length;
        int left = i, right = size_1, j = i;
        if (size_1 >= size)
            while (left < size_1)
                work[(count + 1) % 2][j++] =  work[(count % 2)][left++];              
        int size_2 = size_1 + length >= size ? size : size_1 + length;
        while (left < size_1 && right < size_2) {
            if (work[count % 2][left] < work[count % 2][right]) 
                work[(count + 1) % 2][j++] = work[(count % 2)][left++];
            else 
                work[(count + 1) % 2][j++] = work[(count % 2)][right++];
        }
        while (left < size_1)
            work[(count + 1) % 2][j++] =  work[(count % 2)][left++];
        while (right < size_2)
            work[(count + 1) % 2][j++] =  work[(count % 2)][right++];
    }
}

// Восходящий нерекурсивный алгоритм сортировки слиянием
template<typename T>
void merge_sort(T begin, T end) {
    int size = std::distance(begin, end), count = 0, length = 1;
    using valueType = typename std::iterator_traits<T>::value_type;
    valueType** work = new valueType*[2]{};
    work[0] = new valueType[size]{}; 
    work[1] = new valueType[size]{}; 
    std::copy(begin, end, work[0]);
    while (length <= size) {
        merge(work, size, count, length);
        length *= 2; ++count;
    }
    std::copy(work[count % 2], work[count % 2] + size, begin);
}
