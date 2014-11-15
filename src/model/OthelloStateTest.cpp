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
}
/* Looks like this:
 *
 * #####
 * #WWW#
 * #WBW#
 * #WWW#
 * #####
 *
 */
OthelloState getSurroundedState()
{
	OthelloState state(5,5,Player::Black);

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

/* Looks like this:
 *
 * BBBBB
 * BWWWB
 * BW#WB
 */
OthelloState getHoleState()
{
	OthelloState state(3,5,Player::Black);

	state.setTile(Position(0,0), Tile::Black);
	state.setTile(Position(0,1), Tile::Black);
	state.setTile(Position(0,2), Tile::Black);
	state.setTile(Position(0,3), Tile::Black);
	state.setTile(Position(0,4), Tile::Black);

	state.setTile(Position(1,0), Tile::Black);
	state.setTile(Position(1,1), Tile::White);
	state.setTile(Position(1,2), Tile::White);
	state.setTile(Position(1,3), Tile::White);
	state.setTile(Position(1,4), Tile::Black);

	state.setTile(Position(2,0), Tile::Black);
	state.setTile(Position(2,1), Tile::White);
	state.setTile(Position(2,2), Tile::Empty);
	state.setTile(Position(2,3), Tile::White);
	state.setTile(Position(2,4), Tile::Black);

	return state;
}

/* Looks like this:
 *
 * #WWWB
 */
OthelloState longrowState()
{
	OthelloState state(1,5,Player::Black);

	state.setTile(Position(0,1), Tile::White);
	state.setTile(Position(0,2), Tile::White);
	state.setTile(Position(0,3), Tile::White);
	state.setTile(Position(0,4), Tile::Black);

	return state;
}

TEST_CASE("Test that flip searching.", "[OthelloState, ]")
{
	auto state = OthelloState::initialState();

	Position outside(-1,-1), occupied(3,3), illegal(4,2), legal(3,4);

	SECTION("Causes no flips if pass")
	{
		OthelloAction pass(legal, true);
		auto flips = state.searchFlips(pass);
		REQUIRE(flips.empty());
	}

	SECTION("Gets no flips if outside the grid")
	{
		/* Place a white, which would have been flipped if (-1,-1) was inside
		 * the grid
		 */
		state.setTile(Position(0,0), Tile::White);
		state.setTile(Position(1,1), Tile::Black);

		auto flips = state.searchFlips(OthelloAction(outside));
		REQUIRE(flips.empty());
	}

	SECTION("Cant place on an non-empty tile.")
	{
		auto flips = state.searchFlips(OthelloAction(occupied));
		REQUIRE(flips.empty());
	}

	SECTION("Cant place if all adjacent bricks have the same colour.")
	{
		auto flips = state.searchFlips(OthelloAction(illegal));
		REQUIRE(flips.empty());
	}

	SECTION("Borders are skipped and inward flips are handled.")
	{
		auto state = getSurroundedState();

		Position placement(0,0);
		Position expectedFlip(1,1);
		auto flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,2);
		expectedFlip = Position(1,2);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,4);
		expectedFlip = Position(1,3);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,4);
		expectedFlip = Position(2,3);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,4);
		expectedFlip = Position(3,3);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,2);
		expectedFlip = Position(3,2);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,0);
		expectedFlip = Position(3,1);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,0);
		expectedFlip = Position(2,1);
		flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));
	}

	SECTION("Can flip in many directions at once")
	{
		auto state = getHoleState();

		Position placement(2,2);
		auto flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(5 == flips.size());
	}

	SECTION("Can flip multiple in row.")
	{
		auto state = longrowState();

		Position placement(0,0);
		auto flips = state.searchFlips(OthelloAction(placement));
		REQUIRE(3 == flips.size());
	}
}

TEST_CASE("Test modifications of the state", "[OthelloState, actions]")
{
	OthelloState empty;
	auto state = OthelloState::initialState();

	//3 consecutive legal moves.
	Position pos1(3,2), pos2(2,2), pos3(1,1);
	OthelloAction action1(pos1), action2(pos2), pass(pos3,true);

	SECTION("Verify that the initial state is according to game rules.")
	{
		auto initial = OthelloState::initialState();

		REQUIRE(Tile::White == initial.inspectTile(Position(3,3)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(3,4)));
		REQUIRE(Tile::White == initial.inspectTile(Position(4,4)));
		REQUIRE(Tile::Black == initial.inspectTile(Position(4,3)));
	}

	SECTION("Throws illegal move exception if outside the grid.")
	{
		OthelloAction illegal1(Position(-1,-1));
		REQUIRE_THROWS_AS(state.execute(illegal1)
			, illegal_action_exception);

		OthelloAction illegal2(Position(8,8));
		REQUIRE_THROWS_AS(state.execute(illegal2)
			, illegal_action_exception);


		OthelloAction illegal3(Position(0,-1));
		REQUIRE_THROWS_AS(state.execute(illegal3)
			, illegal_action_exception);

		OthelloAction illegal4(Position(-1,0));
		REQUIRE_THROWS_AS(state.execute(illegal4)
			, illegal_action_exception);

		OthelloAction illegal5(Position(0,8));
		REQUIRE_THROWS_AS(state.execute(illegal5)
			, illegal_action_exception);

		OthelloAction illegal6(Position(8,0));
		REQUIRE_THROWS_AS(state.execute(illegal6)
			, illegal_action_exception);
	}

	SECTION("Can't pass if a placement is possible.")
	{
		REQUIRE_THROWS_AS(state.execute(pass)
			, illegal_action_exception);
	}

	SECTION("Dont throw if pass, even if outside grid or the position is illegal")
	{
		OthelloAction outsidePass(Position(-1,-1), true);

		REQUIRE_NOTHROW(empty.execute(outsidePass));
	}

	SECTION("Performing an action changes turn.")
	{
		state.execute(action1);

		REQUIRE(Player::White == state.whosTurn());

		state.execute(action2);

		REQUIRE(Player::Black == state.whosTurn());
	}

	SECTION("Performing actions places tiles")
	{
		// The tile is empty before placement.
		REQUIRE(Tile::Empty == state.inspectTile(pos1));

		state.execute(action1);

		REQUIRE(Tile::Black == state.inspectTile(pos1));

		REQUIRE(Tile::Empty == state.inspectTile(pos2));

		state.execute(action2);

		// Next placement is white.
		REQUIRE(Tile::White == state.inspectTile(pos2));



		// Pass test are performed on the empty board.
		REQUIRE(Tile::Empty == empty.inspectTile(pos3));
		REQUIRE(Player::Black == empty.whosTurn());

		empty.execute(pass);

		// The position is still empty after the pass.
		REQUIRE(Tile::Empty == empty.inspectTile(pos3));

		//The turn still changed.
		REQUIRE(Player::White == empty.whosTurn());
	}

	SECTION("Game over if both players are out of moves and thus pass.")
	{
		auto state = longrowState();

		REQUIRE(! state.gameOver());

		//Start of with a legal placement.
		state.execute(OthelloAction(Position(0,0)));
		REQUIRE(! state.gameOver());

		//White can/must pass but it is not over yet.
		empty.execute(pass);
		REQUIRE(! empty.gameOver());

		//Black must also pass, it's over.
		empty.execute(pass);
		REQUIRE(empty.gameOver());
	}
}

