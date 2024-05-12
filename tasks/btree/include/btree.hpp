#pragma once

#include "FunctionsApi.hpp"

TIH_API int a(int a);

template<typename T>
class BTree {

protected:

	class TreeNode {
	public:
		TreeNode(int t, TreeNode* parent);
		int insert(const T& value);
		void print_values() const;
		int find_index(const T& value);
		void remove(const T& value);

		int __count;
		bool __is_leaf;
		TreeNode* __parent;
		T* __values;
		TreeNode** __ptrs;
	};

public:

	BTree(int t = 3);
	~BTree();
	bool insert(const T& value);
	bool contains(const T& value);
	void remove(const T& value);
	void output();


private:

	bool insert_recursive(const T& value, TreeNode*& node);
	void split_node(TreeNode* node, bool left);
	void split_root();
	void split_left(TreeNode*& node, TreeNode* second, int index);
	void split_right(TreeNode*& node, TreeNode* second, int index);
	void print_recursive(TreeNode* node, int level);
	bool contains_recursive(const T& value, TreeNode* node);
	void remove_recursive(const T& value, TreeNode*& node);
	void move_key_to(TreeNode*& node, TreeNode*& brother, bool left);
	void unite(TreeNode*& node, TreeNode*& brother, bool left);

	int __t;
	TreeNode* __root;
};


template<typename T>
inline BTree<T>::TreeNode::TreeNode(int t, TreeNode* parent) 
	: __count(0), __is_leaf(true), __parent(parent)
{
	int capacity = 2 * t - 1;
	__values = new T [capacity] {};
	__ptrs = new TreeNode * [capacity + 1] {};
}


template<typename T>
inline int BTree<T>::TreeNode::insert(const T& value) {
	int i = find_index(value);
	for (int j = __count - 1; j >= i; --j) __values[j + 1] = __values[j];
	__values[i] = value; ++__count;
	return i;
}


template<typename T>
inline void BTree<T>::TreeNode::remove(const T& value) {
	int i = find_index(value);
	__values[i] = 0; __count--;
	while (i < __count) {
		std::swap(__values[i], __values[i + 1]); ++i;
	}
}


template<typename T>
inline void BTree<T>::TreeNode::print_values() const {
	for (int i = 0; i < __count; ++i)
		std::cout << __values[i] << '\t';
	std::cout << '\n';
}


template<typename T>
inline int BTree<T>::TreeNode::find_index(const T& value) {
	int i = 0;
	while (i < __count && value > __values[i]) ++i;
	return i;
}


template<typename T>
inline BTree<T>::BTree(int t) : __t(t), __root(nullptr) {}


template<typename T>
inline BTree<T>::~BTree() {}


template<typename T>
inline bool BTree<T>::insert_recursive(const T& value, TreeNode*& node) {
	if (node == nullptr) node = new TreeNode(__t, nullptr);
	if (node->__count >= __t * 2 - 1) {
		split_node(node, value < node->__values[__t - 1]);
		if (value >= node->__values[__t - 1] && node != __root)
			return insert_recursive(
				value, node->__parent->__ptrs[node->__parent->find_index(value)]);
	}
	if (node->__is_leaf) node->insert(value);
	else return insert_recursive(value, node->__ptrs[node->find_index(value)]);
	return true;
}


template<typename T>
inline bool BTree<T>::insert(const T& value) {
	return insert_recursive(value, __root);
}


template<typename T>
inline bool BTree<T>::contains_recursive(const T& value, TreeNode* node) {
	if (!node) return false;
	for (int i = 0; i < node->__count; ++i)
		if (value == node->__values[i]) return true;
	return contains_recursive(value, node->__ptrs[node->find_index(value)]);
}


template<typename T>
inline bool BTree<T>::contains(const T& value) {
	return contains_recursive(value, __root);
}


template<typename T>
inline void BTree<T>::remove_recursive(const T& value, TreeNode*& node) {
	if (!node) return;
	int i = node->find_index(value);
	if (node->__values[i] == value) {
		if (node->__is_leaf && node->__count >= __t) node->remove(value);
		else if (!node->__is_leaf) {
			if ((i != 0 && node->__ptrs[i - 1]->__count < __t && node->__ptrs[i]->__count < __t)
				|| (i != node->__count && node->__ptrs[i + 1]->__count < __t && node->__ptrs[i]->__count < __t)) {
				unite(node->__ptrs[i], node->__ptrs[i + 1], false);
				if (node == __root && node->__count < 2) {
					__root = node->__ptrs[i];
					__root->__is_leaf = true;
					delete node->__ptrs[i];
					delete node->__ptrs[i + 1];
					return remove_recursive(value, __root);
				} 
				else return remove_recursive(value, node->__ptrs[i]);
			}
		} 
		else node->remove(value);
	}
	else if (!node->__is_leaf && node->__ptrs[i] != nullptr) {
		if (node->__ptrs[i]->__count >= __t)
			return remove_recursive(value, node->__ptrs[i]);
		else if (i != 0 && node->__ptrs[i - 1]->__count >= __t)
			move_key_to(node->__ptrs[i], node->__ptrs[i - 1], true);
		else if (i != node->__count && node->__ptrs[i + 1]->__count >= __t)
			move_key_to(node->__ptrs[i], node->__ptrs[i + 1], false);
		else if (i != 0 && node->__ptrs[i - 1]->__count < __t)
			unite(node->__ptrs[i], node->__ptrs[(i--) - 1], true);
		else if (i != node->__count && node->__ptrs[i + 1]->__count < __t)
			unite(node->__ptrs[i], node->__ptrs[i + 1], false);
		return remove_recursive(value, node->__ptrs[i]);
	}
	else return;
}


template<typename T>
inline void BTree<T>::remove(const T& value) {
	return remove_recursive(value, __root);
}


template<typename T>
inline void BTree<T>::print_recursive(TreeNode* node, int level) {
	if (node == nullptr) return;
	std::cout << "\nLevel: " << level << '\n';
	for (int i = 0; i < node->__count; ++i)
		std::cout << node->__values[i] << '\t';
	std::cout << '\n';
	for (int i = 0; i < node->__count + 1; ++i)
		print_recursive(node->__ptrs[i], level + 1);
}


template<typename T>
inline void BTree<T>::output() {
	if (__root->__count) print_recursive(__root, 0);
}


template<typename T>
inline void BTree<T>::move_key_to(TreeNode*& node, TreeNode*& brother, bool left) {
	auto& par = node->__parent;
	int index = left ? par->find_index(node->__values[0]) - 1
		: par->find_index(node->__values[node->__count - 1]);
	node->insert(par->__values[index]);
	if (left) {
		for (int i = node->__count + 1; i > 0; --i)
			node->__ptrs[i] = node->__ptrs[i - 1];
		node->__ptrs[0] = brother->__ptrs[brother->__count];
		brother->__ptrs[brother->__count] = nullptr;
	}
	else {
		node->__ptrs[node->__count] = brother->__ptrs[0];
		for (int i = 0; i < brother->__count + 1; ++i)
			brother->__ptrs[i] = brother->__ptrs[i + 1];
	}
	auto elem = brother->__values[left ? brother->__count - 1 : 0];
	par->__values[index] = elem;
	brother->remove(elem);
}


template<typename T>
inline void BTree<T>::split_node(TreeNode* node, bool left) {
	if (node == __root) split_root();
	else {
		int index = node->__parent->insert(node->__values[__t - 1]);
		for (int i = 2 * __t - 1; i > index; --i)
			node->__parent->__ptrs[i] = node->__parent->__ptrs[i - 1];

		TreeNode* second_node = new TreeNode(__t, node->__parent);
		second_node->__is_leaf = node->__is_leaf;

		if (left) split_left(node, second_node, index);
		else split_right(node, second_node, index);
	}
	return;
}


template<typename T>
inline void BTree<T>::split_left(TreeNode*& node, TreeNode* second_node, int index) {
	for (int i = __t; i < 2 * __t - 1; ++i) {
		second_node->insert(node->__values[i]);
		node->__values[i] = 0;
		node->__count--;
		if (!node->__is_leaf) {
			second_node->__ptrs[i - __t] = node->__ptrs[i];
			second_node->__ptrs[i - __t]->__parent = second_node;
		}
		node->__ptrs[i] = nullptr;
	}
	node->__values[__t - 1] = 0; node->__count--;
	if (!node->__is_leaf) {
		second_node->__ptrs[2 * __t - 1] = node->__ptrs[2 * __t - 1];
		second_node->__ptrs[2 * __t - 1]->__parent = second_node;
	}
	node->__ptrs[2 * __t - 1] = nullptr;
	node->__parent->__ptrs[index] = node;
	node->__parent->__ptrs[index + 1] = second_node;
}


template<typename T>
inline void BTree<T>::split_right(TreeNode*& node, TreeNode* second_node, int index) {
	for (int i = 0; i < __t - 1; ++i) {
		second_node->insert(node->__values[i]);
		node->__values[i] = node->__values[__t + i];
		node->__values[__t + i] = 0; node->__count--;
		if (!node->__is_leaf) {
			second_node->__ptrs[i] = node->__ptrs[i];
			second_node->__ptrs[i]->__parent = second_node;
			node->__ptrs[i] = node->__ptrs[__t + i];
		}
		node->__ptrs[__t + i] = nullptr;
	}
	node->__values[__t - 1] = 0; node->__count--;
	if (!node->__is_leaf) {
		second_node->__ptrs[__t - 1] = node->__ptrs[__t - 1];
		second_node->__ptrs[__t - 1]->__parent = second_node;
		node->__ptrs[__t - 1] = node->__ptrs[2 * __t - 1];
	}
	node->__ptrs[2 * __t - 1] = nullptr;
	node->__parent->__ptrs[index] = second_node;
	node->__parent->__ptrs[index + 1] = node;
}


template<typename T>
inline void BTree<T>::split_root() {
	TreeNode* left_node = new TreeNode(__t, __root);
	TreeNode* right_node = new TreeNode(__t, __root);

	if (!__root->__is_leaf) left_node->__is_leaf = right_node->__is_leaf = false;
	for (int i = 0; i < __t - 1; ++i) {
		left_node->insert(__root->__values[i]);
		left_node->__ptrs[i] = __root->__ptrs[i];
		right_node->insert(__root->__values[__t + i]);
		right_node->__ptrs[i] = __root->__ptrs[__t + i];
	}
	left_node->__ptrs[__t - 1] = __root->__ptrs[__t - 1];
	right_node->__ptrs[__t - 1] = __root->__ptrs[2 * __t - 1];

	__root->__is_leaf = false;
	__root->__values[0] = __root->__values[__t - 1];
	for (int i = 1; i < 2 * __t; ++i) {
		__root->__values[i] = 0;
		__root->__ptrs[i] = nullptr;
	}
	__root->__ptrs[0] = left_node; __root->__ptrs[1] = right_node;
	__root->__count = 1;
}


template<typename T>
inline void BTree<T>::unite(TreeNode*& node, TreeNode*& brother, bool left) {
	auto& par = node->__parent;
	int index = par->find_index(node->__values[0]) - (left ? 1 : 0);
	if (left) {
		node->insert(par->__values[index]);
		for (int i = 0; i < brother->__count; ++i)
			node->insert(brother->__values[i]);
	}
	else {
		brother->insert(par->__values[index]);
		for (int i = 0; i < node->__count; ++i)
			brother->insert(node->__values[i]);
	}
	par->remove(par->__values[index]);
	for (int i = index; i < par->__count + 1; ++i)
		par->__ptrs[i] = par->__ptrs[i + 1];
}
