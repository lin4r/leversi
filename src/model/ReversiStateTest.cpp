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
}
/* Looks like this_
 *
 * #####
 * #WWW#
 * #WBW#
 * #WWW#
 * #####
 *
 *
 *
 */
ReversiState getSurroundedState()
{
	ReversiState state(5,5,Player::Black);

	state.setTile(Position(1,1), Tile::White);
	state.setTile(Position(1,2), Tile::White);
	state.setTile(Position(1,3), Tile::White);

	state.setTile(Position(2,1), Tile::White);
	state.setTile(Position(2,2), Tile::Black);
	state.setTile(Position(2,3), Tile::White);

	state.setTile(Position(3,1), Tile::White);
	state.setTile(Position(3,2), Tile::White);
	state.setTile(Position(3,3), Tile::White);

	return state;
}

TEST_CASE("Test that flip searching.", "[ReversiState, ]")
{
	auto state = ReversiState::initialState();

	Position occupied(3,3), illegal(4,2), legal(3,4);

	SECTION("Cant place on an non-empty tile.")
	{
		auto flips = state.searchFlips(ReversiAction(occupied));
		REQUIRE(flips.empty());
	}

	SECTION("Cant place if all adjacent bricks have the same colour.")
	{
		auto flips = state.searchFlips(ReversiAction(illegal));
		REQUIRE(flips.empty());
	}

	SECTION("Borders are skipped and inward flips are handled.")
	{
		auto state = getSurroundedState();

		Position placement(0,0);
		Position expectedFlip(1,1);
		auto flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,2);
		expectedFlip = Position(1,2);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,4);
		expectedFlip = Position(1,3);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,4);
		expectedFlip = Position(2,3);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,4);
		expectedFlip = Position(3,3);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,2);
		expectedFlip = Position(3,2);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,0);
		expectedFlip = Position(3,1);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,0);
		expectedFlip = Position(2,1);
		flips = state.searchFlips(ReversiAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));
	}
}

TEST_CASE("Test modifications of the state", "[ReversiState, actions]")
{
	ReversiState state;

	Position pos1(0,0), pos2(1,1), pos3(3,3);
	ReversiAction action1(pos1), action2(pos2), pass(pos3,true);

	SECTION("Verify that the initial state is according to game rules.")
	{
		auto initial = ReversiState::initialState();

		REQUIRE(Tile::White == initial.inspectTile(Position(3,3)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(3,4)));
		REQUIRE(Tile::White == initial.inspectTile(Position(4,4)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(4,3)));
	}

	SECTION("Throws illegal move exception if outside the grid.")
	{
		ReversiAction illegal1(Position(-1,-1));
		REQUIRE_THROWS_AS(state.performAction(illegal1)
			, illegal_move_exception);

		ReversiAction illegal2(Position(8,8));
		REQUIRE_THROWS_AS(state.performAction(illegal2)
			, illegal_move_exception);


		ReversiAction illegal3(Position(0,-1));
		REQUIRE_THROWS_AS(state.performAction(illegal3)
			, illegal_move_exception);

		ReversiAction illegal4(Position(-1,0));
		REQUIRE_THROWS_AS(state.performAction(illegal4)
			, illegal_move_exception);

		ReversiAction illegal5(Position(0,8));
		REQUIRE_THROWS_AS(state.performAction(illegal5)
			, illegal_move_exception);

		ReversiAction illegal6(Position(8,0));
		REQUIRE_THROWS_AS(state.performAction(illegal6)
			, illegal_move_exception);
	}

	SECTION("Dont throw if pass, even if outside grid or the position is illegal")
	{
		ReversiAction outsidePass(Position(-1,-1), true);

		REQUIRE_NOTHROW(state.performAction(outsidePass));

		//TODO illegal inside grid.
	}

	SECTION("Performing an action changes turn.")
	{
		state.performAction(action1);

		REQUIRE(Player::White == state.whosTurn());

		state.performAction(action2);

		REQUIRE(Player::Black == state.whosTurn());
	}

	SECTION("Performing actions places tiles")
	{
		/* The tile is empty before placement. */
		REQUIRE(Tile::Empty == state.inspectTile(pos1));

		state.performAction(action1);

		REQUIRE(Tile::Black == state.inspectTile(pos1));

		REQUIRE(Tile::Empty == state.inspectTile(pos2));

		state.performAction(action2);

		/*Next placement is black.*/
		REQUIRE(Tile::White == state.inspectTile(pos2));

		REQUIRE(Tile::Empty == state.inspectTile(pos3));

		state.performAction(pass);

		/*The position is still empty after the pass. */
		REQUIRE(Tile::Empty == state.inspectTile(pos3));

		ReversiAction nonPass(pass.get_position());

		state.performAction(nonPass);

		/* The turn still changed. */
		REQUIRE(Tile::White == state.inspectTile(nonPass.get_position()));
	}
}
