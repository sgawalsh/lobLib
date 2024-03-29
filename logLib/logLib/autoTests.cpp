#include "pch.h"
#include <windows.h>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

unsigned int Factorial(unsigned int number) {
	return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("first Test")
{
	REQUIRE(1 == 1);
}

TEST_CASE("2nd  Test")
{
	REQUIRE(1 == 0);
}