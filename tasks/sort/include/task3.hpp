#include "pch.hpp"

// * TASK 3 //

// Алгоритм сортировки простыми вставками
template<typename T>
void insert_sort(T begin, T end) {
    for (auto i = begin; i != end; ++i) {
        auto temp = *i;
        auto j = i;
        while (j != begin && *(std::prev(j)) > temp) {
            *j = *(std::prev(j));
            --j;
        }
        *j = temp;
    }
}

// Получение массива шагов для шага [3h + 1] и [2h + 1]
std::vector<int> calc_steps1(int size, int(*next)(int)) {
    int current_step = 1, sup = size / 3 + 1;
    std::vector<int> steps;
    while (current_step <= sup) {
        steps.push_back(current_step);
        current_step = next(current_step);   
    }
    return steps;
}

// Получение массива шагов для шага Сейджика
std::vector<int> calc_steps2(int size) {
    int current_step = 1, count = 0, sup = size / 3 + 1;
    std::vector<int> steps;
    while (current_step <= sup) {
        steps.push_back(current_step);
        current_step = count % 2 ?
            8 * pow(2, count) - 6 * pow(2, (count + 1) / 2) + 1:
            9 * pow(2, count) - 9 * pow(2, count / 2) + 1;
        ++count;
    }
    return steps;
}

// Получение массива шагов с помощью треугольника Пратта
std::vector<int> calc_steps3(int size) {
    std::vector<int> steps;
    int max = 0, sup = size / 3 + 1, current_step = 0;
    while (pow(3, max) <= sup) ++max;
    for (int p = 0; p < max; ++p) {
        for (int q = 0; q < max; ++q) {
            current_step = pow(2, p) * pow(3, q);
            if (current_step <= sup) steps.push_back(current_step);
        }
    } 
    std::sort(steps.begin(), steps.end());
    return steps;
}

// Алгоритм Шелла с шагом [3h + 1]
template<typename T>
void shell_sort1(T begin, T end) {
    auto size = std::distance(begin, end); 
    auto steps = calc_steps1(size, [](int h){return 3 * h + 1;});
    int steps_count = steps.size();
    for (int r = steps_count - 1; r >= 0; --r) {
        for (int i = steps[r]; i < size; ++i) {
            auto temp = *(std::next(begin, i));
            int j = i - steps[r];
            while (j > -1 && *(std::next(begin, j)) > temp) {
                *(std::next(begin, j + steps[r])) = 
                    *(std::next(begin, j));
                j -= steps[r];
            }
            *(std::next(begin, j + steps[r])) = temp;
        }
    }
}

// Алгоритм Шелла с шагом [2h + 1]
template<typename T>
void shell_sort2(T begin, T end) {
    auto size = std::distance(begin, end); 
    auto steps = calc_steps1(size, [](int h){return 2 * h + 1;});
    int steps_count = steps.size();
    for (int r = steps_count - 1; r >= 0; --r) {
        for (int i = steps[r]; i < size; ++i) {
            auto temp = *(std::next(begin, i));
            int j = i - steps[r];
            while (j > -1 && *(std::next(begin, j)) > temp) {
                *(std::next(begin, j + steps[r])) = 
                    *(std::next(begin, j));
                j -= steps[r];
            }
            *(std::next(begin, j + steps[r])) = temp;
        }
    }
}

// Алгоритм Шелла с массивом шагов Седжвика
template<typename T>
void shell_sort3(T begin, T end) {
    auto size = std::distance(begin, end); 
    auto steps = calc_steps2(size);
    int steps_count = steps.size();
    for (int r = steps_count - 1; r >= 0; --r) {
        for (int i = steps[r]; i < size; ++i) {
            auto temp = *(std::next(begin, i));
            int j = i - steps[r];
            while (j > -1 && *(std::next(begin, j)) > temp) {
                *(std::next(begin, j + steps[r])) = 
                    *(std::next(begin, j));
                j -= steps[r];
            }
            *(std::next(begin, j + steps[r])) = temp;
        }
    }
}

// Алгоритм Шелла с использованием треугольника Пратта
template<typename T>
void shell_sort4(T begin, T end) {
    auto size = std::distance(begin, end); 
    auto steps = calc_steps3(size);
    int steps_count = steps.size();
    for (int r = steps_count - 1; r >= 0; --r) {
        for (int i = steps[r]; i < size; ++i) {
            auto temp = *(std::next(begin, i));
            int j = i - steps[r];
            while (j > -1 && *(std::next(begin, j)) > temp) {
                *(std::next(begin, j + steps[r])) = 
                    *(std::next(begin, j));
                j -= steps[r];
            }
            *(std::next(begin, j + steps[r])) = temp;
        }
    }
}