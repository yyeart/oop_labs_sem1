#include "lab01/matrix_ops.hpp"

#include <gtest/gtest.h>

namespace lab01 {
namespace {

TEST(MatrixCreateTest, AllocatesMatrixAndRows) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{3};

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);
    EXPECT_NE(matrix[0], nullptr);
    EXPECT_NE(matrix[1], nullptr);

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixCreateTest, InitializesZeroElements) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{2};

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        EXPECT_NE(matrix[i], nullptr);
        if (matrix[i] == nullptr) {
            continue;
        }
        for (std::size_t j = 0; j < kCols; ++j) {
            EXPECT_EQ(matrix[i][j], 0);
        }
    }

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixFillTest, FillsMatrix) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{3};

    const int value = -1;

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);

    matrix_fill(matrix, kRows, kCols, value);

    for (std::size_t i = 0; i < kRows; ++i) {
        EXPECT_NE(matrix[i], nullptr);
        if (matrix[i] == nullptr) {
            continue;
        }
        for (std::size_t j = 0; j < kCols; ++j) {
            EXPECT_EQ(matrix[i][j], value);
        }
    }

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixFillTest, ReplacesPreviousValues) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{2};

    const int first_value = 1;
    const int second_value = 2;

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);

    matrix_fill(matrix, kRows, kCols, first_value);
    matrix_fill(matrix, kRows, kCols, second_value);

    for (std::size_t i = 0; i < kRows; ++i) {
        EXPECT_NE(matrix[i], nullptr);
        if (matrix[i] == nullptr) {
            continue;
        }
        for (std::size_t j = 0; j < kCols; ++j) {
            EXPECT_EQ(matrix[i][j], second_value);
        }
    }

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, Transpose3x2Matrix) {
    constexpr std::size_t kRows{3};
    constexpr std::size_t kCols{2};

    int** matrix = matrix_create(kRows, kCols);
    int counter = 1;

    ASSERT_NE(matrix, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = counter;
            ++counter;
        }
    }

    const int expected[kCols][kRows] = {{1, 3, 5}, {2, 4, 6}};
    int** transposed = matrix_transpose(matrix, kRows, kCols);

    EXPECT_NE(transposed, nullptr);

    if (transposed != nullptr) {
        for (std::size_t i = 0; i < kCols; ++i) {
            EXPECT_NE(transposed[i], nullptr);
            if (transposed[i] == nullptr) {
                continue;
            }
            for (std::size_t j = 0; j < kRows; ++j) {
                EXPECT_EQ(transposed[i][j], expected[i][j]);
            }
        }
    }

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, TransposeSquareMatrix) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{2};

    int** matrix = matrix_create(kRows, kCols);
    int counter = 1;

    ASSERT_NE(matrix, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = counter;
            counter++;
        }
    }

    const int expected[kCols][kRows] = {{1, 3}, {2, 4}};
    int** transposed = matrix_transpose(matrix, kRows, kCols);

    EXPECT_NE(transposed, nullptr);

    if (transposed != nullptr) {
        for (std::size_t i = 0; i < kCols; ++i) {
            EXPECT_NE(transposed[i], nullptr);
            if (transposed[i] == nullptr) {
                continue;
            }
            for (std::size_t j = 0; j < kRows; ++j) {
                EXPECT_EQ(transposed[i][j], expected[i][j]);
            }
        }
    }

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, TransposeNx1Matrix) {
    constexpr std::size_t kRows{4};
    constexpr std::size_t kCols{1};

    int** matrix = matrix_create(kRows, kCols);
    int counter = 1;

    ASSERT_NE(matrix, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = counter;
            counter++;
        }
    }

    const int expected[kCols][kRows] = {1, 2, 3, 4};
    int** transposed = matrix_transpose(matrix, kRows, kCols);

    EXPECT_NE(transposed, nullptr);

    if (transposed != nullptr) {
        for (std::size_t i = 0; i < kCols; ++i) {
            EXPECT_NE(transposed[i], nullptr);
            if (transposed[i] == nullptr) {
                continue;
            }
            for (std::size_t j = 0; j < kRows; ++j) {
                EXPECT_EQ(transposed[i][j], expected[i][j]);
            }
        }
    }

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, Transpose1xNMatrix) {
    constexpr std::size_t kRows{1};
    constexpr std::size_t kCols{4};

    int** matrix = matrix_create(kRows, kCols);
    int counter = 1;

    ASSERT_NE(matrix, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = counter;
            counter++;
        }
    }

    const int expected[kCols][kRows] = {{1}, {2}, {3}, {4}};
    int** transposed = matrix_transpose(matrix, kRows, kCols);

    EXPECT_NE(transposed, nullptr);

    if (transposed != nullptr) {
        for (std::size_t i = 0; i < kCols; ++i) {
            EXPECT_NE(transposed[i], nullptr);
            if (transposed[i] == nullptr) {
                continue;
            }
            for (std::size_t j = 0; j < kRows; ++j) {
                EXPECT_EQ(transposed[i][j], expected[i][j]);
            }
        }
    }

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, PreservesSourceMatrix) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{3};

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);

    const int expected[kRows][kCols]{
        {1, 2, 3},
        {4, 5, 6},
    };

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = expected[i][j];
        }
    }

    int** transposed = matrix_transpose(matrix, kRows, kCols);

    EXPECT_NE(transposed, nullptr);

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            EXPECT_EQ(matrix[i][j], expected[i][j]);
        }
    }

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixTransposeTest, DoubleTransposeGivesOriginalMatrix) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{3};

    int** matrix = matrix_create(kRows, kCols);

    ASSERT_NE(matrix, nullptr);

    const int expected[kRows][kCols] = {{1, 2, 3}, {4, 5, 6}};

    for (std::size_t i = 0; i < kRows; ++i) {
        for (std::size_t j = 0; j < kCols; ++j) {
            matrix[i][j] = expected[i][j];
        }
    }

    int** first_transpose = matrix_transpose(matrix, kRows, kCols);
    EXPECT_NE(first_transpose, nullptr);

    int** second_transpose = nullptr;
    if (first_transpose != nullptr) {
        second_transpose = matrix_transpose(first_transpose, kCols, kRows);
    }
    EXPECT_NE(second_transpose, nullptr);

    if (second_transpose != nullptr) {
        for (std::size_t i = 0; i < kRows; ++i) {
            EXPECT_NE(matrix[i], nullptr);
            if (matrix[i] == nullptr) {
                continue;
            }

            EXPECT_NE(second_transpose[i], nullptr);
            if (second_transpose[i] == nullptr) {
                continue;
            }

            for (std::size_t j = 0; j < kCols; ++j) {
                EXPECT_EQ(expected[i][j], second_transpose[i][j]);
            }
        }
    }

    matrix_delete(second_transpose, kRows);
    second_transpose = nullptr;

    matrix_delete(first_transpose, kCols);
    first_transpose = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixOpsTest_Fail, ZeroOnZeroReturnsNullptr) {
    constexpr std::size_t kRows{0};
    constexpr std::size_t kCols{0};

    int** matrix = matrix_create(kRows, kCols);
    EXPECT_EQ(matrix, nullptr);

    int** transposed = matrix_transpose(matrix, kRows, kCols);
    EXPECT_EQ(transposed, nullptr);

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixOpsTest_Fail, ZeroOnNReturnsNullptr) {
    constexpr std::size_t kRows{0};
    constexpr std::size_t kCols{2};

    int** matrix = matrix_create(kRows, kCols);
    EXPECT_EQ(matrix, nullptr);

    int** transposed = matrix_transpose(matrix, kRows, kCols);
    EXPECT_EQ(transposed, nullptr);

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixOpsTest_Fail, NOnZeroReturnsNullptr) {
    constexpr std::size_t kRows{2};
    constexpr std::size_t kCols{0};

    int** matrix = matrix_create(kRows, kCols);
    EXPECT_EQ(matrix, nullptr);

    int** transposed = matrix_transpose(matrix, kRows, kCols);
    EXPECT_EQ(transposed, nullptr);

    matrix_delete(transposed, kCols);
    transposed = nullptr;

    matrix_delete(matrix, kRows);
    matrix = nullptr;
}

TEST(MatrixDeleteTest, NullptrOk) {
    EXPECT_NO_THROW(matrix_delete(nullptr, 0));
}
}  // namespace
}  // namespace lab01
