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
		REQUIRE(Player::White == state.whosTurn());
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

TEST_CASE("Test modifications of the state", "[ReversiState,], actions")
{
	ReversiState state;

	Position pos1(0,0), pos2(1,1);
	ReversiAction action1(pos1);
	ReversiAction action2(pos2);

	SECTION("Performing an action changes turn.")
	{
		state.performAction(action1);

		REQUIRE(Player::Black == state.whosTurn());

		state.performAction(action2);

		REQUIRE(Player::White == state.whosTurn());
	}

	SECTION("Performing actions places tiles")
	{
		/* The tile is empty before placement. */
//		REQUIRE(state.inspectTile(pos))
	}
}
