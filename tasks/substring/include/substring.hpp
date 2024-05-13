#pragma once

#include "FunctionsApi.hpp"

template<typename T>
concept Iterable = requires(T t) {
	std::begin(t); std::end(t);
};

template<Iterable T>
void print(T container) {
	auto begin = std::begin(container), end = std::end(container);
	std::cout << '[';
	if (std::distance(begin, end)) {
		std::cout << *begin;
		for (auto it = std::next(begin); it != end; ++it)
			std::cout << ", " << *it;
	}
	std::cout << "]\n";
}

TIH_API int* pref_func(const char* F);	
TIH_API int* last_include_func(const char* F, const char* A);
TIH_API int* good_suff_func(const char* F);

TIH_API std::vector<int> simple_search(const char* T, const char* F);
TIH_API std::vector<int> RK_search(const char* T, const char* F);
TIH_API std::vector<int> KMP_search(const char* T, const char* F);
TIH_API std::vector<int> BM_search(const char* T, const char* F);