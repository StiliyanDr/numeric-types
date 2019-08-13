#include <stdexcept>
#include <assert.h>

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
