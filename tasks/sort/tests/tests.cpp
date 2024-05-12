#include <gtest/gtest.h>
#include "../include/sort.hpp"
#include "../include/task3.hpp"
#include "../include/task4.hpp"
#include "../include/task5.hpp"
#include "../include/task6.hpp"
#include "../include/task7.hpp"
#include "../include/task8.hpp"

template<typename T>
using sortingFunction = void(*)(T*, T*);

template<typename T>
using paramData = std::pair<sortingFunction<T>, std::string>;
const int SIZE = 10000;


class SortFixture : public ::testing::TestWithParam<paramData<int>> {
protected:
    static int count;
    int size = SIZE;
    int* unsorted_arr = new int[SIZE]{};
    int* descending_arr = new int[SIZE]{};
    int* ascending_arr = new int[SIZE]{};
    int* repeats_arr = new int[SIZE]{};
    const char** arr_names = new const char*[4] {
        "Неупорядоченный массив", 
        "Массив в порядке убывания", 
        "Массив в порядке возрастания", 
        "Большое количество повторов"
    }; 
public:
    void SetUp() override {
        srand(1); ++count;
        for (size_t i = 0; i < size; ++i) {
            unsorted_arr[i] = rand() % size;
            descending_arr[i] = size - i;
            ascending_arr[i] = i;
            repeats_arr[i] = rand() % (int)(size / 100);
        }
    }
    void TearDown() override {
        delete[] unsorted_arr;
        delete[] descending_arr;
        delete[] ascending_arr;
        delete[] repeats_arr;
    }
};

int SortFixture::count = 0;

TEST_P(SortFixture, IntType) {
    auto paramData = GetParam();
    auto sortFunction = paramData.first;
    std::cout << '\n' << count <<". Тестирование функции " << paramData.second << ":\n\n";

    int* arrays[] = { unsorted_arr, descending_arr, ascending_arr, repeats_arr };
    for (size_t i = 0; i < 4; ++i) {
        int* arr = arrays[i];

        auto start = clock();
        sortFunction(arr, arr + size);
        auto finish = clock();

        EXPECT_TRUE(std::is_sorted(arr, arr + size));
        printf("%s --> Время сортировки: %f ms\n", arr_names[i] ,
            (double)(finish - start) / CLOCKS_PER_SEC * 1000);
    }
    std::cout << std::endl;
};

INSTANTIATE_TEST_SUITE_P(
    SortTest,
    SortFixture,
    ::testing::Values(
        std::make_pair(insert_sort<int*>, 
            "Алгоритм сортировки простыми вставками"),
        std::make_pair(shell_sort1<int*>, 
            "Алгоритм Шелла с шагом [3h + 1]"),
        std::make_pair(shell_sort2<int*>, 
            "Алгоритм Шелла с шагом [2h + 1]"),
        // std::make_pair(shell_sort3<int*>, 
        //     "Алгоритм Шелла с массивом шагов Седжвика"),
        // std::make_pair(shell_sort4<int*>, 
        //     "Алгоритм Шелла с использованием треугольника Пратта"),
        // std::make_pair(insert_list_sort<int*>,
        //     "Алгоритм сортировки вставками в список"),
        // std::make_pair(insert_bst_sort<int*>,
        //     "Алгоритм сортировки вставками в бинарное дерево поиска"),
        std::make_pair(heap_sort<int*>,
            "Алгоритм пирамидальной сортировки"),
        std::make_pair(holland_flag_sort<int*>, 
            "Алгоритм быстрой сортировки (задача голландского флага)"),
        std::make_pair(quick_sort_recursive<int*>,
            "Алгоритм быстрой сортировки (рекурсивная реализация)"),
        std::make_pair(quick_sort<int*>,
            "Алгоритм быстрой сортировки (нерекурсивная реализация)"),
        std::make_pair(merge_sort<int*>,
            "Восходящий нерекурсивный алгоритм сортировки слиянием"),
        std::make_pair(merge_sort_recursive<int*>,
            "Нисходящий рекурсивный алгоритм сортировки слиянием"),
        // std::make_pair(sort_heap_wrap<int*>, 
        //     "std::sort_heap"),
        // std::make_pair(std::stable_sort<int*>,
        //     "std::stable_sort"),
        std::make_pair(std::sort<int*>, 
            "std::sort")
    )
);

TEST(SortTest, LSDsort) {
    auto text = generateRandomStrings(10000, 10);
    auto start = clock();
    LSD_sort(text.begin(), text.end());
    auto finish = clock();
    EXPECT_TRUE(std::is_sorted(text.begin(), text.end()));
    printf("\n%s --> Время сортировки: %f ms\n\n", "LSD_sort",
        (double)(finish - start) / CLOCKS_PER_SEC * 1000);
}

TEST(SortTest, qsort) {
    auto text = generateRandomStrings(10000, 10);
    auto start = clock();
    quick_sort_recursive(text.begin(), text.end());
    auto finish = clock();
    EXPECT_TRUE(std::is_sorted(text.begin(), text.end()));
    printf("\n%s --> Время сортировки: %f ms\n\n", "quick_sort_recursive",
        (double)(finish - start) / CLOCKS_PER_SEC * 1000);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}