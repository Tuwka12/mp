#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

TEST(TestCaseName, TestName) {
	EXPECT_TRUE(get_digit('b', 7) == 1);
	EXPECT_TRUE(get_digit('b', 6) == 0);
	EXPECT_TRUE(get_digit('b', 5) == 0);
	EXPECT_TRUE(get_digit('b', 1) == 0);
}

TEST(PatriciaTreeTest, BitwiseComparasionTest) {
	EXPECT_EQ(bitwise_cmp('a', 'a'), -1);
	EXPECT_EQ(bitwise_cmp('a', 'b'), 7);
}

TEST(PatriciaTreeTest, OutputTest) {
	setlocale(LC_ALL, "ru");

	PatriciaTree tree;
	char b = 'в';
	std::string text = "выпейчаю";

	for (int i = 0; i < text.size(); ++i)
		tree.insert(text[i]);

	tree.output();
	tree.print();
}


TEST(PatriciaTreeTest, OutputTest1) {
	setlocale(LC_ALL, "ru");

	PatriciaTree tree;
	char b = 'в';
	std::string text = "абвгдеёжзиклмнопрст";

	for (int i = 0; i < text.size(); ++i)
		tree.insert(text[i]);

	//tree.output();
	tree.print();
}


TEST(PatriciaTreeTest, OutputTest2) {
	setlocale(LC_ALL, "ru");

	PatriciaTree tree;
	char b = 'в';
	std::string text = "абвгдеёжзиклмнопрст";

	for (int i = text.size() / 2; i >= 0; --i)
		tree.insert(text[i]);

	for (int i = text.size() / 2 + 1; i < text.size(); ++i)
		tree.insert(text[i]);
	

	//tree.output();
	tree.print();
}


TEST(PatriciaTreeTest, OutputTest3) {
	setlocale(LC_ALL, "ru");

	PatriciaTree tree;
	char b = 'в';
	std::string text = "abcdefghijklmnop";

	for (int i = text.size() / 2; i >= 0; --i)
		tree.insert(text[i]);

	for (int i = text.size() / 2 + 1; i < text.size(); ++i)
		tree.insert(text[i]);


	//tree.output();
	tree.print();
}


TEST(PatriciaTreeTest, OutputTest4) {
	setlocale(LC_ALL, "ru");

	PatriciaTree tree;
	char b = 'в';
	std::string text = "abcdefghijklmnop";

	for (int i = 0; i < text.size(); ++i)
		tree.insert(text[i]);


	//tree.output();
	tree.print();
}