#pragma once

#include "FunctionsApi.hpp"

TIH_API void get_binary(char symbol);
TIH_API int get_digit(char symbol, int number);
TIH_API int bitwise_cmp(char left, char right);

class PatriciaTree {
protected:
	class TreeNode {
	public:
		TreeNode(char value = '\0', int d = 0);

		char __value;
		int __d;
		TreeNode* __left;
		TreeNode* __right;
	};
public:
	PatriciaTree();
	~PatriciaTree();
	bool contains(const char value) const;
	bool insert(const char value);
	void output() const;
	void print() const;
	std::vector<char> round() const;
private:
	TreeNode* get_nearest(const char value) const;
	void round_recursive(std::vector<char>& symbols, TreeNode* node, int d) const;
	void remove_recursive(TreeNode* node);
	void print_recursive(TreeNode* node, int offset) const;

	TreeNode* __root;
};

inline PatriciaTree::TreeNode::TreeNode(char value, int d)
	: __value(value), __d(d), __left(this), __right(this) {}

inline PatriciaTree::PatriciaTree() {
	__root = new TreeNode();
}

inline PatriciaTree::~PatriciaTree() {
	if (__root != __root->__left) remove_recursive(__root->__left);
	delete __root;
}

inline PatriciaTree::TreeNode* PatriciaTree::get_nearest(const char value) const {
	TreeNode* current = __root->__left;
	TreeNode* prev = __root;

	while (current->__d > prev->__d) {
		prev = current;
		if (get_digit(value, current->__d) == 0) current = current->__left;
		else current = current->__right;
	}
	return current;
}

inline bool PatriciaTree::contains(const char value) const {
	return get_nearest(value)->__value == value;
}

inline bool PatriciaTree::insert(const char value) {
	if (contains(value)) return false;
	TreeNode* current = __root->__left;
	TreeNode* prev = __root;

	int d = bitwise_cmp(get_nearest(value)->__value, value);
	while ((current->__d > prev->__d) && (current->__d < d)) {
		prev = current;
		if (get_digit(value, current->__d)) current = current->__right;
		else current = current->__left;
	}
	TreeNode* new_node = new TreeNode(value, d);
	if (prev->__left == current) prev->__left = new_node;
	else prev->__right = new_node;

	if (get_digit(value, d)) new_node->__left = current;
	else new_node->__right = current;
	return true;
}

inline void PatriciaTree::output() const {
	std::vector<char> symbols = round();
	std::cout << '[' << symbols[0];
	for (int i = 1; i < symbols.size(); ++i) 
		std::cout << ", " << symbols[i];
	std::cout << "]\n";
}

inline std::vector<char> PatriciaTree::round() const {
	std::vector<char> symbols;
	round_recursive(symbols, __root->__left, 0);
	return symbols;
}

inline void PatriciaTree::round_recursive(std::vector<char>& symbols, TreeNode* node, int d) const {
	if (node->__d <= d) {
		if (node != __root) symbols.push_back(node->__value);
		return;
	}
	round_recursive(symbols, node->__left, node->__d);
	round_recursive(symbols, node->__right, node->__d);
}

inline void PatriciaTree::remove_recursive(TreeNode* node) {
	if (node->__d < node->__left->__d) remove_recursive(node->__left);
	if (node->__d < node->__right->__d) remove_recursive(node->__right);
	delete node;
}

inline void PatriciaTree::print() const {
	return print_recursive(__root, 0);
}

inline void PatriciaTree::print_recursive(TreeNode* node, int offset) const {
	if (node->__right != node && node->__d < node->__right->__d) print_recursive(node->__right, offset + 1);
	for (int i = 0; i < offset; ++i) std::cout << '\t';
	std::cout << '[' << (char)node->__value << " - " << node->__d << "]\n";
	if (node->__left != node && node->__d < node->__left->__d) print_recursive(node->__left, offset + 1);
}