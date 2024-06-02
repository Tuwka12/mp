#include "pch.hpp"

// Тип данных - ребро графа (v1,v2)
struct Edge {
    int v1, v2;

    Edge(int _v1 = 0, int _v2 = 0) : v1(_v1), v2(_v2) {}

    bool operator != (Edge& edge) 
        { return v1 != edge.v1 || v2 != edge.v2; }

    friend std::ostream& operator << (std::ostream& out, Edge& edge) {
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
void DFS(std::list<int>* L, std::list<Edge>* E, int v, int count, int* visited);
int DFS_recursive(std::list<int>* L, std::list<Edge>* E, int n);

// Поиск в ширину
void BFS(std:: list<int>* L, std:: list<Edge>* E, int v, int count, 
    int *visited, std:: queue<int> Q);
int BFS_recursive(std::list<int>* L, std::list<Edge>* E, int n);

// * Алгоритм Прима
void find_min_edge(int** C, int n, int* visited, int& v, int& w);
void Prim(double** C, int n, Edge* E);
void print_min_ost_tree(Edge* E, int n);

// * Алгоритм Краскала
void Kruskal(int n, Edge* edges, Edge* T, int m);

// * Алгоритм Дейкстры
int* Dijkstra(int** C, int n, int x);

// * Алгоритм Беллмана-Форда
bool BellmanFord(int** C, int n, int* dist, int x);

// ----------------------АЛГОРИТМЫ ОБХОДА ГРАФА--------------------------------------

// Поиск в глубину для одной вершины
void DFS(std::list<int>* L, std::list<Edge>* E, int v, int count, int* visited) {
    visited[v] = 1;
    auto it = L[v].begin(), end = L[v].end();
    while (it != end) {
        int w = *it;
        if (!visited[w]) {
            Edge edge(v, w);
            E[count].push_back(edge);
            DFS(L, E, w, count, visited);
        }
        ++it;
    }
}

// Поиск в глубину
int DFS_recursive(std::list<int>* L, std::list<Edge>* E, int n) {
    int* visited = new int[n]{};
    int count = 0;
    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            DFS(L, E, v, count, visited);
            ++count;
        }
    }
    delete[] visited;
    return count;
}

// Поиск в ширину для одной вершины
void BFS(std::list<int>* L, std::list<Edge>* E, int v, int count, 
    int* visited, std::queue<int> Q) 
{
    visited[v] = 1;
    Q.push(v);
    while (!Q.empty()) {
        int w = Q.front();
        Q.pop();
        auto it = L[w].begin(), end = L[w].end();
        while (it != end) {
            int u = *it;
            if (!visited[u]) {
                visited[u] = 1;
                Edge edge(w, u);
                E[count].push_back(edge);
                Q.push(u);
            }
            ++it;
        }
    }    
}

// Поиск в ширину
int BFS_recursive(std::list<int>* L, std::list<Edge>* E, int n) {
    std::queue<int> Q;
    int* visited = new int[n]{};
    int count = 0;
    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            BFS(L, E, v, count, visited, Q);
            ++count;
        }
    }
    delete[] visited;
    return count;
}

// Обход графа
void make_round(round_func F, std::list<int>* L, int n) {
    std::list<Edge> E[n];
    int k = F(L, E, n);
    printf("Количество остовных деревьев = %d\n", k);
    for (int i = 0; i < k; ++i) {
        std::cout << i + 1 << ": ";
        auto iter = E[i].begin(), end = E[i].end();
        for (iter; iter != end; ++iter) 
            std::cout << *iter << " ";
        std::cout << std::endl << std::endl;
    }
}

// --------------------АЛГОРИТМ ПРИМА--------------------------------------------

// Поиск невключенного ребра минимального веса
void find_min_edge(int** C, int n, int* visited, int& v, int& w) {
    v = w = 0;
    int tmp = MAXDIST;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && visited[i] && !visited[j] && C[i][j] < tmp) {
                v = i, w = j;
                tmp = C[v][w];
            }
        }
    }
}

// Алгоритм Прима
Edge* Prim(int** C, int n) {
    Edge* E = new Edge[n - 1]{};
    int v, w, j = 0, count = 1;
    int* visited = new int[n]{};
    visited[0] = 1;

    while (count != n) {
        find_min_edge(C, n, visited, v, w);
        Edge edge(v, w);
        E[j++] = edge;
        v = w;
        visited[v] = 1;
        ++count;
    }
    delete[] visited;
    return E;
}

// Вывод в консоль минимального остовного дерева
void print_min_ost_tree(Edge* E, int n) {
    std::cout << "Минимальное остовное дерево для данного графа:\n";
    for (int i = 0; i < n - 1; ++i) std::cout << E[i] << " ";
    std::cout << std::endl << std::endl;
}

// Инициализация матрицы NxN
int** create_matrix(int n) {
    int** m = new int* [n];
    for (int i = 0; i < n; ++i) {
        m[i] = new int [n];
        for (int j = 0; j < n; ++j)
            m[i][j] = (i == j) ? 0 : MAXDIST;
    }
    return m;
}

// -----------------------АЛГОРИТМ КРАСКАЛА---------------------------------------------

Edge* Kruskal(int n, Edge* edges, int m) {
    Edge* E = new Edge[n - 1]{};
    int* components = new int[n];
    for (int i = 0; i < n; ++i) 
        components[i] = i;

    int current = 0, count = n, j = 0;
    while (current < m && count > 1) {
        Edge edge = edges[current];
        if (components[edge.v1] != components[edge.v2]) {
            int k = components[edge.v2];
            for (int i = 0; i < n; ++i) {
                if (components[i] == k)
                    components[i] = components[edge.v1];
            }
            --count;
            E[j++] = edge;
        }
        ++current;
    }
    delete[] components;
    return E;
}

// ------------------------------АЛГОРИТМ ДЕЙКСТРЫ--------------------------------------

// Алгоритм Дейкстры
int* Dijkstra(int** C, int n, int x) {
    int* distance = new int[n];
    int* S = new int[n]{};
    S[x] = 1;
    int count = 1;
    for (int i = 0; i < n; ++i)
        distance[i] = C[x][i];
    while (count < n) {
        int j = 1;
        while (S[j]) ++j;
        int k = j;
        for (int i = j + 1; i < n; ++i)
            if (!S[i] && distance[k] > distance[i])
                k = i;
        S[k] = 1;
        ++count;
        for (j = 1; j < n; ++j)
            if (!S[j] && distance[j] > distance[k] + C[k][j])
                distance[j] = distance[k] + C[k][j];
    }
    delete[] S;
    return distance;
}

//  Вывод в консоль матрицы весов рёбер данного графа
void print_weights(int** C, int n) {
    std::cout << "Матрица весов рёбер:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (C[i][j] == MAXDIST) std::cout << std::setw(4) << "-";
            else std::cout << std::setw(4) << C[i][j];
        } std::cout << std::endl;
    } std::cout << std::endl;
}

// Обход всего графа с использованием алгоритма Дейкстры
void Dijkstra_wrap(int** C, int n) {
    for (int i = 0; i < n; ++i) {
        int* dist = Dijkstra(C, n, i);
        std::cout << i << ')';
        for (int j = 0; j < n; ++j) {
            if (dist[j] == MAXDIST)
                std::cout << std::setw(4) << "-";
            else std::cout << std::setw(4) << dist[j];
        }
        std::cout << std::endl;
        delete[] dist;
    }
    for (int i = 0; i < n; ++i) delete[] C[i];
    delete[] C;
}

// ------------------------------АЛГОРИТМ БЕЛЛМАНА-ФОРДА----------------------------

bool BellmanFord(int** C, int n, int* distance, int x) {
    bool flag = true;
    for (int i = 0; i < n; ++i)
        distance[i] = C[x][i];
    for (int k = 0; k < n - 1; ++k) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                if (C[i][j] != 0 && distance[j] > distance[i] + C[i][j])
                    distance[j] = distance[i] + C[i][j];
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (C[i][j] != 0 && distance[j] > distance[i] + C[i][j]) {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

// Обход всего графа с использованием алгоритма Беллмана-Форда
void BellmanFord_wrap(int** C, int n) {
    int* distance = new int[n];
    for (int i = 0; i < n; ++i) {
        if (BellmanFord(C, n, distance, i)) {
            std::cout << i << ')';
            for (int j = 0; j < n; ++j) {
                if (distance[j] == MAXDIST) 
                    std::cout << std::setw(4) << "-";
                else std::cout << std::setw(4) << distance[j];
            } std::cout << std::endl;
        }
        else std::cout << "Кратчайшие расстояния определить невозможно" << std::endl;
    }
    for (int i = 0; i < n; ++i) delete[] C[i];
    delete[] C; delete[] distance;
}