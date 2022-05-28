#include "gtest/gtest.h"
#include "iostream"

TEST(LinearAlgebra, transposeMatrix) {
    std::cout << "Running google tests!\n";
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}