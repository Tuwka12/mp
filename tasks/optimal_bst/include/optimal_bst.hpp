#include "pch.hpp"

template<typename T>
class OptimalBST {
private:
	struct Cell
        { int _index = 0, _t = INT32_MAX, _w = INT32_MAX; };
	class TreeNode {
	public:
		T __value;
		TreeNode* __left;
		TreeNode* __right;
		TreeNode(const T& value);
	};

public:

	OptimalBST(T* values, int* weights, int* failures, int size);
    const TreeNode* find(const T& value) const;
    bool contains(const T& value);
	void output() const;

    std::vector<T> roundLrootR();
    std::vector<T> roundRrootL();

private:

	bool insert(const T& value);
	void insert_recursive(const T& value, TreeNode*& node);
	void printSubTree(TreeNode* node, size_t offset = 0) const;

    std::vector<T> subTreeRoundRrootL(TreeNode* node);

	void fill_matrix(Cell**& matrix, int* weights, int* failures, int size);
	void build_tree(T* values, Cell** matrix, int size);
	void build_tree_recursive(T* values, Cell** matrix, int left, int right);

	TreeNode* __root;
};

template <typename T>
OptimalBST<T>::TreeNode::TreeNode(const T& value)
	: __value(value), __left(nullptr), __right(nullptr) {}


template<typename T>
inline OptimalBST<T>::OptimalBST(T* values, int* weights, int* failures, int size) 
    : __root(nullptr) 
{
    Cell** matrix = new Cell * [size] {};
    for (int i = 0; i < size; ++i)
        matrix[i] = new Cell[size]{};

    fill_matrix(matrix, weights, failures, size);
    build_tree(values, matrix, size);

    for (int i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;
}


template<typename T>
inline void OptimalBST<T>::build_tree_recursive(
    T* values, Cell** matrix, int left, int right)
{
    int root_index = matrix[left][right]._index;
    this->insert(values[root_index]);
    if (root_index - 1 >= left)
        build_tree_recursive(values, matrix, left, root_index - 1);
    if (root_index + 1 <= right)
        build_tree_recursive(values, matrix, root_index + 1, right);
}


template<typename T>
inline void OptimalBST<T>::build_tree(T* values, Cell** matrix, int size) {
    return build_tree_recursive(values, matrix, 0, size - 1);
}


template<typename T>
inline void OptimalBST<T>::fill_matrix(
    Cell**& matrix, int* weights, int* failures, int size)
{
    for (int offset = 0; offset < size; ++offset) {
        for (int row = 0; row < size - offset; ++row) {
            int W = failures[row];
            for (int root = row; root < offset + row + 1; ++root) {
                int Wl = 0, Wr = 0, Tl = 0, Tr = 0; 
                W += (weights[root] + failures[root + 1]);
                if (root != row) {
                    Wl = matrix[row][root - 1]._w;
                    Tl = matrix[row][root - 1]._t;
                }
                if (root != offset + row) {
                    Wr = matrix[root + 1][offset + row]._w;
                    Tr = matrix[root + 1][offset + row]._t;
                }
                int t = Tl + Tr + Wl + Wr;
                if (t < matrix[row][row + offset]._t) {
                    matrix[row][row + offset]._index = root;
                    matrix[row][row + offset]._t = t;
                }
            }
            matrix[row][row + offset]._w = W;
        }
    }
}


template <typename T>
inline void OptimalBST<T>::insert_recursive(const T& value, TreeNode*& node) {
	if (!node) node = new TreeNode(value);
	else insert_recursive(value, value < node->__value ? node->__left : node->__right);
}


template <typename T>
inline bool OptimalBST<T>::insert(const T& value) {
	insert_recursive(value, __root);
	return true;
}


template <typename T>
inline void OptimalBST<T>::output() const {
	printSubTree(__root);
}


template <typename T>
inline void OptimalBST<T>::printSubTree(TreeNode* node, size_t offset) const {
	if (!node) return;
	if (node->__right) printSubTree(node->__right, offset + 1);
	for (size_t i = 0; i < offset; ++i) std::cout << "   ";
	std::cout << node->__value << "\n";
	if (node->__left) printSubTree(node->__left, offset + 1);
}


template<typename T>
inline const typename OptimalBST<T>::TreeNode* OptimalBST<T>::find(
    const T& value) const 
{
    TreeNode* current = __root;
    while (current) {
        if (value == current->__value) return current;
        current = value < current->__value ? current->__left : current->__right;
    }
    return nullptr;
}


template <typename T>
inline bool OptimalBST<T>::contains(const T& value) {
    return find(value) != nullptr;
}


template <typename T>
inline std::vector<T> OptimalBST<T>::roundRrootL() {
    return subTreeRoundRrootL(__root);
}


template <typename T>
inline std::vector<T> OptimalBST<T>::roundLrootR() {
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
inline std::vector<T> OptimalBST<T>::subTreeRoundRrootL(TreeNode* node) {
    if (!node) return std::vector<T>();
    std::vector<T> result;
    if (node->__right)
        result = vector_merge(result, subTreeRoundRrootL(node->__right));
    result.push_back(node->__value);
    if (node->__left)
        result = vector_merge(result, subTreeRoundRrootL(node->__left));
    return result;
}

