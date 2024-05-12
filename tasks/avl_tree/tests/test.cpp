#include "pch.h"

#include "..\Tikhonov\Functions.hpp"


const int SIZE = 5;

class AVL_TreeFixtureClass : public ::testing::Test {
protected:
    int size = SIZE;
    int* values = new int[size] {};

    void SetUp() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < size; ++i)
            values[i] = rand() % 100;
    }
    void TearDown()
    {
        delete[] values;
    }
};


TEST_F(AVL_TreeFixtureClass, InsertionTest1) {
    AVL_Tree<int> tree;
    for (int i = 0; i < size; ++i)
        tree.insert(values[i]);
    tree.output();

    tree.print_balances();
}


TEST(AVL_Tree_Test, LargeTreeTest) {
    std::vector<int> vec = { 10,15,20,25,30,17,35,37,36,34,19,18,16,9,7,8 };
    AVL_Tree<int> tree(vec.begin(), vec.end());
    tree.output();

    tree.print_balances();
}


TEST(AVL_Tree_Test, BookExampleTest) {
    std::vector<int> vec = { 10,47,65,99,82 };
    AVL_Tree<int> tree(vec.begin(), vec.end());
    tree.output();

    tree.print_balances();
}


TEST(AVL_Tree_Test, TrueRemove) {
    std::vector<int> vec = { 4,2,8,1,7,10,6 };
    AVL_Tree<int> tree(vec.begin(), vec.end());
    tree.output();
    tree.remove(2);
    tree.remove(4);
    tree.remove(1);
    tree.remove(6);
    tree.output();

    tree.print_balances();
}


TEST(AVL_Tree_TreeNode_Test, Height_Test) {
    AVL_Tree<int> tree;
    tree.insert(1);
    tree.insert(0);
    tree.insert(2);
    EXPECT_TRUE(tree.__root->height() == 1);
    EXPECT_TRUE(tree.__root->__left->height() == 0);
}


TEST(AVL_Tree_Test, SortedVectorInsertionTest) {
    std::vector<int> nums = { 1,2,3,4,5,6,7,8,9 };
    AVL_Tree<int> tree(nums.begin(), nums.end()); 
    tree.output();

    tree.print_balances();
}


TEST(AVL_Tree_Test, PrintBalancesTest) {
    std::vector<int> nums = { 1,2,3,4,5,6,7,8,9 };
    AVL_Tree<int> tree(nums.begin(), nums.end());
    tree.print_balances();
}