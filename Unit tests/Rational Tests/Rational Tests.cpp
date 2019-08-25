#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Rational.h"

TEST_CASE("Rational constructors",
          "[constructors], [special members]")
{
    SECTION("Default constructor creates zero")
    {
        auto r = Rational<>{};

        REQUIRE(r.getNumerator() == 0);
        REQUIRE(r.getDenominator() == 1);
    }

    SECTION("Single argument constructor creates an integer")
    {
        auto integer = -10;
        auto r = Rational<>{ integer };

        REQUIRE(r.getNumerator() == integer);
        REQUIRE(r.getDenominator() == 1);
    }

    SECTION("Constructor with numerator and denominator")
    {
        SECTION("Creates a reduced rational")
        {
            auto r = Rational<>{ 2, 4 };
            
            REQUIRE(r.getNumerator() == 1);
            REQUIRE(r.getDenominator() == 2);
        }

        SECTION("Keeps the sign in the numerator")
        {
            auto r = Rational<>{ 1, -3 };

            REQUIRE(r.getNumerator() == -1);
            REQUIRE(r.getDenominator() == 3);
        }

        SECTION("Creates a positive rational from two negative integers")
        {
            auto r = Rational<>{ -1, -4 };

            REQUIRE(r.getNumerator() == 1);
            REQUIRE(r.getDenominator() == 4);
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

        REQUIRE(lhs.getNumerator() == rhs.getNumerator());
        REQUIRE(lhs.getDenominator() == rhs.getDenominator());
    }

    SECTION("Move constructor")
    {
        auto lhs = std::move(rhs);

        REQUIRE(lhs.getNumerator() == rhs.getNumerator());
        REQUIRE(lhs.getDenominator() == rhs.getDenominator());
    }

    SECTION("Assignment")
    {
        auto lhs = Rational<>{};

        SECTION("Copy assignment")
        {
            lhs = rhs;

            REQUIRE(lhs.getNumerator() == rhs.getNumerator());
            REQUIRE(lhs.getDenominator() == rhs.getDenominator());
        }

        SECTION("Move assignment")
        {
            lhs = std::move(rhs);

            REQUIRE(lhs.getNumerator() == rhs.getNumerator());
            REQUIRE(lhs.getDenominator() == rhs.getDenominator());
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
            REQUIRE_FALSE(zero);
            REQUIRE(!zero);
        }

        SECTION("Converts nonzero to true")
        {
            REQUIRE(nonzero);
            REQUIRE_FALSE(!nonzero);
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
