#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

//TEST(BTreeTest, TreeNodeCtorTest) {
//	BTree<int>::TreeNode node(3, nullptr);
//	for (int i = 0; i < 6; ++i)
//		EXPECT_TRUE(node.__ptrs[i] == nullptr);
//}
//
//TEST(BTreeTest, TreeNodeInsertTest) {
//	BTree<int>::TreeNode node(3, nullptr);
//	EXPECT_EQ(node.insert(1), 0);
//	EXPECT_EQ(node.insert(4), 1);
//	EXPECT_EQ(node.insert(2), 1);
//	EXPECT_EQ(node.insert(5), 3);
//	EXPECT_EQ(node.insert(-1), 0);
//	//node.print_values();
//}

TEST(BTreeTest, SimpleInsertTest) {
	BTree<int> tree;
	for (int i = 1; i < 11; ++i)
		tree.insert(i);
	//tree.output();
}


TEST(BTreeTest, ContainsTest) {
	BTree<int> tree;
	EXPECT_FALSE(tree.contains(1));

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

	EXPECT_TRUE(tree.contains(1));
	EXPECT_TRUE(tree.contains(2));
	EXPECT_TRUE(tree.contains(3));
	EXPECT_FALSE(tree.contains(10));

	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	//tree.output();

	EXPECT_TRUE(tree.contains(6));
	EXPECT_TRUE(tree.contains(7));
}


//TEST(BTreeTest, TreeNodeRemoveTest) {
//	BTree<int>::TreeNode node(3, nullptr);
//	node.insert(1);
//	node.insert(17);
//	node.insert(81);
//	node.insert(13);
//	node.insert(5);
//	//node.print_values();
//	node.remove(81);
//	//node.print_values();
//	node.remove(1);
//	//node.print_values();
//	node.remove(13);
//	//node.print_values();
//	EXPECT_TRUE(node.__count == 2);
//}


TEST(BTreeTest, RemoveTest) {
	BTree<int> tree;
	tree.insert(23);
	tree.insert(37);
	tree.insert(45);
	tree.insert(15);
	tree.insert(29);
	tree.insert(117);
	tree.insert(20);
	tree.insert(10);
	tree.insert(180);
	tree.insert(50);
	tree.insert(60);
	//tree.output();

	//std::cout << "\n\n";

	tree.remove(180);
	tree.remove(45);
	tree.remove(37);
	tree.insert(35);
	tree.remove(10);
	//tree.output();
	
}

TEST(BTreeTest, UniteLeftWhenRemovingTest) {
	BTree<int> tree;
	for (int i = 1; i < 13; ++i)
		tree.insert(i);
	//tree.output();
	//std::cout << "\n\n";
	//tree.remove(3);
	//tree.output();
}

TEST(BTreeTest, RemoveRootTest) {
	BTree<int> tree;
	for (int i = 1; i < 7; ++i)
		tree.insert(i * 10);
	tree.remove(60);
	//tree.output();
	tree.remove(30);
	//std::cout << "\n\n";
	tree.remove(20);
	tree.remove(10);
	tree.remove(40);
	tree.remove(50);
	//tree.output();

}

TEST(BTreeTest, LastInsertRemoveTest) {
	BTree<int> tree;
	for (int i = 0; i < 19; ++i) {
		tree.insert(i);
		tree.output();
		std::cout << "\n----------------------------------------------\n";

	}
	//tree.output();
	//std::cout << "\n----------------------------------------------\n";
	//std::vector<int> vec = { 11,12,13,0 };

	//for (int i = 0; i < vec.size(); ++i) {
	//	tree.remove(vec[i]);
	//	tree.output();
	//	std::cout << "\n----------------------------------------------\n";
	//}
	//tree.output();
}