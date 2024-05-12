#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

TEST(LinearProbingTest, InsertTest) {
	LinearProbing tbl(11, 4, 8);
	for (int i = 1; i < 9; ++i)
		tbl.insert(i);

	EXPECT_TRUE(tbl.search(8) == 4);
	EXPECT_TRUE(tbl.search(1) == 1);

	tbl.remove(4);
	EXPECT_TRUE(tbl.search(4) == -1);

	//tbl.print();
}

TEST(IsPrimeTest, Test) {
	EXPECT_TRUE(is_prime(37));
	EXPECT_TRUE(is_prime(41));
	EXPECT_TRUE(is_prime(17));
	EXPECT_TRUE(is_prime(101));
	EXPECT_FALSE(is_prime(90));
	EXPECT_FALSE(is_prime(4));
}

TEST(NextPrimeTest, Test) {
	EXPECT_EQ(17, next_prime(15));
	EXPECT_EQ(17, next_prime(13));
	EXPECT_EQ(101, next_prime(100));
	EXPECT_EQ(29, next_prime(23));
	EXPECT_EQ(23, next_prime(22));
}

TEST(PerfectHashTest, CtorTest) {
	PerfectHash tbl(5);
	for (int i = 0; i < 5; ++i)
		tbl.insert(i);

	EXPECT_EQ(3, tbl.search(1).first);
	EXPECT_EQ(1, tbl.search(1).second);

	for (int i = 15; i < 25; ++i)
		tbl.insert(i);

	tbl.remove(19);
	EXPECT_EQ(std::make_pair(4, 1), tbl.search(16));

	//tbl.print();
}