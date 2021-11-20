#include <cassert>

#include "SturmSequence.h"
#include "UnivariatePolynomial.h"

/*
  Test module for SturmSequence.cpp

  This check all public method including overloaded operator.
*/

void SturmSequenceTest()
{
  {
    // Test normal constructor and to_string()
    SturmSequence sturm_sequence = SturmSequence({1, 3, -2, 0, 1});
    sturm_sequence.to_string() = "Sturm ([1/1 3/1 -2/1 0/1 1/1] [3/1 -4/1 0/1 4/1] [-1/1 9/-4 1/1] [-16/27 -1/1] [-1/1])";
  }

  { // Test to_string_detail()
    SturmSequence sturm_sequence = SturmSequence({1, 3, -2, 0, 1});
    sturm_sequence.to_string_detail() = "SturmSequence (#UnivariatePolynomial{a[0]: #Rational{numerator: 1, denominator: 1}, a[1]: #Rational{numerator: 3, denominator: 1}, a[2]: #Rational{numerator: -2, denominator: 1}, a[3]: #Rational{numerator: 0, denominator: 1}, a[4]: #Rational{numerator: 1, denominator: 1}} #UnivariatePolynomial{a[0]: #Rational{numerator: 3, denominator: 1}, a[1]: #Rational{numerator: -4, denominator: 1}, a[2]: #Rational{numerator: 0, denominator: 1}, a[3]: #Rational{numerator: 4, denominator: 1}} #UnivariatePolynomial{a[0]: #Rational{numerator: -1, denominator: 1}, a[1]: #Rational{numerator: 9, denominator: -4}, a[2]: #Rational{numerator: 1, denominator: 1}} #UnivariatePolynomial{a[0]: #Rational{numerator: -16, denominator: 27}, a[1]: #Rational{numerator: -1, denominator: 1}} #UnivariatePolynomial{a[0]: #Rational{numerator: -1, denominator: 1}})";
  }

  {
    // Test sturm sequence with grown coefficient
    SturmSequence sturm_sequence = SturmSequence({3, 0, -1, 4, 0, 1});
    sturm_sequence.to_string() = "Sturm ([3/1 0/1 -1/1 4/1 0/1 1/1] [0/1 -2/1 12/1 0/1 5/1] [-15/8 0/1 3/8 -1/1] [75/271 728/813 -1/1] [33363/12274 1/1] [1/1])";
  }

  {
    // Test count_sign_change_at
    SturmSequence sturm_sequence = SturmSequence({1, 3, -2, 0, 1});
    assert(sturm_sequence.count_sign_change_at(-1) == 2);
  }

  {
    // Test count_sign_change_at_extended
    SturmSequence sturm_sequence = SturmSequence({1, 3, -2, 0, 1});
    assert(sturm_sequence.count_sign_change_at_extended(Infinity::NegativeInfinity) == 3);
  }

  {
    // Test count_real_roots_between
    SturmSequence sturm_sequence({-2, 0, 1});
    assert(sturm_sequence.count_real_roots_between(0, 2) == 1);
  }

  {
    // Test count_real_roots_between_extended
    SturmSequence sturm_sequence({-2, 0, 1});
    assert(sturm_sequence.count_real_roots_between_extended(Infinity::NegativeInfinity, Infinity::PositiveInfinity) == 2);
  }

  {
    // Test next_interval
    SturmSequence sturm_sequence({-2, 0, 1});
    assert(sturm_sequence.next_interval({1, 2}).first == 1);
    assert(sturm_sequence.next_interval({1, 2}).second == Rational(3, 2));
  }
}