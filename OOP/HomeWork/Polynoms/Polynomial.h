#ifndef POLYNOMS_POLYNOMIAL_H
#define POLYNOMS_POLYNOMIAL_H

#include <cmath>
#include <algorithm>
#include <iostream>

template <typename F>
class Polynomial {

public:

    /***
     * Create a polynom with the given coefficients
     * @param coefficients Coefficients from the field sorted in increasing degree
     * @param degree The degree of the last coefficient
     */
    Polynomial(F coefficients[], unsigned degree)
    : degree(degree)
    , coefficients(nullptr) {
        this->coefficients = new F[degree+1];

        for (unsigned i = 0; i <= degree; ++i) {
            this->coefficients[i] = coefficients[i];
        }
    }

    /***
     * Create a polynom with only one coefficients before the highest degree
     * @param coefficient Coefficient of the highest degree
     * @param degree Highest degree
     */
    Polynomial(F coefficient, unsigned degree)
    : degree(degree)
    , coefficients(nullptr) {
        this->coefficients = new F[degree+1];

        for (unsigned i = 0; i < degree; ++i) {
            this->coefficients[i] = (F)0;
        }

        this->coefficients[degree] = coefficient;
    }

    Polynomial(const Polynomial<F>& other)
    : Polynomial(other.coefficients, other.degree) {}

    ~Polynomial() {
        delete[] coefficients;
    }

    Polynomial<F>& operator=(const Polynomial<F>& other) {
        if(this != &other) {
            delete[] coefficients;
            F* newCoefficients = new F[other.degree+1];

            for (unsigned i = 0; i <= other.degree; ++i) {
                newCoefficients[i] = other.coefficients[i];
            }

            delete[] coefficients;
            coefficients = newCoefficients;
            degree = other.degree;
        }
    }

    /// Equality
    bool operator==(const Polynomial<F>& other) const {
        if(degree != other.degree) {
            return false;
        }

        for (unsigned i = 0; i <= degree; ++i) {
            if(coefficients[i] != other.coefficients[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Polynomial<F>& other) const {
        return !(*this == other);
    }

    /// Comparison
    bool operator<(const Polynomial<F>& other) const {
        return degree < other.degree;
    }


    bool operator>=(const Polynomial<F>& other) const {
        return !(*this < other);
    }

    bool operator>(const Polynomial<F>& other) const {
        return degree > other.degree;
    }

    bool operator<=(const Polynomial<F>& other) const {
        return !(*this > other);
    }

    F operator[](unsigned index) const {
        if(index > degree) {
            return (F)0;
        }

        return coefficients[index];
    }

    /// Binary operators with coefficients
    Polynomial<F> operator*(F coefficient) const {
        F* newCoefficients = getNewCoefficients(degree);

        for (unsigned i = 0; i <= degree; ++i) {
            newCoefficients[i] = coefficients[i] * coefficient;
        }

        Polynomial<F> newPoly(newCoefficients, degree);

        delete[] newCoefficients;
        return newPoly;
    }

    Polynomial<F> operator/(F coefficient) const {
        return (*this) * ((F)1/coefficient);
    }

    /// Binary operators with other polynomials
    Polynomial<F> operator+(const Polynomial<F>& other) const {
        unsigned highestDegree = std::max(degree, other.degree);
        F* newCoefficients = getNewCoefficients(highestDegree);

        for (unsigned i = 0; i <= highestDegree; ++i) {
            newCoefficients[i] = (*this)[i] + other[i];
        }

        Polynomial<F> newPoly(newCoefficients, highestDegree);

        delete[] newCoefficients;
        return newPoly;
    }

    Polynomial<F> operator-(const Polynomial<F>& other) const {
        return (*this) + (other * (F)(-1));
    }

    Polynomial<F> operator*(const Polynomial<F>& other) const {
        unsigned highestDegree = degree + other.degree;
        F* newCoefficients = getNewCoefficients(highestDegree);

        for (unsigned i = 0; i <= degree; ++i) {
            if((*this)[i] == (F)0) {
                continue;
            }

            for (unsigned j = 0; j <= other.degree; ++j) {
                if(other[j] == (F)0) {
                    continue;
                }

                newCoefficients[i+j] += (*this)[i] * other[j];
            }
        }

        return getNewPoly(newCoefficients, highestDegree);
    }

    Polynomial<F> operator/(const Polynomial<F>& other) const {
        if(other.degree > degree){
            return Polynomial<F>((F)0, 0);
        }

        unsigned highestDegree = degree - other.degree;
        F* newCoefficients = getNewCoefficients(highestDegree);

        Polynomial<F> curr = *this;

        while(curr.degree >= other.degree) {
            unsigned newDegree = curr.degree - other.degree;
            F coefficient = curr[degree] / other[other.degree];
            newCoefficients[newDegree] = coefficient;
            curr -= other * Polynomial<F>(coefficient, newDegree);
        }

        return getNewPoly(newCoefficients, highestDegree);
    }

    Polynomial<F>& operator+=(const Polynomial<F>& other) {
        *this = (*this) + other;
        return *this;
    }

    Polynomial<F>& operator-=(const Polynomial<F>& other) {
        Polynomial<F> res = (*this) - other;
        *this = res;
        return *this;
    }

    Polynomial<F>& operator*=(const Polynomial<F>& other) {
        *this = (*this) * other;
        return *this;
    }

    /// Calculating with X
    F operator()(F x) const {
        F result = (F)0;

        for (unsigned i = 0; i <= degree; ++i) {
            F curr = coefficients[i];

            for (int j = 0; j < i; ++j) {
                curr *= x;
            }

            result += curr;
        }

        return result;
    }

    /// Calculating integral a/b
    F operator()(F a, F b) const {
        Polynomial<F> integrated = this->integrate();
        return integrated(b) - integrated(a);
    }

    /// Incrementing (integrating)
    F& operator++() {
        (*this) = integrate();
        return *this;
    }

    F operator++(int) {
        Polynomial<F> old(*this);
        (*this) = integrate();
        return old;
    }

    /// Decrementing (differentiating)
    F& operator--() {
        (*this) = differentiate();
        return *this;
    }

    F operator--(int) {
        Polynomial<F> old(*this);
        (*this) = differentiate();
        return old;
    }

    /// Casting to unsigned
    explicit operator unsigned() const {
        return degree;
    }


    /// Casting to bool
    operator bool() const {
        for (unsigned i = 0; i <= degree; ++i) {
            if(coefficients[i] != (F)0) {
                return false;
            }
        }

        return true;
    }

    bool operator!() const {
        return !((bool)(*this));
    }

private:
    F *coefficients;
    unsigned degree;

    Polynomial<F> integrate() const {
        F* newCoefficients = getNewCoefficients(degree+1);

        for (int i = 1; i < degree + 2; ++i) {
            newCoefficients[i] = coefficients[i-1] * ((F)1 / (F)i);
        }

        return getNewPoly(newCoefficients, degree+1);
    }

    Polynomial<F> differentiate() {
        F* newCoefficients = getNewCoefficients(degree-1);

        for (int i = 1; i <= degree; ++i) {
            newCoefficients[i-1] = coefficients[i] * (F)i;
        }

        Polynomial<F> newPoly(newCoefficients, degree-1);

        delete[] newCoefficients;
        return newPoly;
    }

    F* getNewCoefficients(unsigned degree) const {
        F *newCoefficients = new F[degree+1];
        for (unsigned i = 0; i <= degree; ++i) {
            newCoefficients[i] = (F)0;
        }

        return newCoefficients;
    }

    Polynomial<F> getNewPoly(F* coefficients, unsigned degree) const {
        Polynomial<F> newPoly(coefficients, degree);

        delete[] coefficients;
        return newPoly;
    }
};

template <typename F>
std::ostream& operator<<(std::ostream& out, Polynomial<F> polynomial) {

    unsigned degree = (unsigned)polynomial;

    for (unsigned i = 0; i <= degree; ++i) {
        if(polynomial[i] == (F)0) {
            continue;
        }

        out << polynomial[i];
        if(i > 0) {
            out << "x^" << i;
        }

        if(i < degree) {
            out << " + ";
        }
    }

    out << std::endl;
    return out;
}


#endif //POLYNOMS_POLYNOMIAL_H
