//
// Created by gregj on 10/13/2024.
//

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(FactorialTest, Negative) {
    // This test is named "Negative", and belongs to the "FactorialTest"
    // test case.
    const Matrices::Matrix matrix(10,10);
    const int size = static_cast<int>(matrix.matrix.size());
    EXPECT_EQ(size, 10);
}

