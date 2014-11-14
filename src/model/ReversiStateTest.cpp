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
 * Unit tests for ReversiState.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "ReversiState.hpp"

using namespace reversi;

TEST_CASE("Default values", "[ReversiState, defaultValues]")
{
	ReversiState state;

	SECTION("White player starts.")
	{
		REQUIRE(Player::White == state.get_turn());
	}

	SECTION("Board has eight rows")
	{
		REQUIRE(8 == state.get_boardRows());
	}

	SECTION("Board has eight columns")
	{
		REQUIRE(8 == state.get_boardColumns());
	}
}
