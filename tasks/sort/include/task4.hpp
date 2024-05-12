#include "pch.hpp"

// * TASK 4 //

// Алгоритм сортировки вставками в список
template<typename T>
void insert_list_sort(T begin, T end) {
    int size = std::distance(begin, end);
    std::list<typename std::iterator_traits<T>::value_type> temp;
    for (auto it = begin; it != end; ++it) {
        bool is_inserted = false;
        auto list_end = temp.end();
        for (auto it2 = temp.begin(); it2 != list_end; ++it2) {
            if (*it < *it2) {
                temp.insert(it2, *it);
                is_inserted = true;
                break;
            }
        }
        if (!is_inserted) temp.push_back(*it);
        //temp.insert(find_position(temp.begin(), temp.end(), *it), *it);
    }
    auto list_begin = temp.begin();
    for (int i = 0; i < size; ++i) 
        *(begin++) = *(list_begin++);
}

// Алгоритм сортировки вставками в бинарное дерево поиска
template<typename T>
void insert_bst_sort(T begin, T end) {
    BST<typename std::iterator_traits<T>::value_type> tree;
    for(auto it = begin; it != end; ++it)
        tree.insert(*it);
    auto sorted_values = tree.roundLrootR();
    auto sorted_values_begin = sorted_values.begin();
    for (auto it = begin; it != end; ++it)
        *it = *(sorted_values_begin++);
}