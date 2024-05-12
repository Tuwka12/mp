#pragma once

#include "FunctionsApi.hpp"

TIH_API bool is_prime(int n);
TIH_API int next_prime(int n);

const int EMPTY = INT_MAX;
const int DEL = INT_MIN;

class LinearProbing {
public:
	LinearProbing() = default;
	LinearProbing(int capacity, int a, int b);
	int search(int value) const;
	bool insert(int value);
	bool remove(int value);
	void print() const;
	int count() const;
	const int* table() const;

protected:
	int hash(int value) const;
	void rebuild_table();

	int __capacity;
	int __count;
	int __a;
	int __b;
	int __p;
	int* __table;
};

inline LinearProbing::LinearProbing(int capacity, int a, int b)
	: __capacity(capacity), __count(0), __a(a), __b(b) {
	__table = new int[capacity] {};
	for (int i = 0; i < capacity; ++i) __table[i] = EMPTY;
	__p = next_prime(capacity);
}

inline int LinearProbing::hash(int value) const {
	return ((__a * value + __b) % __p) % __capacity;
}

inline bool LinearProbing::insert(int value) {
	if (search(value) != -1) return false;
	if ((float)__count / __capacity > 0.7) rebuild_table();
	int index = hash(value), i = 0;
	while (true) {
		int element = __table[(index + i) % __capacity];
		if (element == EMPTY || element == DEL) break;
		++i;
	}
	__table[(index + i) % __capacity] = value;
	++__count;
	return true;
}

inline int LinearProbing::search(int value) const {
	int index = hash(value);
	while (__table[index] != EMPTY) {
		if (__table[index] == value) return index;
		++index;
	}
	return -1;
}

inline void LinearProbing::print() const {
	for (int i = 0; i < __capacity; ++i) {
		std::cout << i << ")\t";
		if (__table[i] == EMPTY) std::cout << "Empty\n";
		else if (__table[i] == DEL) std::cout << "Del\n";
		else std::cout << __table[i] << "\n";
	}
}

inline int LinearProbing::count() const {
	return __count;
}

inline const int* LinearProbing::table() const {
	return __table;
}

inline void LinearProbing::rebuild_table() {
	int tmp_capacity = __capacity;
	__capacity = (int)(__capacity * 1.8); __count = 0;
	int* tmp = new int[tmp_capacity] {};
	std::copy(__table, __table + tmp_capacity, tmp);
	delete[] __table;
	__table = new int[__capacity] {};
	for (int i = 0; i < __capacity; ++i) 
		__table[i] = EMPTY;
	for (int i = 0; i < tmp_capacity; ++i) 
		if (tmp[i] != EMPTY) insert(tmp[i]);
	delete[] tmp;
}

inline bool LinearProbing::remove(int value) {
	int index = search(value);
	if (index == -1) return false;
	__table[index] = DEL;
	return true;
}


class PerfectHash {
public:
	PerfectHash(int capacity);
	bool insert(int value);
	bool remove(int value);
	std::pair<int,int> search(int value) const;
	void print() const;
private:
	int hash(int value) const;

	int* __a;
	int* __b;
	int __p;
	int __capacity;
	int __count;
	LinearProbing* __table;
};

inline PerfectHash::PerfectHash(int capacity) {
	__capacity = capacity; __count = 0; 
	__p = next_prime(capacity);

	__a = new int[capacity + 1] {};
	__b = new int[capacity + 1] {};
	for (int i = 0; i < capacity + 1; ++i) {
		__a[i] = abs(rand() % capacity);
		__b[i] = abs(rand() % capacity);
	}
	__table = new LinearProbing [capacity] {};
	for (int i = 1; i < capacity + 1; ++i)
		__table[i - 1] = LinearProbing(3, __a[i], __b[i]);
}

inline int PerfectHash::hash(int value) const {
	return ((__a[0] * value + __b[0]) % __p) % __capacity;
}

inline bool PerfectHash::insert(int value) {
	int index = hash(value);
	return __table[index].insert(value);
}

inline std::pair<int, int> PerfectHash::search(int value) const {
	int index = hash(value);
	int i = __table[index].search(value);
	return std::make_pair(index, i);
}

inline void PerfectHash::print() const {
	for (int i = 0; i < __capacity; ++i) {
		std::cout << '\n' << i 
			<< "]--------------------------------------\n";
		__table[i].print();
	}
}

inline bool PerfectHash::remove(int value) {
	return __table[hash(value)].remove(value);
}