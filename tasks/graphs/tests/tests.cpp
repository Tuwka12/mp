#include <gtest/gtest.h>
#include "graphs.hpp"

TEST(GraphTest, DFSTest1) {
    std::list<int> L[6];
    L[0].push_back(1); L[0].push_back(5);
    L[1].push_back(2);
    L[2].push_back(3);
    L[3].push_back(4);
    L[4].push_back(1);
    L[5].push_back(4);

    make_round(DFS_recursive, L, 6);
}

// Граф на рис. 5.2.1 стр. 286
TEST(GraphTest, DFSTest2) {
    std::list<int> L[7];
    L[0].push_back(1);
    L[1].push_back(2); L[1].push_back(3); L[1].push_back(4);
    L[2].push_back(4); L[2].push_back(5);
    L[3].push_back(6);
    L[4].push_back(0);
    L[5].push_back(3);
    L[6].push_back(0);

    make_round(DFS_recursive, L, 7);
}

TEST(GraphTest, PrimTest) {
    int n = 6;
    auto C = create_matrix(n);
    C[0][1] = 8; C[1][0] = 8;
    C[0][5] = 5; C[5][0] = 5;
    C[1][2] = 1; C[2][1] = 1;
    C[2][3] = 10; C[3][2] = 10;
    C[3][4] = 1; C[4][3] = 1;
    C[4][1] = 15; C[1][4] = 15;
    C[5][4] = 3; C[4][5] = 3;

    auto res = Prim(C, n);
    print_min_ost_tree(res, n);

    for(int i = 0; i < n; ++i) 
        delete[] C[i];
    delete[] C; delete[] res;
}

TEST(GraphTest, PrimTest2) {
    int n = 7;
    auto C = create_matrix(n);
    C[0][1] = 20; C[1][0] = 20;
    C[0][4] = 2; C[4][0] = 2;
    C[0][6] = 5; C[6][0] = 5;
    C[1][2] = 3; C[2][1] = 3;
    C[1][3] = 2; C[3][1] = 2;
    C[1][4] = 15; C[4][1] = 15;
    C[2][4] = 10; C[4][2] = 10;
    C[2][5] = 1; C[5][2] = 1;
    C[3][5] = 4; C[5][3] = 4;
    C[3][6] = 1; C[6][3] = 1;

    auto res = Prim(C, n);
    print_min_ost_tree(res, n);

    for(int i = 0; i < n; ++i) 
        delete[] C[i];
    delete[] C; delete[] res;
}

TEST(GraphTest, KruskalTest) {
    int m = 7, n = 6;
    Edge edges[m];
    edges[0] = Edge(1,2);
    edges[1] = Edge(3,4);
    edges[2] = Edge(5,4);
    edges[3] = Edge(0,5);
    edges[4] = Edge(0,1);
    edges[5] = Edge(2,3);
    edges[6] = Edge(4,1);

    auto res = Kruskal(n, edges, m);
    print_min_ost_tree(res, n);
    delete[] res;
}

TEST(GraphTest, KruskalTest2) {
    int m = 9, n = 7;
    Edge edges[m];
    edges[0] = Edge(2, 5);
    edges[1] = Edge(3, 6);
    edges[2] = Edge(1, 3);
    edges[3] = Edge(0, 4);
    edges[4] = Edge(1, 2);
    edges[5] = Edge(3, 5);
    edges[6] = Edge(0, 6);
    edges[7] = Edge(2, 4);
    edges[8] = Edge(0, 1);

    auto res = Kruskal(n, edges, m);
    print_min_ost_tree(res, n);
    delete[] res;
}

// TEST(GraphTest, DijkstraTest) {
//     int n = 6;
//     auto C = create_matrix(n);
//     C[0][1] = 20;
//     C[0][4] = 10;
//     C[3][2] = 20;
//     C[5][2] = 1; 
//     C[0][3] = 40;
//     C[1][5] = 10;
//     C[4][3] = 15; 

//     print_weights(C, n);
//     Dijkstra_wrap(C, n);
// }

// TEST(GraphTest, DijkstraTest2) {
//     int n = 6;
//     auto C = create_matrix(n);
//     C[0][1] = 8; 
//     C[0][5] = 5; 
//     C[1][2] = 1; 
//     C[2][3] = 10;
//     C[3][4] = 1; 
//     C[4][1] = 15;
//     C[5][4] = 3; 

//     print_weights(C, n);
//     Dijkstra_wrap(C, n);
// }

// TEST(GraphTest, BellmanFordTest) {
//     int n = 6;
//     auto C = create_matrix(n);
//     C[0][1] = 20;
//     C[0][4] = 10;
//     C[3][2] = 20;
//     C[5][2] = 1; 
//     C[0][3] = 40;
//     C[1][5] = 10;
//     C[4][3] = 15; 

//     print_weights(C, n);
//     BellmanFord_wrap(C, n);
// }

TEST(GraphTest, BellmanFordTest2) {
    int n = 5;
    auto C = create_matrix(n);
    C[0][1] = 6; C[0][3] = 7;
    C[1][2] = 3; C[1][3] = 8;
    C[1][4] = -4; C[2][1] = -2;
    C[3][2] = -3; C[3][4] = 9;
    C[4][0] = 2; C[4][2] = 7;

    print_weights(C, n);
    BellmanFord_wrap(C, n);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}