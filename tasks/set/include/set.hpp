#pragma once

#include "FunctionsApi.hpp"

const size_t AMOUNT_OF_CHARS = 256;
const size_t OFFSET = 128;

class CharSet {
private:
	size_t __capacity;
	std::bitset<AMOUNT_OF_CHARS> __indicator;
public:
	TIH_API CharSet(size_t capacity = AMOUNT_OF_CHARS);
	TIH_API ~CharSet();
	TIH_API CharSet(const CharSet& other);
	TIH_API CharSet(CharSet&& other) noexcept;
	TIH_API CharSet& operator = (const CharSet& other);
	TIH_API CharSet& operator = (CharSet&& other) noexcept;
	TIH_API void add(char ch);
	TIH_API void remove(char ch);
	TIH_API size_t cardinality();
	TIH_API size_t capacity();
	TIH_API bool in_set(char ch);
	TIH_API bool operator == (const CharSet& other);
	TIH_API CharSet operator * (const CharSet other);
	TIH_API CharSet operator + (const CharSet other);
	TIH_API CharSet operator - (const CharSet other);
	TIH_API friend std::ostream& operator << (std::ostream& output, const CharSet& other);
};

class IntSet {
private:
	int __left;
	int __right;
	int __cardinality;
	std::vector<bool> __indicator;
public:
	TIH_API IntSet(int left, int right);
	TIH_API ~IntSet();
	TIH_API IntSet(const IntSet& other);
	TIH_API IntSet(IntSet&& other) noexcept;
	TIH_API IntSet& operator = (const IntSet& other);
	TIH_API IntSet& operator = (IntSet&& other) noexcept;
	TIH_API void add(int number);
	TIH_API void remove(int number);
	TIH_API size_t cardinality();
	TIH_API size_t capacity();
	TIH_API bool in_set(int number);
	TIH_API bool operator == (const IntSet& other);
	TIH_API IntSet operator * (const IntSet other); // Точно можно лучше
	TIH_API IntSet operator + (const IntSet other); // Точно можно лучше
	TIH_API IntSet operator - (const IntSet other); // Реализовать
	TIH_API friend std::ostream& operator << (std::ostream& output, const IntSet& other);
};