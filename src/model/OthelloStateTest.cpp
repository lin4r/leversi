/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of othello-assignment.
 * 
 * othello-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Unit tests for OthelloState.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "OthelloState.hpp"

using namespace othello;

TEST_CASE("Default values", "[OthelloState, defaultValues]")
{
	OthelloState state;

	SECTION("Black player starts.")
	{
		REQUIRE(Player::Black == state.whosTurn());
	}

	SECTION("Board has eight rows")
	{
		REQUIRE(8 == state.get_boardRows());
	}

	SECTION("Board has eight columns")
	{
		REQUIRE(8 == state.get_boardColumns());
	}

	SECTION("Verify that the initial state is according to game rules.")
	{
		auto initial = OthelloState::initialState();

		REQUIRE(Tile::White == initial.inspectTile(Position(3,3)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(3,4)));
		REQUIRE(Tile::White == initial.inspectTile(Position(4,4)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(4,3)));
	}
}

TEST_CASE("Verify Game over.")
{
	OthelloState state;

	SECTION("Game Over after two pass")
	{
		REQUIRE(! state.gameOver());
		state.updateGameStatus(true);
		REQUIRE(! state.gameOver());
		state.updateGameStatus(true);
		REQUIRE(state.gameOver());
	}

	SECTION("Not game over if placement ocurrs between two pass.")
	{
		state.updateGameStatus(true);
		state.updateGameStatus(false);
		REQUIRE(! state.gameOver());
		state.updateGameStatus(true);
		REQUIRE(! state.gameOver());
	}

	SECTION("Still game over if i make an (erroneus) placement after two passes")
	{
		state.updateGameStatus(true);
		state.updateGameStatus(true);
		state.updateGameStatus(false);
		REQUIRE(state.gameOver());
	}
}
