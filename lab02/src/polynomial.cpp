#include "lab02/polynomial.hpp"

#include <utility>

namespace lab02 {

Polynomial::Polynomial() = default;

Polynomial::Polynomial(const double* coeffs, int degree) {
    if (degree == -1) {
        return;
    }

    while (degree >= 0 && coeffs[degree] == 0.0) {
        --degree;
    }

    if (degree == -1) {
        return;
    }

    const std::size_t count{static_cast<std::size_t>(degree) + 1};

    coeffs_ = new double[count];
    degree_ = degree;

    for (std::size_t i = 0; i < count; ++i) {
        coeffs_[i] = coeffs[i];
    }
}

Polynomial::Polynomial(const Polynomial& other) : Polynomial(other.coeffs_, other.degree_) {}

Polynomial::Polynomial(Polynomial&& other) : coeffs_(other.coeffs_), degree_(other.degree_) {
    other.coeffs_ = nullptr;
    other.degree_ = -1;
}

void Polynomial::swap(Polynomial& other) {
    std::swap(coeffs_, other.coeffs_);
    std::swap(degree_, other.degree_);
}

Polynomial& Polynomial::operator=(Polynomial other) {
    swap(other);
    return *this;
}

Polynomial::~Polynomial() {
    delete[] coeffs_;
}

int Polynomial::degree() const {
    return degree_;
}

double Polynomial::coeff(std::size_t index) const {
    if (degree_ < 0.0 || index > static_cast<std::size_t>(degree_)) {
        return 0.0;
    }

    return coeffs_[index];
}

void Polynomial::trim() {
    int new_degree{degree_};

    while (new_degree >= 0 && coeffs_[new_degree] == 0.0) {
        --new_degree;
    }

    if (new_degree == degree_) {
        return;
    }

    Polynomial normalized(coeffs_, new_degree);
    swap(normalized);
}

void Polynomial::add(const Polynomial& other) {
    int result_degree;
    if (degree_ > other.degree_) {
        result_degree = degree_;
    } else {
        result_degree = other.degree_;
    }

    if (result_degree == -1) {
        return;
    }

    Polynomial result;
    const std::size_t count{static_cast<std::size_t>(result_degree) + 1};

    result.coeffs_ = new double[count];
    result.degree_ = result_degree;

    for (std::size_t i = 0; i < count; ++i) {
        result.coeffs_[i] = coeff(i) + other.coeff(i);
    }

    result.trim();
    swap(result);
}

void Polynomial::mul(const Polynomial& other) {
    if (degree_ == -1 || other.degree_ == -1) {
        Polynomial zero;
        swap(zero);
        return;
    }

    Polynomial result;

    result.degree_ = degree_ + other.degree_;
    result.coeffs_ = new double[static_cast<std::size_t>(result.degree_) + 1]{};

    const std::size_t this_count{static_cast<std::size_t>(degree_) + 1};
    const std::size_t other_count{static_cast<std::size_t>(other.degree_) + 1};

    for (std::size_t i = 0; i < this_count; ++i) {
        for (std::size_t j = 0; j < other_count; ++j) {
            result.coeffs_[i + j] += coeff(i) * other.coeff(j);
        }
    }

    result.trim();
    swap(result);
}

double Polynomial::evaluate(double x) const {
    double result{};

    for (int i = degree_; i >= 0; --i) {
        result = result * x + coeffs_[i];
    }

    return result;
}

Polynomial Polynomial::pow(std::size_t n) const {
    const double arr[]{1.0};
    Polynomial result(arr, 0);

    for (std::size_t i = 0; i < n; ++i) {
        result.mul(*this);
    }

    return result;
}

void Polynomial::print(std::ostream& out) const {
    const std::size_t count{static_cast<std::size_t>(degree_) + 1};
    bool is_first = true;

    for (std::size_t i = 0; i < count; ++i) {
        const double value{coeffs_[i]};

        if (value == 0.0) {
            continue;
        }

        const bool is_negative = value < 0.0;
        double module;
        if (is_negative) {
            module = -value;
        } else {
            module = value;
        }

        if (!is_first) {
            out << (is_negative ? " - " : " + ");
        } else if (is_negative) {
            out << "-";
        }

        if (i == 0 || module != 1.0) {
            out << module;
        }

        if (i > 0) {
            out << "x";

            if (i > 1) {
                out << "^" << i;
            }
        }

        is_first = false;
    }

    if (is_first) {
        out << '0';
    }
}

}  // namespace lab02
