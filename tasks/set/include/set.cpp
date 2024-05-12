#include "pch.h"

#include "Functions.hpp"

// CHARSET //

CharSet::CharSet(size_t capacity) 
	: __capacity(capacity) {}

CharSet::~CharSet() {}

CharSet::CharSet(const CharSet& other) 
	: __capacity(other.__capacity), __indicator(other.__indicator) {}

CharSet::CharSet(CharSet&& other) noexcept 
	: __capacity(other.__capacity), __indicator(other.__indicator) {
	other.__capacity = 0;
	other.__indicator.reset();
}

CharSet& CharSet::operator = (const CharSet& other) {
	if (this != &other) {
		__capacity = other.__capacity;
		__indicator = other.__indicator;
	}
	return *this;
}

CharSet& CharSet::operator = (CharSet&& other) noexcept {
	if (this != &other) {
		__capacity = other.__capacity;
		__indicator = other.__indicator;

		other.__capacity = 0;
		other.__indicator.reset();
	}
	return *this;
}

void CharSet::add(char ch) {
	if (cardinality() == __capacity) return;
	__indicator[ch + OFFSET] = 1;
}

size_t CharSet::cardinality() {
	return __indicator.count();
}

size_t CharSet::capacity() {
	return __capacity;
}

bool CharSet::in_set(char ch) {
	return __indicator[ch + OFFSET] == 1;
}

void CharSet::remove(char ch) {
	__indicator[ch + OFFSET] = 0;
}

bool CharSet::operator == (const CharSet& other) {
	return __indicator == other.__indicator;
}

CharSet CharSet::operator + (const CharSet other) {
	CharSet result(*this);
	result.__indicator = __indicator | other.__indicator;
	result.__capacity = result.cardinality();
	return result;
}

CharSet CharSet::operator * (const CharSet other) {
	CharSet result(*this);
	result.__indicator = __indicator & other.__indicator;
	result.__capacity = result.cardinality();
	return result;
}

CharSet CharSet::operator - (const CharSet other) {
	CharSet result(*this);
	result.__indicator = __indicator & (__indicator ^ other.__indicator);
	result.__capacity = result.cardinality();
	return result;
}

std::ostream& operator << (std::ostream& output, const CharSet& other) {
	bool firstPrinted = false;
	output << "{";
	for (size_t i = 0; i < AMOUNT_OF_CHARS; ++i) {
		if (other.__indicator[i]) {
			if (!firstPrinted) firstPrinted = true;
			else output << ", ";
			output << (char)(i - 128);
		}
	}
	return output << "}";
}



// INTSET //

IntSet::IntSet(int left, int right) 
	: __left(left), __right(right), __cardinality(0), 
	__indicator(std::vector<bool>(right - left + 1)) {}

IntSet::~IntSet() {}

IntSet::IntSet(const IntSet& other) 
	: __left(other.__left), __right(other.__right), __cardinality(other.__cardinality),
	__indicator(other.__indicator) {}

IntSet::IntSet(IntSet&& other) noexcept
	: __left(other.__left), __right(other.__right), __cardinality(other.__cardinality),
	__indicator(other.__indicator) {
	other.__left = other.__right = other.__cardinality = 0;
	other.__indicator.clear();
}

IntSet& IntSet::operator = (const IntSet& other) {
	if (this != &other) {
		__left = other.__left;
		__right = other.__right;
		__cardinality = other.__cardinality;
		__indicator = other.__indicator;
	}
	return *this;
}

IntSet& IntSet::operator = (IntSet&& other) noexcept {
	if (this != &other) {
		__left = other.__left;
		__right = other.__right;
		__cardinality = other.__cardinality;
		__indicator = other.__indicator;

		other.__left = other.__right = other.__cardinality = 0;
		other.__indicator.clear();
	}
	return *this;
}

void IntSet::add(int number) {
	if (number < __left || number > __right) return;
	if (!__indicator[number - __left]) ++__cardinality;
	__indicator[number - __left] = true;
}

void IntSet::remove(int number) {
	if (number < __left || number > __right) return;
	if (__indicator[number - __left]) --__cardinality;
	__indicator[number - __left] = false;
}

size_t IntSet::cardinality() {
	return __cardinality;
}

size_t IntSet::capacity() {
	return __right - __left + 1;
}

bool IntSet::in_set(int number) {
	if (number < __left || number > __right) return false;
	return __indicator[number - __left] == 1;
}

bool IntSet::operator == (const IntSet& other) {
	return __indicator == other.__indicator;
}

IntSet IntSet::operator + (const IntSet other) {
	IntSet result(min(__left, other.__left), max(__right, other.__right));
	size_t this_capacity = __right - __left + 1;
	size_t other_capacity = other.__right - other.__left + 1;
	for (size_t i = 0; i < this_capacity; ++i)
		if (__indicator[i]) result.add((int)(i + __left));
	for (size_t i = 0; i < other_capacity; ++i)
		if (other.__indicator[i]) result.add((int)(i + other.__left));
	return result;
}

IntSet IntSet::operator * (const IntSet other) {
	int left_border = max(__left, other.__left);
	int right_border = min(__right, other.__right);
	if (left_border > right_border) return IntSet(0, 0);
	IntSet result(left_border, right_border);
	int count = right_border - left_border + 1;
	for (size_t i = 0; i < count; ++i)
		if (__indicator[i] == 1 && other.__indicator[i] == 1) result.add((int)(i + other.__left));
	return result;
}

IntSet IntSet::operator - (const IntSet other) {
	IntSet result(*this);
	size_t other_size = other.__right - other.__left + 1;
	for (size_t i = 0; i < other_size; ++i) {
		if (other.__indicator[i]) {
			int number = (int)(i + other.__left);
			if (in_set(number)) result.remove(number);
		}
	}
	return result;
}

std::ostream& operator << (std::ostream& output, const IntSet& other) {
	bool firstPrinted = false;
	output << "{";
	size_t capacity = other.__right - other.__left + 1;
	for (size_t i = 0; i < capacity; ++i) {
		if (other.__indicator[i]) {
			if (!firstPrinted) firstPrinted = true;
			else output << ", ";
			output << (int)(i + other.__left);
		}
	}
	return output << "}";
}
