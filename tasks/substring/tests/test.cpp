#include "pch.h"

#include "..\Tikhonov\Functions.hpp"

using unit = std::pair<const char*, const char*>;
using func = std::vector<int>(*)(const char*, const char*);

class SubstringFixture : public ::testing::TestWithParam<unit> {
protected:
	static int count;
	const char* func_names[4] = { 
		"simple_search", "RK_search", "KMP_search", "BM_search" 
	};
	func functions[4] = { 
		simple_search, RK_search, KMP_search, BM_search 
	};
public:
	void SetUp() override { ++count; }
};

int SubstringFixture::count = 0;


TEST_P(SubstringFixture, SearchTest) {
	setlocale(LC_ALL, "rus");

	auto [T, F] = GetParam();
	bool is_big = (int)(strlen(T) > 100);

	std::cout << '\n' << count << ")";
	if (!is_big) printf(" Поиск подстроки \"%s\" в строке \"%s\":\n", F, T);

	for (int i = 0; i < 4; ++i) {
		std::cout << '\n' << func_names[i] << "():\n";
		auto start = clock();
		auto res = functions[i](T, F);
		auto finish = clock();
		print(res);
		if (is_big) printf("Время поиска: %f\n", 
			(double)(finish - start) / CLOCKS_PER_SEC * 1000);
	}
}

TEST(SearchTest, PrefixFunctionTest) {
	const char* T = "абракадабра";
	auto res = pref_func(T);
	int test[11] = { 0,0,0,1,0,1,0,1,2,3,4 };
	for (int i = 0; i < (int)(strlen(T)); ++i) {
		EXPECT_EQ(res[i], test[i]);
	}
}

TEST(SearchTest, LastIncludeFunctionTest) {
	const char* A = "abcd";
	const char* T = "acbd";
	auto res = last_include_func(T, A);
	std::vector<int> test = { 0,2,1,3 };
	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(res[i], test[i]);
}

INSTANTIATE_TEST_CASE_P(
	SubstringTest,
	SubstringFixture,
	::testing::Values(
		std::make_pair("anton", "ton"),
		std::make_pair("fizika", "izi"),
		std::make_pair("abrakadabra", "ra"),
		std::make_pair("wesadrtyuikjmhgfnsadbdsadtfygnbvss", "sad"),
		std::make_pair("arestdygdsfgsfgfsdfafsfbsfarestcbdzfxcasdf", "fg"),
		std::make_pair("name name name age height name", "name"),
		std::make_pair("", "sub"),
		std::make_pair("dsfhmnvssdfcppbdnvc", "cpp"),
		std::make_pair("375447703739", "37"),
		std::make_pair("89911865667", "118"),
		std::make_pair("123123123123", "123")
	));


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}