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
	ReversiAction action1(0,0);
	ReversiAction action2(1,1);

	SECTION("Performing an action changes turn.")
	{
		state.performAction(action1);

		REQUIRE(Player::Black == state.whosTurn());

		state.performAction(action2);

		REQUIRE(Player::White == state.whosTurn());
	}

	SECTION("Performing actions places tiles")
	{
		int posX{0}, posY{0};
		ReversiAction(posX, posY);

		//TODO
	}
}
