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
		REQUIRE(8 == state.getBoardRows());
	}

	SECTION("Board has eight columns")
	{
		REQUIRE(8 == state.getBoardColumns());
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

//TODO Test belongs in othello action.
//TEST_CASE("Verify Game over.", "[OthelloState, gameOver]")
//{
//	OthelloState state;
//
//	SECTION("Game Over after two pass")
//	{
//		REQUIRE(! state.gameOver());
//		state.updateGameStatus(true);
//		REQUIRE(! state.gameOver());
//		state.updateGameStatus(true);
//		REQUIRE(state.gameOver());
//	}
//
//	SECTION("Not game over if placement ocurrs between two pass.")
//	{
//		state.updateGameStatus(true);
//		state.updateGameStatus(false);
//		REQUIRE(! state.gameOver());
//		state.updateGameStatus(true);
//		REQUIRE(! state.gameOver());
//	}
//
//	SECTION("Still game over if i make an (erroneus) placement after two passes")
//	{
//		state.updateGameStatus(true);
//		state.updateGameStatus(true);
//		state.updateGameStatus(false);
//		REQUIRE(state.gameOver());
//	}
//}

TEST_CASE("Veerify that equality operator works.", "[OthelloState, operator]")
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
