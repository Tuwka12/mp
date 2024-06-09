#pragma once

#include "FunctionsApi.hpp"

// Тип данных - ребро графа (v1,v2)
struct Edge {
    int v1, v2;
    TIH_API Edge(int _v1 = 0, int _v2 = 0) : v1(_v1), v2(_v2) {}

    TIH_API bool operator != (Edge& edge) {
        return v1 != edge.v1 || v2 != edge.v2;
    }

    TIH_API friend std::ostream& operator << (std::ostream& out, Edge& edge) {
        out << '(' << edge.v1 << ',' << edge.v2 << ')';
        return out;
    }
};

// Указатель на функию обхода графа
using round_func = int (*)(std::list<int>*, std::list<Edge>*, int);

const int MAXDIST = 1000000;

// -----------------------------------------------------------------------------

// * Алгоритмы обхода графов
// Поиск в глубину
TIH_API void DFS(std::list<int>* L, std::list<Edge>* E, int v, int count, int* visited);
TIH_API int DFS_recursive(std::list<int>* L, std::list<Edge>* E, int n);

// Поиск в ширину
TIH_API void BFS(std::list<int>* L, std::list<Edge>* E, int v, int count,
         int* visited, std::queue<int> Q);
TIH_API int BFS_recursive(std::list<int>* L, std::list<Edge>* E, int n);
TIH_API void make_round(round_func F, std::list<int>* L, int n);

 // * Алгоритм Прима
TIH_API void find_min_edge(int** C, int n, int* visited, int& v, int& w);
TIH_API Edge* Prim(int** C, int n);
TIH_API void print_min_ost_tree(Edge* E, int n);
TIH_API int** create_matrix(int n);

// * Алгоритм Краскала
TIH_API Edge* Kruskal(int n, Edge* edges, int m);

// * Алгоритм Дейкстры
TIH_API int* Dijkstra(int** C, int n, int x);
TIH_API void Dijkstra_wrap(int** C, int n);

// * Алгоритм Беллмана-Форда
TIH_API bool BellmanFord(int** C, int n, int* dist, int x);
TIH_API void BellmanFord_wrap(int** C, int n);
TIH_API void print_weights(int** C, int n);

// * Алгоритм нахождения сильно связных компонент
TIH_API void dfs(std::vector<std::vector<int>>& G, int v, std::vector<bool>& visited, std::stack<int>& order);
TIH_API void reverse_dfs(std::vector<std::vector<int>>& G, int v, std::vector<bool>& visited, std::vector<int>& component);
TIH_API std::vector<std::vector<int>> strongly_connected_components(std::vector<std::vector<int>>& G, int n);
TIH_API void print_strongly_connected_components(std::vector<std::vector<int>>& G, int n);

// * Алгоритм нахождения двусвязных компонент
TIH_API void DFSBlocks(std::list<int>* L, std::list<Edge>* T, int n, int u,
    std::stack<Edge>& S, int* dfnumber, int* markedge,
    int* father, int& numver, int** NumEdge, int& count, int* P);
TIH_API int FindBlocks(std::list<int>* L, std::list<Edge>* T, int n, int m, int** NumEdge);

// * Алгоритм Форда-Фалкерсона
TIH_API bool path_exists(int** G, int n, int source, int sink, int* parent);
TIH_API int FordFalkerson(int** G, int n, int source, int sink);