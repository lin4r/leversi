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

TEST_CASE("Always fails.", "[Game, fails]")
{
	REQUIRE(false);
}
