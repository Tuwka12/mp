#include "pch.h"

#include "Functions.hpp"

void lex_permutation(int n) {
	int i, j, left, right;
	int* perm = new int[n];
	for (j = 0; j < n; ++j) perm[j] = j + 1;

	while (true) {
		for (i = 0; i < n; ++i) std::cout << perm[i] << ' ';
		std::cout << std::endl;

		for (i = n - 2; i > -1 && perm[i] > perm[i + 1]; --i);
		if (i == -1) break;
		for (j = n - 1; perm[i] > perm[j]; --j);
		std::swap(perm[i], perm[j]);

		left = i + 1;
		right = n - 1;
		while (right > left)
			std::swap(perm[right--], perm[left++]);
	}
	delete[] perm;
}

void transposition_permutation(int n) {
	int i, m;
	int* perm = new int[n + 2] {};
	int* iperm = new int[n + 2] {};
	int* d = new int[n + 1] {};
	perm[0] = n + 1;
	perm[n + 1] = n + 1;
	m = n + 1;

	for (i = 1; i < n + 1; ++i) {
		perm[i] = iperm[i] = i;
		d[i] = -1;
	}
	d[1] = 0;
	do {
		for (i = 1; i < n + 1; ++i) std::cout << perm[i] << ' ';
		std::cout << std::endl;
		m = n;
		while (perm[iperm[m] + d[m]] > m) d[m--] = -d[m];
		std::swap(perm[iperm[m] + d[m]], perm[iperm[m]]);
		std::swap(iperm[perm[iperm[m]]], iperm[m]);
	} while (m > 1);

	delete[] perm; delete[] iperm; delete[] d;
}