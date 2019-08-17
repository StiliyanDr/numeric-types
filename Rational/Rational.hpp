#include <stdexcept>
#include <assert.h>

template <class Integer>
inline constexpr bool
operator!=(const Rational<Integer>& lhs,
	       const Rational<Integer>& rhs) noexcept
{
	return !(lhs == rhs);
}

template <class Integer>
constexpr bool
operator==(const Rational<Integer>& lhs,
	       const Rational<Integer>& rhs) noexcept
{
	return lhs.getNumerator() == rhs.getNumerator() &&
		   lhs.getDenominator() == rhs.getDenominator();
}

template <class Integer>
inline constexpr bool
operator>(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept
{
	return rhs < lhs;
}

template <class Integer>
inline constexpr bool
operator<=(const Rational<Integer>& lhs,
	       const Rational<Integer>& rhs) noexcept
{
	return !(rhs < lhs);
}

template <class Integer>
inline constexpr bool
operator>=(const Rational<Integer>& lhs,
	       const Rational<Integer>& rhs) noexcept
{
	return !(lhs < rhs);
}

template <class Integer>
constexpr bool
operator<(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept
{
	return (lhs.getNumerator() * rhs.getDenominator()) <
		   (lhs.getDenominator() * rhs.getNumerator());
}

template <class Integer>
constexpr const Rational<Integer>
operator+(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept
{
	auto result = lhs;
	result += rhs;

	return result;
}

template <class Integer>
constexpr Rational<Integer>&
Rational<Integer>::operator+=(const Rational& rhs) noexcept
{
	auto numerator = this->numerator * rhs.denominator +
		             this->denominator * rhs.numerator;
	auto denominator = this->denominator * rhs.denominator;
	*this = Rational{ numerator, denominator };

	return *this;
}

template <class Integer>
constexpr const Rational<Integer>
operator-(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept
{
	auto result = lhs;
	result -= rhs;

	return result;
}

template <class Integer>
inline constexpr Rational<Integer>&
Rational<Integer>::operator-=(const Rational& rhs) noexcept
{
	*this += -rhs;

	return *this;
}

template <class Integer>
constexpr const Rational<Integer>
operator-(const Rational<Integer>& r) noexcept
{
	return Rational<Integer>{ Integer{ -1 } } * r;
}

template <class Integer>
constexpr const Rational<Integer>
operator*(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs) noexcept
{
	auto result = lhs;
	result *= rhs;

	return result;
}

template <class Integer>
constexpr Rational<Integer>&
Rational<Integer>::operator*=(const Rational& rhs) noexcept
{
	auto numerator = this->numerator * rhs.numerator;
	auto denominator = this->denominator * rhs.denominator;
	
	*this = Rational{ numerator, denominator };

	return *this;
}

template <class Integer>
constexpr const Rational<Integer>
operator/(const Rational<Integer>& lhs,
	      const Rational<Integer>& rhs)
{
	auto result = lhs;
	result /= rhs;

	return result;
}

template <class Integer>
constexpr Rational<Integer>&
Rational<Integer>::operator/=(const Rational& rhs)
{
	if (!isZero(rhs.numerator))
	{
		*this *= reciprocalOf(rhs);

		return *this;
	}
	else
	{
		throw std::logic_error{ "Zero division!" };
	}
}

template <class Integer>
constexpr const Rational<Integer>
reciprocalOf(const Rational<Integer>& r)
{
	if (r != Rational<Integer>{ Integer{ 0 } })
	{
		return Rational<Integer>{ r.getDenominator(),
						          r.getNumerator() };
	}
	else
	{
		throw std::logic_error{ "Zero has no reciprocal!" };
	}
}

template <class Integer>
inline constexpr Rational<Integer>::Rational() noexcept :
	numerator{ 0 },
	denominator{ 1 }
{
}

template <class Integer>
constexpr Rational<Integer>::Rational(Integer numerator,
	                                  Integer denominator) :
	numerator{ numerator },
	denominator{ denominator }
{
	verifyDenominatorIsNonZero();
	normalise();
	moveSignInNumerator();
}

template <class Integer>
constexpr void
Rational<Integer>::verifyDenominatorIsNonZero() const
{
	if (isZero(denominator))
	{
		throw std::invalid_argument{ "Denominator must not be zero!" };
	}
}

template <class Integer>
inline constexpr bool
Rational<Integer>::isZero(Integer i) noexcept
{
	return i == Integer{ 0 };
}

template <class Integer>
constexpr void Rational<Integer>::normalise() noexcept
{
	assert(!isZero(denominator));

	auto gcd = gcdOf(numerator, denominator);
	assert(!isZero(gcd));

	numerator /= gcd;
	denominator /= gcd;
}

template <class Integer>
constexpr Integer
Rational<Integer>::gcdOf(Integer a, Integer b) noexcept
{
	while (!isZero(b))
	{
		auto c = b;
	    b = a % b;
	    a = c;
	}

	return a;
}

template <class Integer>
constexpr void
Rational<Integer>::moveSignInNumerator() noexcept
{
	if (denominator < Integer{ 0 })
	{
		auto minusOne = Integer{ -1 };
		denominator *= minusOne;
		numerator *= minusOne;
	}
}

template <class Integer>
inline constexpr bool
Rational<Integer>::operator!() const noexcept
{
	return !static_cast<bool>(*this);
}

template <class Integer>
inline constexpr
Rational<Integer>::operator bool() const noexcept
{
	return !isZero(numerator);
}

template <class Integer>
inline constexpr
Rational<Integer>::operator double() const noexcept
{
	assert(!isZero(denominator));

	return static_cast<double>(numerator) /
		   static_cast<double>(denominator);
}

template <class Integer>
inline constexpr Integer
Rational<Integer>::getNumerator() const noexcept
{
	return numerator;
}

template <class Integer>
inline constexpr Integer
Rational<Integer>::getDenominator() const noexcept
{
	return denominator;
}
