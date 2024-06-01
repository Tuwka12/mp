#include <gtest/gtest.h>
#include "subsetgen.cpp"

TEST(SubSetGenTest, SubSetWithoutStack) {
    print(sub_set(4));
}

TEST(SubSetGenTest, CodeGreyWithStack) {
    print(code_grey(3));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}