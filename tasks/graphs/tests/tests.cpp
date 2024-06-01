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
    auto C = create_matrix(6);
    C[0][1] = 8; C[0][5] = 5;
    C[1][2] = 1;
    C[2][3] = 10;
    C[3][4] = 1;
    C[4][1] = 15;
    C[5][4] = 3;

    Prim_wrap(C, 6);
}

TEST(GraphTest, PrimTest2) {
    auto C = create_matrix(7);
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

    Prim_wrap(C, 7);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}