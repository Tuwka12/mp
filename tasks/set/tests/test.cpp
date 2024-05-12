#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

// CHARSET //

TEST(CharSetTests, CharSetConstructTest) {
	CharSet chs1(3);
	EXPECT_EQ(0, chs1.cardinality());
	EXPECT_EQ(3, chs1.capacity());
}

TEST(CharSetTests, CharSetAddTest) {
	CharSet chs1(5);
	chs1.add('a');
	chs1.add('b');
	chs1.add('c');
	chs1.add('d');
	chs1.add('e');
	EXPECT_EQ(5, chs1.cardinality());
	chs1.add('e');
	EXPECT_EQ(5, chs1.cardinality());
}

TEST(CharSetTests, CharSetRemoveTest) {
	CharSet chs1(5);
	chs1.add('a');
	chs1.add('b');
	chs1.add('c');
	chs1.add('d');
	chs1.add('e');
	EXPECT_EQ(5, chs1.cardinality());
	chs1.remove('a');
	chs1.remove('z');
	EXPECT_EQ(4, chs1.cardinality());
}

TEST(CharSetTests, CharSetInSetTest) {
	CharSet chs1(5);
	chs1.add('a');
	chs1.add('b');
	EXPECT_TRUE(chs1.in_set('a'));
	EXPECT_TRUE(chs1.in_set('b'));
	EXPECT_FALSE(chs1.in_set('z'));
}

TEST(CharSetTests, CharSetCopyConstructTest) {
	CharSet chs1(3);
	chs1.add('/');
	chs1.add('-');
	CharSet chs2(chs1);
	EXPECT_TRUE(chs1 == chs2);
}

TEST(CharSetTests, CharSetMoveConstructTest) {
	CharSet chs1(7);
	chs1.add('a');
	CharSet copy(chs1);
	CharSet chs2(static_cast<CharSet&&>(chs1));
	EXPECT_FALSE(chs1 == chs2);
	EXPECT_TRUE(chs2 == copy);
	EXPECT_TRUE(chs1.cardinality() == 0);
	EXPECT_FALSE(chs1.in_set('a'));
}

TEST(CharSetTests, CharSetCopyAssignmentTest) {
	CharSet chs1(7);
	CharSet chs2 = chs1;
	EXPECT_TRUE(chs1 == chs2);
}

TEST(CharSetTests, CharSetMoveAssignmentTest) {
	CharSet chs1(7);
	chs1.add('a');
	CharSet copy(chs1);
	CharSet chs2 = static_cast<CharSet&&>(chs1);
	EXPECT_FALSE(chs1 == chs2);
	EXPECT_TRUE(chs2 == copy);
	EXPECT_TRUE(chs1.cardinality() == 0);
	EXPECT_FALSE(chs1.in_set('a'));
}

TEST(CharSetTests, CharSetUnionTest) {
	CharSet chs1(5);
	for (size_t i = 0; i < 5; ++i) {
		chs1.add((char)(i + '1'));
	}
	CharSet chs2(7);
	for (size_t i = 0; i < 7; ++i) {
		chs2.add((char)(i + '4'));
	}
	CharSet chs3 = chs1 + chs2;
	EXPECT_EQ(10, chs3.cardinality());
	EXPECT_EQ(10, chs3.capacity());
	EXPECT_TRUE(chs3.in_set('1'));
	EXPECT_TRUE(chs3.in_set('3'));
	EXPECT_TRUE(chs3.in_set('5'));
	EXPECT_TRUE(chs3.in_set('9'));
}

TEST(CharSetTests, CharSetEmptyUnionTest) {
	CharSet chs1(5);
	CharSet chs2(7);
	CharSet chs3 = chs1 + chs2;
	EXPECT_EQ(0, chs3.cardinality());
	EXPECT_EQ(0, chs3.capacity());
}

TEST(CharSetTests, CharSetIntersectionTest) {
	CharSet chs1(5);
	for (size_t i = 0; i < 5; ++i) {
		chs1.add((char)(i + '1'));
	}
	CharSet chs2(7);
	for (size_t i = 0; i < 7; ++i) {
		chs2.add((char)(i + '4'));
	}
	CharSet chs3 = chs1 * chs2;
	EXPECT_EQ(2, chs3.cardinality());
	EXPECT_EQ(2, chs3.capacity());
	EXPECT_FALSE(chs3.in_set('1'));
	EXPECT_TRUE(chs3.in_set('4'));
	EXPECT_TRUE(chs3.in_set('5'));
	EXPECT_FALSE(chs3.in_set('9'));
}

TEST(CharSetTests, CharSetEmptyIntersectionTest) {
	CharSet chs1(5);
	CharSet chs2(7);
	CharSet chs3 = chs1 * chs2;
	EXPECT_EQ(0, chs3.cardinality());
	EXPECT_EQ(0, chs3.capacity());
}

TEST(CharSetTests, CharSetDifferenceTest) {
	CharSet chs1(5);
	for (size_t i = 0; i < 5; ++i) {
		chs1.add((char)(i + '1'));
	}
	CharSet chs2(7);
	for (size_t i = 0; i < 7; ++i) {
		chs2.add((char)(i + '4'));
	}
	CharSet chs3 = chs1 - chs2;
	EXPECT_EQ(3, chs3.cardinality());
	EXPECT_EQ(3, chs3.capacity());
	EXPECT_TRUE(chs3.in_set('1'));
	EXPECT_FALSE(chs3.in_set('4'));
	EXPECT_FALSE(chs3.in_set('5'));
	EXPECT_TRUE(chs3.in_set('2'));
}

TEST(CharSetTests, CharSetEmptyDifferenceTest) {
	CharSet chs1(5);
	CharSet chs2(7);
	CharSet chs3 = chs1 - chs2;
	EXPECT_EQ(0, chs3.cardinality());
	EXPECT_EQ(0, chs3.capacity());
}

TEST(CharSetTests, CharSetOutputTest) {
	CharSet chs1(10);
	for (size_t i = 0; i < 10; ++i) {
		chs1.add((char)(i + 'h'));
	}
	std::cout << chs1 << "\n" << CharSet(5) << "\n";
}

// INTSET //

TEST(IntSetTests, IntSetConstructTest) {
	IntSet is1(0, 10);
	EXPECT_EQ(0, is1.cardinality());
	EXPECT_EQ(11, is1.capacity());
}

TEST(IntSetTests, IntSetAddTest) {
	IntSet is1(5, 15);
	for (int i = 12; i < 18; ++i) {
		is1.add(i);
	}
	EXPECT_EQ(4, is1.cardinality());
}

TEST(IntSetTests, IntSetRemoveTest) {
	IntSet is1(-5, 5);
	for (int i = 0; i < 11; ++i) {
		is1.add(i - 5);
	}
	EXPECT_EQ(11, is1.cardinality());
	is1.remove(1);
	is1.remove(10);
	EXPECT_EQ(10, is1.cardinality());
}

TEST(IntSetTests, IntSetInSetTest) {
	IntSet is1(100, 110);
	is1.add(101);
	is1.add(102);
	EXPECT_TRUE(is1.in_set(101));
	EXPECT_TRUE(is1.in_set(102));
	EXPECT_FALSE(is1.in_set(103));
	EXPECT_FALSE(is1.in_set(90));
}

TEST(IntSetTests, IntSetCopyConstructTest) {
	IntSet is1(3, 7);
	is1.add(4);
	is1.add(6);
	IntSet is2(is1);
	EXPECT_TRUE(is1 == is2);
}

TEST(IntSetTests, IntSetMoveConstructTest) {
	IntSet is1(5, 15);
	is1.add(10);
	IntSet copy(is1);
	IntSet is2(static_cast<IntSet&&>(is1));
	EXPECT_FALSE(is1 == is2);
	EXPECT_TRUE(is2 == copy);
	EXPECT_TRUE(is1.cardinality() == 0);
	EXPECT_FALSE(is1.in_set(10));
}

TEST(IntSetTests, IntSetCopyAssignmentTest) {
	IntSet is1(7, 15);
	IntSet is2 = is1;
	EXPECT_TRUE(is1 == is2);
}

TEST(IntSetTests, IntSetMoveAssignmentTest) {
	IntSet is1(7, 15);
	is1.add(10);
	IntSet copy(is1);
	IntSet is2 = static_cast<IntSet&&>(is1);
	EXPECT_FALSE(is1 == is2);
	EXPECT_TRUE(is2 == copy);
	EXPECT_TRUE(is1.cardinality() == 0);
	EXPECT_FALSE(is1.in_set(10));
}

TEST(IntSetTests, IntSetUnionTest) {
	IntSet is1(0, 10);
	for (int i = 0; i < 11; ++i) {
		is1.add(i);
	}
	IntSet is2(7, 20);
	for (int i = 7; i < 21; ++i) {
		is2.add(i);
	}
	IntSet is3 = is1 + is2;
	EXPECT_EQ(21, is3.cardinality());
	EXPECT_EQ(21, is3.capacity());
	EXPECT_TRUE(is3.in_set(1));
	EXPECT_TRUE(is3.in_set(3));
	EXPECT_TRUE(is3.in_set(5));
	EXPECT_TRUE(is3.in_set(18));
}

TEST(IntSetTests, IntSetEmptyUnionTest) {
	IntSet is1(5, 10);
	IntSet is2(7, 14);
	IntSet is3 = is1 + is2;
	EXPECT_EQ(0, is3.cardinality());
	EXPECT_EQ(10, is3.capacity());
}

TEST(IntSetTests, IntSetIntersectionTest) {
	IntSet is1(0, 10);
	for (int i = 0; i < 11; ++i) {
		is1.add(i);
	}
	IntSet is2(7, 20);
	for (int i = 7; i < 21; ++i) {
		is2.add(i);
	}
	IntSet is3 = is1 * is2;
	EXPECT_EQ(4, is3.cardinality());
	EXPECT_EQ(4, is3.capacity());
	EXPECT_FALSE(is3.in_set(1));
	EXPECT_FALSE(is3.in_set(18));
	EXPECT_TRUE(is3.in_set(7));
	EXPECT_TRUE(is3.in_set(10));
}

TEST(IntSetTests, IntSetEmptyIntersectionTest) {
	IntSet is1(5, 10);
	IntSet is2(7, 14);
	IntSet is3 = is1 * is2;
	EXPECT_EQ(0, is3.cardinality());
	EXPECT_EQ(4, is3.capacity());
}

TEST(IntSetTests, IntSetDifferenceTest) {
	IntSet is1(-5, 5);
	for (int i = -5; i < 3; ++i) {
		is1.add(i);
	}
	is1.add(4);
	is1.add(5);
	IntSet is2(-3, 10);
	for (int i = -3; i < 10; ++i) {
		is2.add(i);
	}
	IntSet is3 = is1 - is2;
	EXPECT_EQ(2, is3.cardinality());
	EXPECT_TRUE(is3.in_set(-5));
	EXPECT_TRUE(is3.in_set(-4));
	EXPECT_FALSE(is3.in_set(-3));
}


TEST(IntSetTests, IntSetEmptyDifferenceTest) {
	IntSet is1(5, 10);
	IntSet is2(7, 14);
	IntSet is3 = is1 - is2;
	EXPECT_EQ(0, is3.cardinality());
	EXPECT_EQ(is1.capacity(), is3.capacity());
}

TEST(IntSetTests, IntSetOutputTest) {
	IntSet is1(-7, 7);
	for (int i = -7; i < 8; ++i) {
		is1.add(i);
	}
	std::cout << is1 << "\n" << IntSet(0, 10) << "\n";
}


//TEST(TimeExecutionTest, CharSetTest) {
//	setlocale(0, "ru");
//	CharSet chs1(256);
//	auto start = clock();
//	for (size_t i = 0; i < 256; ++i) {
//		chs1.add((char)i);
//	}
//	auto finish = clock();
//	printf("Время выполнения функции = %f секунд\n", (double)(finish - start) / CLOCKS_PER_SEC);
//}

TEST(TimeExecutionTest, IntSetTest) {
	setlocale(0, "ru");
	IntSet is1(-10000000, 10000000);
	auto start_add = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		is1.add(i);
	}
	auto finish_add = clock();
	auto start_remove = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		is1.remove(i);
	}
	auto finish_remove = clock();
	printf("(IntSet) Время выполнения функции add = %f секунд\n", 
		(double)(finish_add - start_add) / CLOCKS_PER_SEC);
	printf("(IntSet) Время выполнения функции remove = %f секунд\n",
		(double)(finish_remove - start_remove) / CLOCKS_PER_SEC);
}

TEST(TimeExecutionTest, SetTest) {
	std::set<int> st;
	auto start_add = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		st.insert(i);
	}
	auto finish_add = clock();
	auto start_remove = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		st.erase(i);
	}
	auto finish_remove = clock();
	printf("(set<int>) Время выполнения функции add = %f секунд\n", 
		(double)(finish_add - start_add) / CLOCKS_PER_SEC);
	printf("(set<int>) Время выполнения функции remove = %f секунд\n",
		(double)(finish_remove - start_remove) / CLOCKS_PER_SEC);
}

TEST(TimeExecutionTest, UnorderedSetTest) {
	std::unordered_set<int> st;
	auto start_add = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		st.insert(i);
	}
	auto finish_add = clock();
	auto start_remove = clock();
	for (int i = -10000000; i < 10000001; ++i) {
		st.erase(i);
	}
	auto finish_remove = clock();
	printf("(unordered_set<int>) Время выполнения функции add = %f секунд\n", 
		(double)(finish_add - start_add) / CLOCKS_PER_SEC);
	printf("(unordered_set<int>) Время выполнения функции remove = %f секунд\n",
		(double)(finish_remove - start_remove) / CLOCKS_PER_SEC);
}

//TEST(TimeExecutionTest, IntSetUnionTest) {
//	setlocale(0, "ru");
//	IntSet is1(-1000000, 1000000);
//	IntSet is2(-2000000, -1000000);
//	for (int i = -1000000; i < 1000001; ++i) {
//		is1.add(i);
//	}
//	for (int i = -2000000; i < -1000001; ++i) {
//		is2.add(i);
//	}
//	auto start = clock();
//	IntSet is3 = is1 + is2;
//	auto finish = clock();
//	printf("(IntSet U IntSet) Время выполнения функции = %f секунд\n", (double)(finish - start) / CLOCKS_PER_SEC);
//}
