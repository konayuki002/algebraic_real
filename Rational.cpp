#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/multiprecision/cpp_int.hpp> //install boost: sudo apt install libboost-dev

#include "Comparable.cpp"
#include "Fractional.cpp"
#include "Showable.cpp"

/*
  Class for rational number:

    p / q (p, q: integer)

  Defined along with https://ufcpp.net/study/math/set/rational/
*/
class Rational : public Showable<Rational>, public Comparable<Rational>, public Fractional<Rational>
{
private:
  boost::multiprecision::cpp_int numerator, denominator;
  Rational reduce()
  {
    Rational r_not_reduced(*this);
    auto a = numerator, b = denominator;
    while (b != 0)
    {
      auto tmp_a = a;
      a = b;
      b = tmp_a % b;
    }
    numerator /= a;
    denominator /= a;
    return r_not_reduced;
  }
  int sign(boost::multiprecision::cpp_int k) const
  {
    if (k == 0)
      return 0;
    if (k > 0)
      return +1;
    return -1;
  }

public:
  Rational() : Rational(0){};

  Rational(const boost::multiprecision::cpp_int numerator, const boost::multiprecision::cpp_int denominator) : numerator(numerator)
  {
    if (denominator == 0)
      throw std::domain_error("Zero denominator Exception");

    this->denominator = denominator;
    this->reduce();
  };

  // Rational({1, 2})
  Rational(const std::initializer_list<int> list)
  {
    if (list.size() != 2)
      throw std::invalid_argument("Initializer arguments are too many");
    if (list.begin()[1] == 0)
      throw std::domain_error("Zero denominator Exception");

    numerator = list.begin()[0];
    denominator = list.begin()[1];

    this->reduce();
  }

  Rational(const int integer) : numerator(integer), denominator(1){};

  std::string to_string() const
  {
    return numerator.str() + "/" + denominator.str();
  }

  std::string to_string_detail() const
  {
    return "#Rational{numerator: " + numerator.str() + ", denominator: " + denominator.str() + "}";
  }

  bool less_than(const Rational &r) const
  {
    return (numerator * r.denominator - denominator * r.numerator) * (denominator * r.denominator) < 0;
  }

  Rational &add(const Rational &r)
  {
    this->numerator = this->numerator * r.denominator + this->denominator * r.numerator;
    this->denominator = this->denominator * r.denominator;
    reduce();
    return *this;
  };

  Rational &multiply(const Rational &r)
  {
    this->numerator = this->numerator * r.numerator;
    this->denominator = this->denominator * r.denominator;
    reduce();
    return *this;
  };

  Rational negate() const
  {
    return Rational(-numerator, denominator);
  }

  Rational inverse() const
  {
    if (denominator == 0)
      throw std::domain_error("Zero inverse error: " + to_string());
    return Rational(denominator, numerator);
  }

  int sign() const
  {
    if (sign(numerator) * sign(denominator) == 1) // when same sign
    {
      return +1;
    }
    else if (sign(numerator) * sign(denominator) == -1)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
};
