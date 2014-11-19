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

using namespace othello;

TEST_CASE("Comitting and undoing actoins.", "[Game]")
{
	Game game;
	OthelloState initial = game.refState();

	Position pos1(3,2), pos2(2,2);
	OthelloAction legal1(pos1), legal2(pos2);

	game.commitAction(legal1);

	SECTION("State changed after commit")
	{
		OthelloState after = game.refState();
		REQUIRE(initial != after);
	}

	game.undoLastAction();

	SECTION("State restored after undo.")
	{
		OthelloState restored = game.refState();
		REQUIRE(initial == restored);
	}
}
