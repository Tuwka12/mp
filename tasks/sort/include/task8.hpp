#include "pch.hpp"

// * TASK 8 //

// Получение массива очередей, хранящего указатели на слова
int** get_bounds(int size) {
    int** bounds = new int*[size];
    for (int i = 0; i < size; ++i)
        bounds[i] = new int[2]{-1,-1};
    return bounds;
}

// Создание заполненной очереди, содержщей пары со строками
template<typename T, typename It>
std::pair<T, int>* get_filled_queue(int size, It begin) {
    std::pair<T, int>* work = new std::pair<T, int>[size]{};
    for (int i = 0; i < size - 1; ++i)
        work[i] = std::make_pair(*begin++, i + 1);
    work[size - 1] = std::make_pair(*begin, -1);
    return work;
}

template<typename T>
int length(T word) {
    int length = 0;
    while (word[length] != '\0') ++length;
    return length;
}

// Один этап сортировки по отдельному символу
template<typename T>
void sort_by_symbol(int** bounds, int& begin_work, T work, int s) {
    std::set<int> filled;
    int start = begin_work;
    while (start != -1) {
        auto symbol = (work[start].first)[s], temp = work[start].second;
        filled.insert(symbol);
        if (bounds[symbol][0] == -1) bounds[symbol][0] = start;
        if (bounds[symbol][1] != -1) work[bounds[symbol][1]].second = start;
        bounds[symbol][1] = start;
        work[start].second = -1;
        start = temp;
    }
    begin_work = bounds[*(filled.begin())][0];
    auto subend = --filled.end();
    for (auto it = filled.begin(); it != subend; ++it) {
        work[bounds[*it][1]].second = bounds[*std::next(it)][0];
        bounds[*it][0] = bounds[*it][1] = -1;
    }
    bounds[*subend][0] = bounds[*subend][1] = -1;
}

// Алгоритм распределяющей сортировки для слов одинаковой длины
template<typename T>
void LSD_sort(T begin, T end) {
    using valueType = typename std::iterator_traits<T>::value_type;
    using pair = std::pair<valueType, int>;
    int word_length = length(*begin), begin_work = 0, alphabet_size = 256;
    int size = std::distance(begin, end);
    int** bounds = get_bounds(alphabet_size);
    pair* work = get_filled_queue<valueType, T>(size, begin);

    for (int s = word_length - 1; s > -1; --s)
        sort_by_symbol<pair*>(bounds, begin_work, work, s);

    while (begin_work != -1) {
        *begin++ = work[begin_work].first;
        begin_work = work[begin_work].second;
    }
}