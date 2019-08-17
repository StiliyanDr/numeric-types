#ifndef __RATIONAL_HEADER_INCLUDED__
#define __RATIONAL_HEADER_INCLUDED__

#include <type_traits>

template <class Integer = int>
class Rational
{
	static_assert(std::is_integral_v<Integer>,
		          "Integer must be an integral type!");

public:
	constexpr Rational() noexcept;
	constexpr Rational(Integer numerator,
		               Integer denominator = Integer{ 1 });

	constexpr Rational& operator+=(const Rational& rhs) noexcept;
	constexpr Rational& operator-=(const Rational& rhs) noexcept;
	constexpr Rational& operator*=(const Rational& rhs) noexcept;
	constexpr Rational& operator/=(const Rational& rhs);

	explicit constexpr operator double() const noexcept;

	constexpr Integer getNumerator() const noexcept;
	constexpr Integer getDenominator() const noexcept;

private:
	static constexpr bool isZero(Integer i) noexcept;
	static constexpr Integer gcdOf(Integer a,
		                           Integer b) noexcept;

private:
	constexpr void verifyDenominatorIsNonZero() const;
	constexpr void normalise() noexcept;
	constexpr void moveSignInNumerator() noexcept;

private:
	Integer numerator;
	Integer denominator;
};

template <class Integer>
constexpr const Rational<Integer>
operator+(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr const Rational<Integer>
operator-(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr const Rational<Integer>
operator*(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr const Rational<Integer>
operator/(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs);

template <class Integer>
constexpr const Rational<Integer>
operator-(const Rational<Integer>& r) noexcept;
template <class Integer>
constexpr const Rational<Integer>
reciprocalOf(const Rational<Integer>& r);

template <class Integer>
constexpr bool operator==(const Rational<Integer>& lhs,
	                      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr bool operator!=(const Rational<Integer>& lhs,
	                      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr bool operator<(const Rational<Integer>& lhs,
	                     const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr bool operator>(const Rational<Integer>& lhs,
	                     const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr bool operator<=(const Rational<Integer>& lhs,
	                      const Rational<Integer>& rhs) noexcept;
template <class Integer>
constexpr bool operator>=(const Rational<Integer>& lhs,
	                      const Rational<Integer>& rhs) noexcept;

#include "Rational.hpp"

#endif //__RATIONAL_HEADER_INCLUDED__