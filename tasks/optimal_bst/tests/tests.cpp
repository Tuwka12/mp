#include <gtest/gtest.h>
#include "optimal_bst.hpp"

const int SIZE = 20;

class OptimalBSTFixtureClass : public ::testing::Test {
protected:
    int size = SIZE;
    int* values = new int[size]{};
    int* weights = new int[size]{};
    int* failures = new int[size]{};

    void SetUp() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < size; ++i) {
            values[i] = rand() % 100;
            weights[i] = rand() % 100;
            failures[i] = rand() % 100;
        }
    }
    void TearDown() {
        delete[] values; delete[] weights; delete[] failures;
    }
};


TEST(OptimalBST_Test, BookExampleTest) {
    int size = 4;
    char* letters = new char[size] {'A','B','C','D'};
    int* weights = new int[size] {6,2,8,7};
    int* failures = new int[size + 1] {1,2,3,4,5};

    OptimalBST tree(letters, weights, failures, size);
    tree.output();

    EXPECT_TRUE(tree.contains('A'));
    EXPECT_FALSE(tree.contains('F'));
}


TEST(OptimalBST_Test, BookExampleTest_2) {
    int size = 4;
    char* letters = new char[size] {'A','B','C','D'};
    int* weights = new int[size] {6,2,1,7};
    int* failures = new int[size + 1] {7,2,3,4,5};

    OptimalBST tree(letters, weights, failures, size);
    tree.output();

    EXPECT_TRUE(tree.contains('A'));
    EXPECT_FALSE(tree.contains('F'));
}


TEST_F(OptimalBSTFixtureClass, roundLrootRTest) {
    OptimalBST<int> tree(values, weights, failures, size);
    auto vec = tree.roundLrootR();
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}


TEST_F(OptimalBSTFixtureClass, roundRrootLTest) {
    OptimalBST<int> tree(values, weights, failures, size);
    auto vec = tree.roundRrootL();
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end(), [](int x, int y) {
        return x > y;
    }));
}


TEST_F(OptimalBSTFixtureClass, OutputTest) {
    OptimalBST<int> tree(values, weights, failures, size);
    tree.output();
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}