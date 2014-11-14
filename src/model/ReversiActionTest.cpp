/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of reversi-assignment.
 * 
 * reversi-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Unit tests for ReversiAction.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "ReversiAction.hpp"

using namespace reversi;

TEST_CASE("Test action string conversion.", "[ReversiAction, actionString]")
{
	ReversiAction pass(Position(1,2),true);
	ReversiAction put(Position(3,4));

	SECTION ("Verify pass format")
	{
		REQUIRE("pass" == pass.actionString());
	}

	SECTION ("Verify move format")
	{
		REQUIRE("(3,4)" == put.actionString());
	}
}

TEST_CASE("Test action string parseing", "[ReversiAction, actionString]")
{
	using namespace std;

	SECTION("Throws if misspelled.")
	{
		REQUIRE_THROWS_AS(ReversiAction("pards")
			, actionstring_syntax_exception);
	}

	SECTION("Throws if we add tail")
	{
		REQUIRE_THROWS(ReversiAction("pardsasdf"));
	}

	SECTION("Throws if we add head")
	{
		REQUIRE_THROWS(ReversiAction("asdfpass"));
	}

	SECTION("Can parse pass")
	{
		ReversiAction pass("pass");

		REQUIRE(pass.get_pass());
	}

	SECTION("Can parse a non-pass")
	{
		ReversiAction nonPass1("(3,4)");
		Position excpected = {3,4};

		REQUIRE(excpected == nonPass1.get_position());

		/* TODO Robuster matching allowing this and whitespaces in the
		 * parantheses will be implemented once gcc supports regex (4.9)
		 */
//		/* Obviusly not a real Othello position. I want to test more than one
//		 * digit numbers.
//		 */
//		ReversiAction nonPass2("(12,1337)");
//
//		REQUIRE(12 == nonPass2.get_row());
//		REQUIRE(1337 == nonPass2.get_column());
	}
}
