#pragma once

#include <cstddef>
#include <ostream>

namespace lab02 {

class Polynomial {
    double* coeffs_{nullptr};
    int degree_{-1};

public:
    Polynomial();
    Polynomial(const double* coeffs, int degree);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other);
    Polynomial& operator=(Polynomial other);
    ~Polynomial();

    void swap(Polynomial& other);
    void trim();

    void add(const Polynomial& other);
    void mul(const Polynomial& other);
    double evaluate(double x) const;
    void print(std::ostream& out) const;
    Polynomial pow(std::size_t n) const;

    int degree() const;
    double coeff(std::size_t index) const;
};

}  // namespace lab02
