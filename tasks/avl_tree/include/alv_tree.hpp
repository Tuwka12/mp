#pragma once

#include "FunctionsApi.hpp"

TIH_API int a(int a);

template<typename T>
class AVL_Tree {
private:
	class TreeNode {
	public:
		TreeNode(const T& value);
		int height() const;

		T __value;
		TreeNode* __left;
		TreeNode* __right;
		int __balance;
	};

public:

	AVL_Tree() : __root(nullptr) {};
	template<typename Iter>
	AVL_Tree(Iter begin, Iter end);
	~AVL_Tree();

	const TreeNode* find(const T& value) const;
	bool insert(const T& value);
	bool remove(const T& value);
	bool contains(const T& value);
	void output() const;
	void print_balances();

	std::vector<T> roundLrootR();
	std::vector<T> roundRrootL();

	TreeNode* __root;
private:

	void roundLeft(TreeNode*& current);
	void roundRight(TreeNode*& current);
	void update_balance(TreeNode*& node);
	void delete_node(TreeNode*& node, bool& was_found, bool& stop);
	void clear(TreeNode*& node);
	void insert_recursive(const T& value, TreeNode*& node, bool& was_rotated);
	void remove_recursive(const T& value, TreeNode*& node, bool& was_found, bool& stop);
	void print_subtree(TreeNode* node, size_t offset = 0) const;
	std::vector<T> subTreeRoundRrootL(TreeNode* node);
};


template <typename T>
AVL_Tree<T>::TreeNode::TreeNode(const T& value)
	: __value(value), __left(nullptr), __right(nullptr), __balance(0) {}


template<typename T>
inline int AVL_Tree<T>::TreeNode::height() const {
	if (!this) return -1;
	int left = this->__left->height(), right = this->__right->height();
	return 1 + (left > right ? left : right);
}


template<typename T>
template<typename Iter>
inline AVL_Tree<T>::AVL_Tree(Iter begin, Iter end) : __root(nullptr) {
	for (auto it = begin; it != end; ++it)
		insert(*it);
}


template <typename T>
inline AVL_Tree<T>::~AVL_Tree() {
	clear(__root);
}


template <typename T>
inline void AVL_Tree<T>::clear(TreeNode*& node) {
	if (node) {
		clear(node->__left);
		clear(node->__right);
	}
	delete node;
}


template<typename T>
inline void AVL_Tree<T>::print_balances() {
	for (auto& elem : roundLrootR()) {
		auto node = find(elem);
		std::cout << node->__balance << " ->\t" << node->__value << '\n';
	}
}

template<typename T>
inline void AVL_Tree<T>::roundLeft(TreeNode*& current) {
	auto temp = current;
	current = current->__right;
	temp->__right = nullptr;
	if (current->__left) temp->__right = current->__left;
	current->__left = temp;
}


template<typename T>
inline void AVL_Tree<T>::roundRight(TreeNode*& current) {
	auto temp = current;
	current = current->__left;
	temp->__left = nullptr;
	if (current->__right) temp->__left = current->__right;
	current->__right = temp;
}


template <typename T>
inline bool AVL_Tree<T>::insert(const T& value) {
	bool was_rotated = false;
	insert_recursive(value, __root, was_rotated);
	return true;
}


template <typename T>
inline void AVL_Tree<T>::insert_recursive(const T& value, TreeNode*& node, bool& was_rotated) {
	if (!node) node = new TreeNode(value);
	else {
		insert_recursive(value, value < node->__value ? node->__left : node->__right, was_rotated);
		if (was_rotated) return; // !!!
		if (node->__balance == 0) node->__balance = value < node->__value ? 1 : -1;
		else if ((node->__balance == 1 && value > node->__value)
			|| (node->__balance == -1 && value < node->__value))
		{
			node->__balance = 0; was_rotated = true;
		}
		else {
			if (node->__balance == 1 && value < node->__value) {
				if (value < node->__left->__value) roundRight(node);
				else { roundLeft(node->__left); roundRight(node); }
			}
			else if (node->__balance == -1 && value > node->__value) {
				if (value >= node->__right->__value) roundLeft(node);
				else { roundRight(node->__right); roundLeft(node); }
			}
			update_balance(node);
			was_rotated = true;
		}
	}
}


template<typename T>
inline bool AVL_Tree<T>::remove(const T& value) {
	bool was_found = false, stop = false;
	remove_recursive(value, __root, was_found, stop);
	return was_found;
}


template<typename T>
inline void AVL_Tree<T>::delete_node(TreeNode*& node, bool& was_found, bool& stop) {
	if (!node->__left && !node->__right) {
		delete node;
		node = nullptr;
	}
	else if (node->__left && !node->__right) {
		auto temp = node->__left;
		delete node;
		node = temp;
	}
	else if (!node->__left && node->__right) {
		auto temp = node->__right;
		delete node;
		node = temp;
	}
	else {
		auto current = node->__right;
		while (current->__left) current = current->__left;
		auto temp_value = current->__value;
		remove_recursive(temp_value, node->__right, was_found, stop);
		node->__value = temp_value;
	}
	was_found = true;
}


template<typename T>
inline void AVL_Tree<T>::remove_recursive(const T& value, TreeNode*& node, bool& was_found, bool& stop) {
	if (!node) return;
	if (node->__value == value) delete_node(node, was_found, stop);
	else node->__value > value ? remove_recursive(value, node->__left, was_found, stop) :
		remove_recursive(value, node->__right, was_found, stop);
	if (!was_found || !node || stop) return;
	if (node->__balance == 0)
		node->__balance = node->__left->height() - node->__right->height();
	else if ((node->__balance == -1 && value >= node->__value)
		|| (node->__balance == 1 && value < node->__value))
		node->__balance = 0;
	else if ((node->__balance == -1 && value < node->__value)
		|| (node->__balance == 1 && value >= node->__value)) {
		if (node->__right->height() > node->__left->height()) {
			if (node->__right->__balance == 0) { roundLeft(node); stop = true; }
			else if (node->__right->__balance == -1) roundLeft(node);
			else { roundRight(node->__right); roundLeft(node); }
		}
		else {
			if (node->__left->__balance == 0) { roundRight(node); stop = true; }
			else if (node->__left->__balance == -1) roundRight(node);
			else { roundLeft(node->__right); roundRight(node); }
		}
		if (!stop) update_balance(node);
	}
}


template <typename T>
inline void AVL_Tree<T>::output() const {
	print_subtree(__root);
	std::cout << "------------------------------------\n";
}


template <typename T>
inline void AVL_Tree<T>::print_subtree(TreeNode* node, size_t offset) const {
	if (!node) return;
	if (node->__right) print_subtree(node->__right, offset + 1);
	for (size_t i = 0; i < offset; ++i) std::cout << "   ";
	std::cout << node->__value << "\n";
	if (node->__left) print_subtree(node->__left, offset + 1);
}


template<typename T>
inline const typename AVL_Tree<T>::TreeNode* AVL_Tree<T>::find(const T& value) const {
	TreeNode* current = __root;
	while (current) {
		if (value == current->__value) return current;
		current = value < current->__value ? current->__left : current->__right;
	}
	return nullptr;
}


template <typename T>
inline bool AVL_Tree<T>::contains(const T& value) {
	return find(value) != nullptr;
}


template <typename T>
inline std::vector<T> AVL_Tree<T>::roundRrootL() {
	return subTreeRoundRrootL(__root);
}


template <typename T>
inline std::vector<T> AVL_Tree<T>::roundLrootR() {
	std::vector<T> result = subTreeRoundRrootL(__root);
	std::reverse(result.begin(), result.end());
	return result;
}


template <typename T>
inline std::vector<T> vector_merge(std::vector<T> left, std::vector<T> right) {
	size_t count = right.size();
	for (size_t i = 0; i < count; ++i) left.push_back(right[i]);
	return left;
}


template <typename T>
inline std::vector<T> AVL_Tree<T>::subTreeRoundRrootL(TreeNode* node) {
	if (!node) return std::vector<T>();
	std::vector<T> result;
	if (node->__right)
		result = vector_merge(result, subTreeRoundRrootL(node->__right));
	result.push_back(node->__value);
	if (node->__left)
		result = vector_merge(result, subTreeRoundRrootL(node->__left));
	return result;
}


template<typename T>
inline void AVL_Tree<T>::update_balance(TreeNode*& node) {
	if (!node) return;
	node->__balance = node->__left->height() - node->__right->height();
	node->__left->__balance = node->__left->__left->height() - node->__left->__right->height();
	node->__right->__balance = node->__right->__left->height() - node->__right->__right->height();
}
