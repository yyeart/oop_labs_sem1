#include <iostream>
#include <utility>

#include "lab02/polynomial.hpp"

namespace {

void PrintPolynomial(const char* label, const lab02::Polynomial& polynomial) {
    std::cout << label;
    polynomial.print(std::cout);
    std::cout << "\n";
}

}  // namespace

int main() {
    const double a_coeffs[]{1.0, 2.0};
    const double b_coeffs[]{0.0, 1.0, 1.0};

    const lab02::Polynomial a(a_coeffs, 1);
    const lab02::Polynomial b(b_coeffs, 2);

    PrintPolynomial("a = ", a);
    PrintPolynomial("b = ", b);

    lab02::Polynomial sum(a);
    sum.add(b);
    PrintPolynomial("a + b = ", sum);

    lab02::Polynomial product(a);
    product.mul(b);
    PrintPolynomial("a * b = ", product);
    std::cout << "(a + b)(2) = " << sum.evaluate(2.0) << "\n";

    lab02::Polynomial copy(a);
    PrintPolynomial("Copy a = ", copy);

    lab02::Polynomial moved(std::move(copy));
    PrintPolynomial("Moved a = ", moved);

    lab02::Polynomial assigned;
    assigned = b;
    PrintPolynomial("After assignment b = ", assigned);

    const double base_coeffs[]{1.0, 1.0};
    const lab02::Polynomial base(base_coeffs, 1);
    PrintPolynomial("(1 + x)^3 = ", base.pow(3));
    PrintPolynomial("(1 + x)^0 = ", base.pow(0));

    return 0;
}
