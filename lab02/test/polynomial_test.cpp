#include "lab02/polynomial.hpp"

#include <utility>

#include <gtest/gtest.h>

namespace lab02 {
namespace {

TEST(PolynomialTest, CreatesEmptyPolynomial) {
    const Polynomial polynomial;

    EXPECT_EQ(polynomial.degree(), -1);
    EXPECT_DOUBLE_EQ(polynomial.evaluate(2.0), 0.0);
}

TEST(PolynomialTest, CreatesConstantAndTrimsZeros) {
    const double single[]{7.0};
    const Polynomial constant(single, 0);

    EXPECT_EQ(constant.degree(), 0);
    EXPECT_DOUBLE_EQ(constant.coeff(0), 7.0);

    const double coefficients[]{7.0, 0.0, 0.0};
    Polynomial polynomial(coefficients, 2);

    polynomial.trim();

    EXPECT_EQ(polynomial.degree(), 0);
    EXPECT_DOUBLE_EQ(polynomial.coeff(0), 7.0);
}

TEST(PolynomialTest, CopyConstructorCreatesIndependentCopy) {
    const double coefficients[]{1.0, 2.0};
    const Polynomial original(coefficients, 1);
    Polynomial copy(original);

    copy.add(original);

    EXPECT_EQ(copy.degree(), 1);
    EXPECT_DOUBLE_EQ(copy.coeff(0), 2.0);
    EXPECT_DOUBLE_EQ(copy.coeff(1), 4.0);

    EXPECT_EQ(original.degree(), 1);
    EXPECT_DOUBLE_EQ(original.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(original.coeff(1), 2.0);
}

TEST(PolynomialTest, MoveConstructorEmptiesSource) {
    const double coefficients[]{1.0, 2.0};
    Polynomial source(coefficients, 1);

    const Polynomial destination(std::move(source));

    EXPECT_EQ(destination.degree(), 1);
    EXPECT_DOUBLE_EQ(destination.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(destination.coeff(1), 2.0);

    EXPECT_EQ(source.degree(), -1);
    EXPECT_DOUBLE_EQ(source.evaluate(2.0), 0.0);
}

TEST(PolynomialTest, CopyAssignmentReplacesData) {
    const double coefficients[]{1.0, 2.0};
    const double old_coefficients[]{9.0};
    const Polynomial source(coefficients, 1);
    Polynomial destination(old_coefficients, 0);

    destination = source;

    EXPECT_EQ(destination.degree(), 1);
    EXPECT_DOUBLE_EQ(destination.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(destination.coeff(1), 2.0);

    destination.add(source);

    EXPECT_DOUBLE_EQ(destination.coeff(0), 2.0);
    EXPECT_DOUBLE_EQ(destination.coeff(1), 4.0);
    EXPECT_DOUBLE_EQ(source.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(source.coeff(1), 2.0);
}

TEST(PolynomialTest, MoveAssignmentEmptiesSource) {
    const double coefficients[]{1.0, 2.0};
    const double old_coefficients[]{9.0};
    Polynomial source(coefficients, 1);
    Polynomial destination(old_coefficients, 0);

    destination = std::move(source);

    EXPECT_EQ(destination.degree(), 1);
    EXPECT_DOUBLE_EQ(destination.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(destination.coeff(1), 2.0);

    EXPECT_EQ(source.degree(), -1);
    EXPECT_DOUBLE_EQ(source.evaluate(2.0), 0.0);
}

TEST(PolynomialTest, SelfAssignmentPreservesData) {
    const double coefficients[]{1.0, 2.0};
    Polynomial polynomial(coefficients, 1);
    const Polynomial& same_object = polynomial;

    polynomial = same_object;

    EXPECT_EQ(polynomial.degree(), 1);
    EXPECT_DOUBLE_EQ(polynomial.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(polynomial.coeff(1), 2.0);
}

TEST(PolynomialAddTest, AddsPolynomialsAndZero) {
    const double first_coefficients[]{1.0, 2.0};
    const double second_coefficients[]{0.0, 1.0, 1.0};
    Polynomial first(first_coefficients, 1);
    const Polynomial second(second_coefficients, 2);

    first.add(second);

    EXPECT_EQ(first.degree(), 2);
    EXPECT_DOUBLE_EQ(first.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(first.coeff(1), 3.0);
    EXPECT_DOUBLE_EQ(first.coeff(2), 1.0);

    const Polynomial zero;
    first.add(zero);

    EXPECT_EQ(first.degree(), 2);
    EXPECT_DOUBLE_EQ(first.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(first.coeff(1), 3.0);
    EXPECT_DOUBLE_EQ(first.coeff(2), 1.0);
}

TEST(PolynomialMulTest, MultipliesPolynomialsAndZero) {
    const double first_coefficients[]{1.0, 2.0};
    const double second_coefficients[]{0.0, 1.0, 1.0};
    Polynomial first(first_coefficients, 1);
    const Polynomial second(second_coefficients, 2);

    first.mul(second);

    EXPECT_EQ(first.degree(), 3);
    EXPECT_DOUBLE_EQ(first.coeff(0), 0.0);
    EXPECT_DOUBLE_EQ(first.coeff(1), 1.0);
    EXPECT_DOUBLE_EQ(first.coeff(2), 3.0);
    EXPECT_DOUBLE_EQ(first.coeff(3), 2.0);

    const Polynomial zero;
    first.mul(zero);

    EXPECT_EQ(first.degree(), -1);
    EXPECT_DOUBLE_EQ(first.evaluate(2.0), 0.0);
}

TEST(PolynomialEvaluateTest, CalculatesValueAtPoint) {
    const double coefficients[]{1.0, 3.0, 1.0};
    const Polynomial polynomial(coefficients, 2);

    EXPECT_DOUBLE_EQ(polynomial.evaluate(2.0), 11.0);
    EXPECT_DOUBLE_EQ(polynomial.evaluate(0.0), 1.0);
}

TEST(PolynomialPowTest, RaisesToThirdPower) {
    const double coefficients[]{1.0, 1.0};
    const Polynomial polynomial(coefficients, 1);

    const Polynomial result = polynomial.pow(3);

    EXPECT_EQ(result.degree(), 3);
    EXPECT_DOUBLE_EQ(result.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(result.coeff(1), 3.0);
    EXPECT_DOUBLE_EQ(result.coeff(2), 3.0);
    EXPECT_DOUBLE_EQ(result.coeff(3), 1.0);

    EXPECT_EQ(polynomial.degree(), 1);
    EXPECT_DOUBLE_EQ(polynomial.coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(polynomial.coeff(1), 1.0);
}

TEST(PolynomialPowTest, ZeroPowerReturnsOne) {
    const double coefficients[]{1.0, 2.0};
    const Polynomial polynomial(coefficients, 1);
    const Polynomial zero;

    const Polynomial result = polynomial.pow(0);
    const Polynomial zero_result = zero.pow(0);

    EXPECT_EQ(result.degree(), 0);
    EXPECT_DOUBLE_EQ(result.coeff(0), 1.0);

    EXPECT_EQ(zero_result.degree(), 0);
    EXPECT_DOUBLE_EQ(zero_result.coeff(0), 1.0);
}

}  // namespace
}  // namespace lab02
