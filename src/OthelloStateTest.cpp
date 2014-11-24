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

#include <vector>

using namespace othello;
using std::vector;

TEST_CASE("Default values", "[OthelloState, defaultValues]")
{
	OthelloState state;

	SECTION("Black player starts.")
	{
		REQUIRE(Player::Black == state.whosTurn());
	}

	SECTION("Board has eight rows")
	{
		REQUIRE(8 == state.getBoardRows());
	}

	SECTION("Board has eight columns")
	{
		REQUIRE(8 == state.getBoardColumns());
	}

	SECTION("Not game over")
	{
		REQUIRE(! state.isGameOver());
	}

	SECTION("Was not pass")
	{
		REQUIRE(! state.wasActionPass());
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

TEST_CASE("Verify that equality operator works.", "[OthelloState, operator]")
{
	auto state1 = OthelloState::initialState();
	auto state2 = OthelloState::initialState();

	SECTION("Initially, they're equal")
	{
		REQUIRE(state1 == state2);
	}

	state1.flipBrick(Position(3,3));

	SECTION("Not equal after a modification.")
	{
		REQUIRE(state1 != state2);
	}

	state2.flipBrick(Position(3,3));

	SECTION("After the other state was adjusted, theyr'e equal again.")
	{
		REQUIRE(state1 == state2);
	}

	SECTION("Not equal after change of turn.")
	{
		state1.changeTurn();
		REQUIRE(state1 != state2);
	}

	SECTION("Not equal if one game is over.")
	{
		state1.setGameOver(true);
		REQUIRE(state1 != state2);
	}

	SECTION("Not equal if size differs.")
	{
		OthelloState smallBoard(4,4,Player::Black);
		OthelloState largeBoard(4,5,Player::Black);

		REQUIRE(smallBoard != largeBoard);
	}


	SECTION("Not equal id passStatus changes")
	{
		state1.setActionWasPass(true);
		REQUIRE(state1 != state2);
	}
}

TEST_CASE("Test board iterator.", "[OthelloState, iterator]")
{
	OthelloState state(2, 2, Player::Black);
	state.setTile(Position(0,0), Tile::Black);
	state.setTile(Position(1,1), Tile::White);

	/* Observe column major ordering. */
	vector<Tile> expected =
		{Tile::Black, Tile::Empty, Tile::Empty, Tile::White};
	vector<Tile> result;

	for (auto tile : state.getBoardIterator()) {
		result.push_back(tile);
	}

	REQUIRE(expected == result);
}
