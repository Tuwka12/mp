#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

int n = 4;

TEST(PermutationTest, LexPermuteTest) {
	lex_permutation(n);
}

TEST(PermutationTest, PermTranspTest) {
	transposition_permutation(n);
}