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
 * Unit tests for Position.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Position.hpp"

using namespace othello;

TEST_CASE("Verify cardinal directions", "[Position]")
{
	Position pos(0,0);

	SECTION("Verify north.")
	{
		Position expected(-1,0);

		REQUIRE(expected == pos.north());
	}

	SECTION("Verify east.")
	{
		Position expected(0,1);

		REQUIRE(expected == pos.east());
	}

	SECTION("Verify south.")
	{
		Position expected(1,0);

		REQUIRE(expected == pos.south());
	}

	SECTION("Verify west.")
	{
		Position expected(0,-1);

		REQUIRE(expected == pos.west());
	}

	SECTION("Verify north-east")
	{
		Position expected(-1,1);

		REQUIRE(expected == pos.northEast());
	}

	SECTION("Verify south-east")
	{
		Position expected(1,1);

		REQUIRE(expected == pos.southEast());
	}

	SECTION("Verify south-west")
	{
		Position expected(1,-1);

		REQUIRE(expected == pos.southWest());
	}

	SECTION("Verify north-west")
	{
		Position expected(-1,-1);

		REQUIRE(expected == pos.northWest());
	}
}
