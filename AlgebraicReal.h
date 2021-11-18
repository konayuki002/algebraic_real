#pragma once

#include <stdexcept>

#include "Comparable.cpp"
#include "Fractional.cpp"
#include "Rational.cpp"
#include "Showable.cpp"
#include "UnivariatePolynomial.h"

/*
  Class for algebraic number:

  Defined along with https://ufcpp.net/study/math/set/rational/
*/
class AlgebraicReal : public Showable<AlgebraicReal>, public Comparable<AlgebraicReal>, public Fractional<AlgebraicReal>
{
private:
  bool is_rational;

  Rational r;

  UnivariatePolynomial defining_polynomial;

  // (r1, r2]
  std::pair<Rational, Rational> interval;

public:
  static AlgebraicReal make_AlgebraicReal(const UnivariatePolynomial &defining_polynomial, const std::pair<Rational, Rational> &interval);

  AlgebraicReal();
  // Rational initialization
  AlgebraicReal(const Rational &r);
  AlgebraicReal(const UnivariatePolynomial &defining_polynomial, const std::pair<Rational, Rational> &interval);

  std::string to_string() const;
  std::string to_string_detail() const;

  bool less_than(const AlgebraicReal &a) const;

  bool equal_to(const AlgebraicReal &a) const;

  AlgebraicReal &add(const AlgebraicReal &a);
  AlgebraicReal &multiply(const AlgebraicReal &a);
  AlgebraicReal negate() const;

  AlgebraicReal inverse() const;

  bool get_is_rational() const;
  Rational get_rational() const;
  UnivariatePolynomial get_defining_polynomial() const;
  std::pair<Rational, Rational> get_isolating_interval() const;
  std::vector<UnivariatePolynomial> sturm_sequence() const;
  // name differ from source (interval())
  std::pair<Rational, Rational> next_interval(const std::pair<Rational, Rational> old_interval) const;
};