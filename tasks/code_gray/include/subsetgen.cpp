#include "subsetgen.hpp"

list sub_set(int n) {
    std::vector<int> vec(n + 1);
    std::vector<int> tmp(n);
    list result;
    int i, j;
    for (i = 0; i < n + 1; ++i) vec[i] = 0;
    while (vec[0] == 0) {
        for (i = 1; i < n + 1; ++i) {
            std::copy(++vec.begin(), vec.end(), tmp.begin());
            result.push_back(tmp);
            i = n;
            while (vec[i] == 1) vec[i--] = 0;
            vec[i] = 1;
        }
    }
    result.pop_back();
    return result;
}

list code_grey(int n) {
    std::stack<int> st;
    std::vector<int> vec(n);
    list result;
    int i, j;
    for (i = n - 1; i >= 0; --i) 
        st.push(i);
    while (!st.empty()) {
        result.push_back(vec);
        i = st.top(); 
        st.pop();
        vec[n - i - 1] = (vec[n - i - 1] + 1) % 2;
        for (j = i - 1; j >= 0; --j) st.push(j);
    }
    result.push_back(vec);
    return result;
}

void print(list lst) {
    int m = lst.size(), n = lst[0].size(), i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j)
            std::cout << lst[i][j] << " ";
        std::cout << '\n';
    }
}