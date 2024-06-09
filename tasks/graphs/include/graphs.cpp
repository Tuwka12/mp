#include "pch.h"

#include "Functions.hpp"

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
    int* visited = new int[n] {};
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
    int* visited = new int[n] {};
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
    std::list<Edge>* E = new std::list<Edge>[n];
    int k = F(L, E, n);
    printf("Количество остовных деревьев = %d\n", k);
    for (int i = 0; i < k; ++i) {
        std::cout << i + 1 << ": ";
        auto iter = E[i].begin(), end = E[i].end();
        for (iter; iter != end; ++iter)
            std::cout << *iter << " ";
        std::cout << std::endl << std::endl;
    }
    delete[] E;
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
    int* visited = new int[n] {};
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
        m[i] = new int[n];
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
    int* S = new int[n] {};
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

// ----------------------АЛГОРИТМ НАХОЖДЕНИЯ СИЛЬНО СВЯЗНЫХ КОМПОНЕНТ------------------------------

// Функция для обхода в глубину
void dfs(std::vector<std::vector<int>>& G, int u, std::vector<bool>& visited, std::stack<int>& Stack) {
    visited[u] = true;
    for (int v : G[u])
        if (!visited[v])
            dfs(G, v, visited, Stack);
    Stack.push(u);
}

// Функция для обхода в глубину в обратном графе
void reverse_dfs(std::vector<std::vector<int>>& G, int u, std::vector<bool>& visited, std::vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : G[u])
        if (!visited[v])
            reverse_dfs(G, v, visited, component);
}

std::vector<std::vector<int>> strongly_connected_components(std::vector<std::vector<int>>& G, int n) {
    std::vector<bool> visited(n, false);
    std::stack<int> order;
    std::vector<std::vector<int>> inv(n), result;

    for (int i = 0; i < n; i++)
        if (!visited[i]) dfs(G, i, visited, order);
    for (int i = 0; i < n; i++)
        for (int v : G[i]) inv[v].push_back(i);
    fill(visited.begin(), visited.end(), false);

    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!visited[u]) {
            std::vector<int> component;
            reverse_dfs(inv, u, visited, component);
            result.push_back(component);
        }
    }
    return result;
}

void print_strongly_connected_components(std::vector<std::vector<int>>& G, int n) {
    auto res = strongly_connected_components(G, n);
    std::cout << "Сильно связные компоненты:\n";
    for (int i = 0; i < res.size(); ++i) {
        std::cout << i + 1 << ") ";
        for (int v : res[i]) std::cout << v << " ";
        std::cout << std::endl;
    }
}

// -----------------------АЛГОРИТМ НАХОЖДЕНИЯ ДВУСВЯЗНЫХ КОМПОНЕНТ------------------------------

// Обход в глубину компоненты связности
void DFSBlocks(std::list<int>* L, std::list<Edge>* T, int n, int u,
    std::stack<Edge>& S, int* dfnumber, int* markedge,
    int* father, int& numver, int** NumEdge, int& count, int* P)
{
    dfnumber[u] = P[u] = ++numver;
    auto it = L[u].begin(), end = L[u].end();
    while (it != end) {
        int v = *it;
        int k = NumEdge[u][v];
        if (!markedge[k]) {
            Edge edge(u, v);
            S.push(edge);
            markedge[k] = 1;
        }
        if (dfnumber[v] == 0) {
            father[v] = u;
            DFSBlocks(L, T, n, v, S, dfnumber, markedge, father, numver, NumEdge, count, P);
            int backedge = -1;
            for (int row = v - 2; row >= 0; --row) {
                backedge = NumEdge[row][v];
                if (backedge != -1 && markedge[backedge] == 0) {
                    Edge edge(row, v);
                    S.push(edge);
                    markedge[backedge] = 1;
                    if (dfnumber[row] < P[v])
                        P[v] = dfnumber[row];
                    break;
                }
            }
            if (P[u] > P[v]) P[u] = P[v];
            if (P[v] >= dfnumber[u]) {
                Edge edge(u, v), p;
                while (!S.empty() && (p = S.top()) != edge) {
                    S.pop();
                    T[count].push_back(p);
                }
                S.pop();
                T[count].push_back(p);
                ++count;
            }
        }
        ++it;
    }
}

int FindBlocks(std::list<int>* L, std::list<Edge>* T, int n, int m, int** NumEdge) {
    std::stack<Edge> S;
    int count = 0;
    int* markedge = new int[m] {};
    int* dfnumber = new int[n] {};
    int* P = new int[n] {};
    int* father = new int[n] {};
    int numver = 0;
    for (int u = 0; u < n; ++u)
        if (!dfnumber[u])
            DFSBlocks(L, T, n, u, S, dfnumber, markedge, father, numver, NumEdge, count, P);
    return count;
}

// -----------------------------------АЛГОРИТМ ФОРДА-ФАЛКЕРСОНА------------------------------------------

// Нахождение пути от истока до стока с помощью поиска в ширину
bool path_exists(int** G, int n, int source, int sink, int* parents) {
    int* visited = new int[n] {};
    std::queue<int> q;
    int v, i;
    q.push(source);
    visited[source] = 1;

    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (i = 0; i < n; ++i) {
            if (!visited[i] && G[v][i] > 0) {
                q.push(i);
                visited[i] = 1;
                parents[i] = v;
            }
        }
    }
    return visited[sink];
}

int FordFalkerson(int** G, int n, int source, int sink) {
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) parent[i] = -1;
    int max_flow = 0, path_flow, v, s;

    while (path_exists(G, n, source, sink, parent)) {
        path_flow = INT_MAX;
        s = sink;
        while (s != source) {
            path_flow = G[parent[s]][s] < path_flow ? G[parent[s]][s] : path_flow;
            s = parent[s];
        }
        max_flow += path_flow;
        v = sink;
        while (v != source) {
            G[parent[v]][v] -= path_flow;
            G[v][parent[v]] += path_flow;
            v = parent[v];
        }
    }
    return max_flow;
}