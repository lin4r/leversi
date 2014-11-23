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
 * Unit tests for Game
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Game.hpp"
#include "undo_initial_state_exception.hpp"

using namespace othello;

TEST_CASE("Comitting and undoing placements.", "[Game, placement]")
{
	Game game;
	auto initial = game.getState();

	Position pos1(3,2), pos2(2,2);
	OthelloAction legal1(pos1), legal2(pos2);

	game.commitAction(legal1);

	SECTION("State changed after commit")
	{
		auto after = game.getState();
		REQUIRE(initial != after);
	}

	game.undoLastAction();

	SECTION("State restored after undo.")
	{
		auto restored = game.getState();
		REQUIRE(initial == restored);
	}

	game.commitAction(legal1);
	game.commitAction(legal2);

	game.undoLastAction();
	game.undoLastAction();

	SECTION("Can undo multiple commits.")
	{
		auto restored = game.getState();
		REQUIRE(initial == restored);
	}
}

TEST_CASE("Comitting and undoing pass actions.", "[Game]")
{
	auto game = Game::testEmptyBoard();
	auto initial = game.getState();
	OthelloAction pass(Position(-1,-1), true);

	game.commitAction(pass);

	SECTION("State changed after commit")
	{
		auto after = game.getState();
		REQUIRE(initial != after);
	}

	game.undoLastAction();

	SECTION("State restored after undo.")
	{
		auto restored = game.getState();
		REQUIRE(initial == restored);
	}
}
/*
TEST_CASE("Can't undo the initial state.", "[Game]")
{
	Game game;
	REQUIRE_THROWS_AS(game.undoLastAction(), undo_initial_state_exception);
}
*/
