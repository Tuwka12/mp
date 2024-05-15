#include "pch.h"

#include "Functions.hpp"

std::vector<int> simple_search(const char* T, const char* F) {
	int n = (int)(strlen(T)), m = (int)(strlen(F));
	std::vector<int> result;
	for (int r = 0; r < n - m + 1; ++r) {
		int j = 0;
		while (j < m && F[j] == T[j + r]) ++j;
		if (j == m) result.push_back(r);
	}
	return result;
}

std::vector<int> RK_search(const char* T, const char* F) {
	std::vector<int> result;
	int q = 617, d = 256;
	int n = (int)(strlen(T)), m = (int)(strlen(F));
	int h = (long long)(pow(d, m - 1)) % q, f = 0, t = 0;

	for (int i = 0; i < m; ++i) {
		f = (d * f + F[i]) % q;
		if (f < 0) f = (f + q) % q;
		t = (d * t + T[i]) % q;
		if (t < 0) t = (t + q) % q;
	}
	for (int r = 0; r < n - m + 1; ++r) {
		if (t == f) {
			int k = 0;
			while (k < m && T[r + k] == F[k]) ++k;
			if (k == m) result.push_back(r);
		}
		t = (d * (t - T[r] * h) + T[r + m]) % q;
		if (t < 0) t = (t + q) % q;
	}
	return result;
}

int* pref_func(const char* F) {
	int m = (int)(strlen(F));
	int* prefix = new int[m] {};
	int j = 0, i = 1;
	while (i < m) {
		if (F[i] == F[j]) {
			prefix[i++] = ++j;
			continue;
		}
		if (j == 0) prefix[i++] = 0;
		else j = prefix[j - 1];
	}
	return prefix;
}

std::vector<int> KMP_search(const char* T, const char* F) {
	std::vector<int> result;
	int* prefix = pref_func(F);
	int n = (int)(strlen(T)), m = (int)(strlen(F));
	int k = 0, j = 0;
	while (k < n) {
		if (T[k] == F[j]) {
			++k; ++j;
			if (j == m) {
				result.push_back(k - m);
				j = prefix[j - 1];
			}
			continue;
		}
		if (j == 0) ++k;
		else j = prefix[j - 1];
	}
	delete[] prefix;
	return result;
}

int* last_include_func(const char* F, const char* A) {
	int m = (int)(strlen(F)), power = (int)(strlen(A));
	int* last_include = new int[power] {};
	for (int i = 1; i < m; ++i)
		last_include[F[i] - A[0]] = i;
	return last_include;
}

int* good_suff_func(const char* F) {
	int m = (int)(strlen(F)), j, size = m + 1;
	int* good_suffix = new int[size] {};
	char* rF = new char[m];
	for (int i = 0; i < m; ++i)
		rF[i] = F[m - i - 1];

	int* prefix = pref_func(F);
	int* r_prefix = pref_func(rF);

	for (int i = 0; i < size; ++i)
		good_suffix[i] = m - prefix[m - 1];

	for (int i = 1; i < size; ++i) {
		j = m - r_prefix[i - 1];
		if (good_suffix[j] > i - r_prefix[i - 1])
			good_suffix[j] = i - r_prefix[i - 1];
	}
	delete[] rF; delete[] prefix; delete[] r_prefix;
	return good_suffix;
}

std::vector<int> BM_search(const char* T, const char* F) {
	std::vector<int> result;
	char* A = new char[255]{};
	for (int i = 1; i < 256; ++i) A[i - 1] = (char)(i);
	int n = (int)(strlen(T)), m = (int)(strlen(F));
	int power = (int)(strlen(A)), r = 0, j = m;

	int* last_include = last_include_func(F, A);
	int* good_suffix = good_suff_func(F);
	
	for (; r <= n - m; j = m) {
		int j1 = m - 1;
		while (j1 >= 0 && F[j1] == T[r + j1]) {
			--j1; --j;
		}
		if (j1 == -1) {
			result.push_back(r);
			r += good_suffix[0];
		}
		else {
			int temp = good_suffix[j], index;
			for (index = 0; index < power; ++index)
				if (T[r + j - 1] == A[index]) break;
			if (good_suffix[j] < j - 1 - last_include[index])
				temp = j - 1 - last_include[index];
			r += temp;
		}
	}
	return result;
}

