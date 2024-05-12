#ifndef _ADD_H
#define _ADD_H

#include <stack>

template <typename T>
std::vector<T> vector_merge(std::vector<T> left, std::vector<T> right);

template <typename T>
class BST {
private:
	class TreeNode {
	public:
		T __value;
		TreeNode* __left;
		TreeNode* __right;
		TreeNode(const T& value);
	};

public:

	BST();
	BST(std::vector<T> elements);
	BST(const BST& other);
	BST(BST&& other);

	~BST();

	BST& operator = (const BST& tree) = delete;
	BST& operator = (BST&& tree) = delete;

	bool empty() const;
	bool insert(const T& value);
	bool remove(const T& value);
	bool contains(const T& value);

	std::vector<T> roundLrootR();
	std::vector<T> roundRrootL();
	std::vector<T> roundLRroot();
	std::vector<T> roundRLroot();

	void output();

public:
	std::vector<T> subTreeRoundRrootL(BST<T>::TreeNode* node);
	std::vector<T> subTreeRoundLRroot(BST<T>::TreeNode* node);

	std::pair<BST<T>::TreeNode*, BST<T>::TreeNode*> find(const T& value);

	void printSubTree(BST<T>::TreeNode* node, size_t offset = 0);

	void recursiveRemove(BST<T>::TreeNode* node);
	void recursiveInsert(BST<T>::TreeNode*& node, const T& value);

	void removeWithoutChilds(BST<T>::TreeNode* node, BST<T>::TreeNode* parent);
	void removeWithRightChild(BST<T>::TreeNode* node, BST<T>::TreeNode* parent);
	void removeWithLeftChild(BST<T>::TreeNode* node, BST<T>::TreeNode* parent);
	void removeWithTwoChilds(BST<T>::TreeNode* node);

	BST<T>::TreeNode* __root;
};

// TREE_NODE //

template <typename T>
BST<T>::TreeNode::TreeNode(const T& value)
	: __value(value), __left(nullptr), __right(nullptr) {}

// BINARY_SEARCH_TREE //

template <typename T>
inline BST<T>::BST() : __root(nullptr) {}

template <typename T>
inline BST<T>::BST(std::vector<T> elements) : __root(nullptr) {
	size_t size = elements.size();
	for (size_t i = 0; i < size; ++i)
		insert(elements[i]);
}

template <typename T>
inline BST<T>::~BST() {
	recursiveRemove(__root);
}

template <typename T>
inline void BST<T>::recursiveRemove(BST<T>::TreeNode* node) {
	if (node) {
		recursiveRemove(node->__left);
		recursiveRemove(node->__right);
	}
	delete node;
}

template <typename T>
inline BST<T>::BST(const BST& other) : __root(nullptr) {
	if (!other.__root) return;

	std::stack<BST<T>::TreeNode*> nodes;
	TreeNode* current = other.__root;
	nodes.push(current);

	while (!nodes.empty()) {
		insert(current->__value);
		if (current->__left && current->__right) {
			nodes.push(current);
			current = current->__left;
		}
		else if (!current->__left && !current->__right) {
			current = nodes.top()->__right;
			nodes.pop();
		}
		else {
			current = current->__left ? current->__left : current->__right;
		}
	}
}

template <typename T>
inline BST<T>::BST(BST<T>&& other) : __root(nullptr) {
	__root = other.__root;
	other.__root = nullptr;
}

template <typename T>
inline void BST<T>::recursiveInsert(BST<T>::TreeNode*& node, const T& value) {
	if (!node) node = new TreeNode(value);
	else recursiveInsert(value < node->__value ? node->__left : node->__right, value);
}

template <typename T>
inline bool BST<T>::insert(const T& value) {
	recursiveInsert(__root, value);
	return true;
}

template <typename T>
inline bool BST<T>::empty() const {
	return __root == nullptr;
}

template <typename T>
inline bool BST<T>::contains(const T& value) {
	TreeNode* current = __root;
	while (current) {
		if (value == current->__value) return true;
		current = value < current->__value ? current->__left : current->__right;
	}
	return false;
}

template<typename T>
inline std::pair<typename BST<T>::TreeNode*, typename BST<T>::TreeNode*> BST<T>::find(const T& value) {
	TreeNode* current = __root;
	TreeNode* parent = nullptr;
	while (current) {
		if (value == current->__value) break;
		parent = current;
		current = value < current->__value ? current->__left : current->__right;
	}
	return std::pair<typename BST<T>::TreeNode*, typename BST<T>::TreeNode*>(current, parent);
}

template <typename T>
inline bool BST<T>::remove(const T& value) {
	auto nodes = find(value);
	TreeNode* current = nodes.first;
	TreeNode* parent = nodes.second;

	if (!current) return false;
	if (!current->__left && !current->__right) removeWithoutChilds(current, parent);
	else if (!current->__left && current->__right) removeWithRightChild(current, parent);
	else if (current->__left && !current->__right) removeWithLeftChild(current, parent);
	else removeWithTwoChilds(current);
	return true;
}

template <typename T>
inline std::vector<T> BST<T>::roundRrootL() {
	return subTreeRoundRrootL(__root);
}

template <typename T>
inline std::vector<T> BST<T>::roundLRroot() {
	return subTreeRoundLRroot(__root);
}

template <typename T>
inline std::vector<T> BST<T>::roundLrootR() {
	std::vector<T> result = subTreeRoundRrootL(__root);
	std::reverse(result.begin(), result.end());
	return result;
}

template <typename T>
inline std::vector<T> BST<T>::roundRLroot() {
	std::vector<T> result = subTreeRoundLRroot(__root);
	std::reverse(result.begin(), result.end());
	return result;
}

template <typename T>
inline void BST<T>::output() {
	printSubTree(__root);
}

template <typename T>
inline void BST<T>::printSubTree(BST<T>::TreeNode* node, size_t offset) {
	if (!node) return;
	if (node->__right) printSubTree(node->__right, offset + 1);
	for (size_t i = 0; i < offset; ++i) std::cout << "   ";
	std::cout << node->__value << "\n";
	if (node->__left) printSubTree(node->__left, offset + 1);
}

template <typename T>
inline std::vector<T> BST<T>::subTreeRoundRrootL(TreeNode* node) {
	if (!node) return std::vector<T>();
	std::vector<T> result;
	if (node->__right)
		result = vector_merge(result, subTreeRoundRrootL(node->__right));
	result.push_back(node->__value);
	if (node->__left)
		result = vector_merge(result, subTreeRoundRrootL(node->__left));
	return result;
}

template <typename T>
inline std::vector<T> BST<T>::subTreeRoundLRroot(BST<T>::TreeNode* node) {
	if (!node) return std::vector<T>();
	std::vector<T> result;
	if (node->__left) 
		result = vector_merge(result, subTreeRoundLRroot(node->__left));
	if (node->__right) 
		result = vector_merge(result, subTreeRoundLRroot(node->__right));
	result.push_back(node->__value);
	return result;
}

template <typename T>
inline void BST<T>::removeWithoutChilds(BST<T>::TreeNode* node, BST<T>::TreeNode* parent) {
	if (node == __root) __root = nullptr;
	else if (parent->__value > node->__value) parent->__left = nullptr;
	else parent->__right = nullptr;
	delete node;
}

template <typename T>
inline void BST<T>::removeWithRightChild(BST<T>::TreeNode* node, BST<T>::TreeNode* parent) {
	if (node == __root) __root = node->__right;
	else if (parent->__value > node->__value) parent->__left = node->__right;
	else parent->__right = node->__right;
	delete node;
}

template <typename T>
inline void BST<T>::removeWithLeftChild(BST<T>::TreeNode* node, BST<T>::TreeNode* parent) {
	if (node == __root) __root = node->__left;
	else if (parent->__value > node->__value) parent->__left = node->__left;
	else parent->__right = node->__left;
	delete node;
}

template <typename T>
inline void BST<T>::removeWithTwoChilds(BST<T>::TreeNode* node) {
	TreeNode* max_node = node->__left;
	while (max_node->__right) max_node = max_node->__right;
	T max_value = max_node->__value;
	remove(max_value);
	node->__value = max_value;
}

// OTHER FUNCTIONS //

template <typename T>
inline std::vector<T> vector_merge(std::vector<T> left, std::vector<T> right) {
	size_t count = right.size();
	for (size_t i = 0; i < count; ++i) left.push_back(right[i]);
	return left;
}


#endif