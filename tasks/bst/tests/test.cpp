#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

TEST(BstTest, CtorsTest) {
	BST<double> double_tree;
	EXPECT_TRUE(double_tree.empty());

	std::vector<int> elements = { 10, 21, 15, 7, 9, 17, 4, 2, 12, 14, 25 };
	BST<int> int_tree(elements.begin(), elements.end());
	EXPECT_FALSE(int_tree.empty());
	int_tree.output();
}

TEST(BstTest, InsertContainsRemoveTest1) {
	BST<std::string> person_tree;
	std::string name1 = "Anton";
	std::string name2 = "Andrey";
	std::string name3 = "Alex";

	EXPECT_TRUE(person_tree.insert(name1));
	EXPECT_TRUE(person_tree.contains(name1));
	EXPECT_FALSE(person_tree.contains(name2));
	EXPECT_FALSE(person_tree.remove(name2));

	EXPECT_TRUE(person_tree.insert(name2));
	EXPECT_TRUE(person_tree.contains(name2));
	EXPECT_FALSE(person_tree.contains(name3));
	EXPECT_FALSE(person_tree.remove(name3));

	EXPECT_TRUE(person_tree.insert(name3));
	EXPECT_TRUE(person_tree.remove(name1));
	EXPECT_TRUE(person_tree.remove(name2));
	EXPECT_TRUE(person_tree.remove(name3));

	EXPECT_TRUE(person_tree.empty());
}

TEST(BstTest, CopyCtorTest1) {
	std::vector<int> elements = { 10, 21, 15, 7, 9, 17, 4, 2, 12, 14, 25 };
	BST<int> int_tree(elements.begin(), elements.end());
	BST<int> copy_tree(int_tree);

	EXPECT_FALSE(copy_tree.contains(1));
	EXPECT_TRUE(copy_tree.contains(21));
	EXPECT_TRUE(copy_tree.contains(14));
}

TEST(BstTest, CopyCtorTest2) {
	std::vector<int> elements = { 1, 2, 3, 4, 5 };
	BST<int> int_tree(elements.begin(), elements.end());
	BST<int> copy_tree(int_tree);

	EXPECT_FALSE(copy_tree.contains(6));
	EXPECT_TRUE(copy_tree.contains(4));
	EXPECT_TRUE(copy_tree.contains(5));
}

TEST(BstTest, CopyCtorTestEmpty) {
	BST<int> int_tree;
	BST<int> copy_tree(int_tree);

	EXPECT_TRUE(copy_tree.empty());
}

TEST(BstTest, roundRrootLTest1) {
	std::vector<int> elements = { 1, 2, 3, 4, 5 };
	BST<int> int_tree(elements.begin(), elements.end());
	std::vector<int> values = int_tree.roundLrootR();
	for (size_t i = 0; i < elements.size(); ++i) {
		EXPECT_EQ(elements[i], values[i]);
	}
}

TEST(BstTest, roundRrootLTest2) {
	std::vector<int> elements = { 10, 21, 15, 7, 9, 17, 4, 2, 12, 14, 25 };
	BST<int> int_tree(elements.begin(), elements.end());
	std::vector<int> cmp_with = { 2, 4, 7, 9, 10, 12, 14, 15, 17, 21, 25 };
	std::vector<int> values = int_tree.roundLrootR();
	for (size_t i = 0; i < elements.size(); ++i) {
		EXPECT_EQ(cmp_with[i], values[i]);
	}
}

TEST(BstTest, roundRrootLTestEmpty) {
	BST<int> int_tree;
	EXPECT_TRUE(int_tree.roundRrootL().empty());
}

TEST(BstTest, roundLrootRTest1) {
	std::vector<int> elements = { 1, 2, 3, 4, 5 };
	BST<int> int_tree(elements.begin(), elements.end());
	std::sort(elements.begin(), elements.end());
	std::vector<int> values = int_tree.roundLrootR();
	for (size_t i = 0; i < elements.size(); ++i) {
		EXPECT_EQ(elements[i], values[i]);
	}
}

TEST(BstTest, roundLrootRTest2) {
	std::vector<int> elements = { 10, 21, 15, 7, 9, 17, 4, 2, 12, 14, 25 };
	BST<int> int_tree(elements.begin(), elements.end());
	std::vector<int> cmp_with = { 2, 4, 7, 9, 10, 12, 14, 15, 17, 21, 25 };
	std::sort(cmp_with.begin(), cmp_with.end());
	std::vector<int> values = int_tree.roundLrootR();
	for (size_t i = 0; i < elements.size(); ++i) {
		EXPECT_EQ(cmp_with[i], values[i]);
	}
}

TEST(BstTest, roundLrootRTestEmpty) {
	BST<int> int_tree;
	EXPECT_TRUE(int_tree.roundLrootR().empty());
}

TEST(BstTest, outputTest) {
	std::vector<int> elements = { 10, 21, 15, 7, 9, 17, 4, 2, 12, 14, 25 };
	BST<int> int_tree(elements.begin(), elements.end());
	int_tree.output();
}

TEST(BstTest, removeRootTest) {
	std::vector<int> elements = { 2,5,1,3,7 };
	BST<int> tree(elements.begin(), elements.end());
	tree.output();
	std::cout << "\n------------------------------------------------\n";
	tree.remove(2);
	tree.output();
}
