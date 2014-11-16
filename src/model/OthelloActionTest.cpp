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
 * Unit tests for OthelloAction.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "OthelloAction.hpp"
#include "illegal_action_exception.hpp"
#include "actionstring_syntax_exception.hpp"

#include <set>
using std::set;

using namespace othello;

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

TEST_CASE("Test flip searching.", "[OthelloAction, stateTransitions]")
{
	auto state = OthelloState::initialState();
	Position outside(-1,-1), occupied(3,3), illegal(4,2), legal(3,4);
	OthelloAction pass(legal, true);

	SECTION("Causes no flips if pass")
	{
		auto flips = pass.searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Gets no flips if outside the grid")
	{
		// Place a white, which would have been flipped if (-1,-1) was inside
		// the grid
		//
		state.setTile(Position(0,0), Tile::White);
		state.setTile(Position(1,1), Tile::Black);

		auto flips = OthelloAction(outside).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Cant place on an non-empty tile.")
	{
		auto flips = OthelloAction(occupied).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Cant place if all adjacent bricks have the same colour.")
	{
		auto flips = OthelloAction(illegal).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Borders are skipped and inward flips are handled.")
	{
		auto state = getSurroundedState();

		Position placement(0,0);
		Position expectedFlip(1,1);
		auto flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,2);
		expectedFlip = Position(1,2);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,4);
		expectedFlip = Position(1,3);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,4);
		expectedFlip = Position(2,3);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,4);
		expectedFlip = Position(3,3);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,2);
		expectedFlip = Position(3,2);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,0);
		expectedFlip = Position(3,1);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,0);
		expectedFlip = Position(2,1);
		flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));
	}

	SECTION("Can flip in many directions at once")
	{
		auto state = getHoleState();

		Position placement(2,2);
		auto flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(5 == flips.size());
	}

	SECTION("Can flip multiple in row.")
	{
		auto state = longrowState();

		Position placement(0,0);
		auto flips = OthelloAction(placement).searchFlips(state);
		REQUIRE(3 == flips.size());
	}
}

TEST_CASE("Test modifications of the state", "[OthelloAction, stateTransitions]")
{
	OthelloState empty;
	auto state = OthelloState::initialState();

	//3 consecutive legal moves.
	Position pos1(3,2), pos2(2,2), pos3(1,1);
	OthelloAction action1(pos1), action2(pos2), pass(pos3,true);

	SECTION("Throws illegal move exception if outside the grid.")
	{
		OthelloAction illegal1(Position(-1,-1));
		REQUIRE_THROWS_AS(illegal1.execute(state)
			, illegal_action_exception);

		OthelloAction illegal2(Position(8,8));
		REQUIRE_THROWS_AS(illegal2.execute(state)
			, illegal_action_exception);


		OthelloAction illegal3(Position(0,-1));
		REQUIRE_THROWS_AS(illegal3.execute(state)
			, illegal_action_exception);

		OthelloAction illegal4(Position(-1,0));
		REQUIRE_THROWS_AS(illegal4.execute(state)
			, illegal_action_exception);

		OthelloAction illegal5(Position(0,8));
		REQUIRE_THROWS_AS(illegal5.execute(state)
			, illegal_action_exception);

		OthelloAction illegal6(Position(8,0));
		REQUIRE_THROWS_AS(illegal6.execute(state)
			, illegal_action_exception);
	}

	SECTION("Can't pass if a placement is possible.")
	{
		REQUIRE_THROWS_AS(pass.execute(state)
			, illegal_action_exception);
	}

	SECTION("Dont throw if pass, even if outside grid or the position is illegal")
	{
		OthelloAction outsidePass(Position(-1,-1), true);

		REQUIRE_NOTHROW(outsidePass.execute(empty));
	}

	SECTION("Performing an action changes turn.")
	{
		action1.execute(state);

		REQUIRE(Player::White == state.whosTurn());

		action2.execute(state);

		REQUIRE(Player::Black == state.whosTurn());
	}

	SECTION("Performing placement actions places bricks on tiles")
	{
		// The tile is empty before placement.
		REQUIRE(Tile::Empty == state.inspectTile(pos1));

		action1.execute(state);

		REQUIRE(Tile::Black == state.inspectTile(pos1));

		REQUIRE(Tile::Empty == state.inspectTile(pos2));

		action2.execute(state);

		// Next placement is white.
		REQUIRE(Tile::White == state.inspectTile(pos2));



		// Pass test are performed on the empty board.
		REQUIRE(Tile::Empty == empty.inspectTile(pos3));
		REQUIRE(Player::Black == empty.whosTurn());

		pass.execute(empty);

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
		OthelloAction(Position(0,0)).execute(state);
		REQUIRE(! state.gameOver());

		//White can/must pass but it is not over yet.
		pass.execute(state);
		REQUIRE(! state.gameOver());

		//Black must also pass, it's over.
		pass.execute(state);
		REQUIRE(state.gameOver());
	}
}

TEST_CASE("Test operators", "[OthelloAction, operators]")
{
	OthelloAction action(Position(1,2)), equalAction(Position(1,2))
		, largerRow(Position(2,1)), largerCol(Position(1,4))
		, pass(Position(1,2), true);

	SECTION("Test equality") {
		REQUIRE(action == equalAction);
		REQUIRE(!(action == largerRow));
		REQUIRE(!(action == pass));
	}

	SECTION("Test less-than") {
		REQUIRE(!(action < equalAction));
		REQUIRE(!(equalAction < action));
		REQUIRE(pass < action);
		REQUIRE(pass < largerRow);
		REQUIRE(pass < largerCol);
	}

	SECTION("BUG, Couldn evaluate these actions.")
	{
		OthelloAction p1(Position(2,3)), p2(Position(3,2));
		REQUIRE(p1 < p2);
	}
}

TEST_CASE("Test placement search.", "[OthelloAction, placementSearch]")
{
	auto state = OthelloState::initialState();

	SECTION("Finds exactly the legal placements.")
	{
		auto placementsVector = OthelloAction::findLegalPlacements(state);

		REQUIRE(4 == placementsVector.size());

		/* Convert to set so that we easily can test membership. */
		set<OthelloAction> placementsSet(
			placementsVector.begin(), placementsVector.end());

		const auto has = [&] (OthelloAction action) {
			return placementsSet.find(action) != placementsSet.end();
		};

		/* Just check that the elements was evaluated correctly. */
		CHECK(4 == placementsSet.size());

		/* These are the legal moves on the first turn of the game. */
		REQUIRE(has(OthelloAction(Position(3,2))));
		REQUIRE(has(OthelloAction(Position(2,3))));
		REQUIRE(has(OthelloAction(Position(4,5))));
		REQUIRE(has(OthelloAction(Position(5,4))));
	}
}


TEST_CASE("Test action string conversion.", "[OthelloAction, actionString]")
{
	OthelloAction pass(Position(1,2),true);
	OthelloAction put(Position(3,4));

	SECTION ("Verify pass format")
	{
		REQUIRE("pass" == pass.actionString());
	}

	SECTION ("Verify move format")
	{
		REQUIRE("(3,4)" == put.actionString());
	}
}

TEST_CASE("Test action string parseing", "[OthelloAction, actionString]")
{
	using namespace std;

	SECTION("Throws if misspelled.")
	{
		REQUIRE_THROWS_AS(OthelloAction("pards")
			, actionstring_syntax_exception);
	}

	SECTION("Throws if we add tail")
	{
		REQUIRE_THROWS_AS(OthelloAction("pardsasdf")
			, actionstring_syntax_exception);
	}

	SECTION("Throws if we add head")
	{
		REQUIRE_THROWS_AS(OthelloAction("asdfpass")
			, actionstring_syntax_exception);
	}

	SECTION("Can parse pass")
	{
		OthelloAction pass("pass");

		REQUIRE(pass.isPass());
	}

	SECTION("Can parse a non-pass")
	{
		OthelloAction nonPass1("(3,4)");
		Position excpected = {3,4};

		REQUIRE(excpected == nonPass1.get_position());

		/* TODO Robuster matching allowing this and whitespaces in the
		 * parantheses will be implemented once gcc supports regex (4.9)
		 */
//		/* Obviusly not a real Othello position. I want to test more than one
//		 * digit numbers.
//		 */
//		OthelloAction nonPass2("(12,1337)");
//
//		REQUIRE(12 == nonPass2.get_row());
//		REQUIRE(1337 == nonPass2.get_column());
	}
}
