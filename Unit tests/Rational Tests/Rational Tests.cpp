#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Rational.h"

TEST_CASE("Rational constructors",
          "[constructors], [special members]")
{
    SECTION("Default constructor creates zero")
    {
        auto r = Rational<>{};

        CHECK(r.getNumerator() == 0);
        CHECK(r.getDenominator() == 1);
    }

    SECTION("Single argument constructor creates an integer")
    {
        auto integer = -10;
        auto r = Rational<>{ integer };

        CHECK(r.getNumerator() == integer);
        CHECK(r.getDenominator() == 1);
    }

    SECTION("Constructor with numerator and denominator")
    {
        SECTION("Creates a reduced rational")
        {
            auto r = Rational<>{ 2, 4 };
            
            CHECK(r.getNumerator() == 1);
            CHECK(r.getDenominator() == 2);
        }

        SECTION("Keeps the sign in the numerator")
        {
            auto r = Rational<>{ 1, -3 };

            CHECK(r.getNumerator() == -1);
            CHECK(r.getDenominator() == 3);
        }

        SECTION("Creates a positive rational from two negative integers")
        {
            auto r = Rational<>{ -1, -4 };

            CHECK(r.getNumerator() == 1);
            CHECK(r.getDenominator() == 4);
        }

        SECTION("Throws exception when denominator is zero")
        {
            REQUIRE_THROWS_AS((Rational<>{ 1, 0 }),
                              std::invalid_argument);
        }
    }
}

TEST_CASE("Rational copy and move operations",
          "[copy], [move], [special members]")
{
    auto rhs = Rational<>{ 1, 2 };

    SECTION("Copy constructor")
    {
        auto lhs = rhs;

        CHECK(lhs.getNumerator() == rhs.getNumerator());
        CHECK(lhs.getDenominator() == rhs.getDenominator());
    }

    SECTION("Move constructor")
    {
        auto lhs = std::move(rhs);

        CHECK(lhs.getNumerator() == rhs.getNumerator());
        CHECK(lhs.getDenominator() == rhs.getDenominator());
    }

    SECTION("Assignment")
    {
        auto lhs = Rational<>{};

        SECTION("Copy assignment")
        {
            lhs = rhs;

            CHECK(lhs.getNumerator() == rhs.getNumerator());
            CHECK(lhs.getDenominator() == rhs.getDenominator());
        }

        SECTION("Move assignment")
        {
            lhs = std::move(rhs);

            CHECK(lhs.getNumerator() == rhs.getNumerator());
            CHECK(lhs.getDenominator() == rhs.getDenominator());
        }
    }
}

TEST_CASE("Rational conversions",
          "[conversions]")
{
    SECTION("Conversion to bool")
    {
        auto zero = Rational<>{ 0 };
        auto nonzero = Rational<>{ 1, 2 };

        SECTION("Converts zero to false")
        {
            CHECK_FALSE(zero);
            CHECK(!zero);
        }

        SECTION("Converts nonzero to true")
        {
            CHECK(nonzero);
            CHECK_FALSE(!nonzero);
        }
    }

    SECTION("Conversion to double")
    {
        using namespace Catch::literals;

        auto r = Rational<>{ 1, 2 };
        auto target = 0.5_a;

        auto d = static_cast<double>(r);

        REQUIRE(d == target);
    }
}

TEST_CASE("Rational equality tests compare reduced rationals",
    "[equality]")
{
    CHECK(Rational<>{ 1, 2 } == Rational<>{ 1, 2 });
    CHECK(Rational<>{ 2, 4 } == Rational<>{ 1, 2 });

    CHECK(Rational<>{ 1, 2 } != Rational<>{ 1, 3 });
    CHECK(Rational<>{ 1, 2 } != Rational<>{ -1, 2 });
    CHECK(Rational<>{ 2, 4 } != Rational<>{ 2, 6 });
}

TEST_CASE("Rational comparisons",
          "[comparison]")
{
    auto minusOneThird = Rational<>{ -1, 3 };
    auto zero = Rational<>{ 0 };
    auto oneThird = Rational<>{ 1, 3 };

    SECTION("operator<")
    {
        CHECK(minusOneThird < zero);
        CHECK(minusOneThird < oneThird);
        CHECK(zero < oneThird);
        CHECK_FALSE(oneThird < oneThird);
        CHECK_FALSE(oneThird < minusOneThird);
        CHECK_FALSE(zero < minusOneThird);
    }

    SECTION("operator<=")
    {
        CHECK(oneThird <= oneThird);
        CHECK(zero <= oneThird);
        CHECK(minusOneThird <= oneThird);
        CHECK_FALSE(oneThird <= zero);
    }

    SECTION("operator>")
    {
        CHECK(zero > minusOneThird);
        CHECK(oneThird > minusOneThird);
        CHECK(oneThird > zero);
        CHECK_FALSE(oneThird > oneThird);
        CHECK_FALSE(minusOneThird > zero);
    }

    SECTION("operator>=")
    {
        CHECK(oneThird >= oneThird);
        CHECK(oneThird >= zero);
        CHECK(zero >= minusOneThird);
        CHECK(oneThird >= minusOneThird);
        CHECK_FALSE(minusOneThird >= oneThird);
    }
}

TEST_CASE("Rational increment and decrement",
          "[increment], [decrement]")
{
    auto oneThird = Rational<>{ 1, 3 };

    SECTION("Increment adds one")
    {
        auto fourThirds = Rational<>{ 4, 3 };

        SECTION("Prefix increment")
        {
            REQUIRE(++oneThird == fourThirds);
        }

        SECTION("Postfix increment")
        {
            auto r = oneThird;

            REQUIRE(r++ == oneThird);
            REQUIRE(r == fourThirds);
        }
    }

    SECTION("Decrement subtracts one")
    {
        auto minusTwoThirds = Rational<>{ -2, 3 };

        SECTION("Prefix decrement")
        {
            REQUIRE(--oneThird == minusTwoThirds);
        }

        SECTION("Postfix decrement")
        {
            auto r = oneThird;

            REQUIRE(r-- == oneThird);
            REQUIRE(r == minusTwoThirds);
        }
    }
}

TEST_CASE("Rational negation and reciprocal",
          "[negation], [reciprocal]")
{
    SECTION("Negation keeps the sign in the numerator")
    {
        auto r = Rational<>{ 2, 3 };

        REQUIRE(-r == Rational<>{ -2, 3 });
    }

    SECTION("Negation of zero is zero")
    {
        const auto zero = Rational<>{ 0 };

        REQUIRE(-zero == zero);
    }

    SECTION("reciprocalOf keeps the sign in the numerator")
    {
        auto r = Rational<>{ -2, 3 };
        
        REQUIRE(reciprocalOf(r) == Rational<>{ -3, 2 });
    }

    SECTION("reciprocalOf zero throws exception")
    {
        REQUIRE_THROWS_AS(reciprocalOf(Rational<>{ 0 }),
                          std::logic_error);
    }

    SECTION("Reciprocal of one is one")
    {
        const auto one = Rational<>{ 1 };

        REQUIRE(reciprocalOf(one) == one);
    }
}

TEST_CASE("Rational arithmetic operations",
          "[arithmetic]")
{
    const auto zero = Rational<>{ 0 };
    const auto one = Rational<>{ 1 };

    SECTION("Binary operators")
    {
        SECTION("With neutral elements")
        {
            const auto r = Rational<>{ 1, 2 };

            CHECK((r + zero) == r);
            CHECK((zero + r) == r);
            CHECK((r - zero) == r);
            CHECK((zero - r) == -r);
            CHECK((r * one) == r);
            CHECK((one * r) == r);
            CHECK((r / one) == r);
            CHECK((one / r) == reciprocalOf(r));
        }

        SECTION("Keep rationals reduced with sign in numerator")
        {
            const auto minusOneThird = Rational<>{ -1, 3 };

            CHECK((Rational<>{ -2, 3 } + minusOneThird) == -one);
            CHECK((minusOneThird - Rational<>{ 2, 3 }) == -one);
            CHECK((Rational<>{ 3 } * minusOneThird) == -one);
            CHECK((minusOneThird / Rational<>{ 1, 3 }) == -one);
        }

        SECTION("Zero division throws exception")
        {
            REQUIRE_THROWS_AS(one / zero, std::logic_error);
        }
    }

    SECTION("Compound assignment operators")
    {
        SECTION("With neutral elements")
        {
            const auto oneThird = Rational<>{ 1, 3 };
            auto r = oneThird;

            REQUIRE((r += zero) == oneThird);
            REQUIRE((r -= zero) == oneThird);
            REQUIRE((r *= one) == oneThird);
            REQUIRE((r /= one) == oneThird);
        }

        SECTION("Keep rationals reduced with sign in numerator")
        {
            auto minusFourThirds = Rational<>{ -4, 3 };

            SECTION("Addition")
            {
                REQUIRE((minusFourThirds += Rational<>{ 1, 3 }) == -one);
            }

            SECTION("Subtraction")
            {
                REQUIRE((minusFourThirds -= Rational<>{ 2, 3 }) ==
                        Rational<>{ -2 });
            }

            SECTION("Multiplication")
            {
                REQUIRE((minusFourThirds *= Rational<>{ 3 }) ==
                        Rational<>{ -4 });
            }

            SECTION("Division")
            {
                REQUIRE((minusFourThirds /= Rational<>{ 1, 3 }) ==
                        Rational<>{ -4 });
            }
        }

        SECTION("Zero division throws exception")
        {
            auto r = one;

            REQUIRE_THROWS_AS(r /= zero, std::logic_error);
        }
    }
}
