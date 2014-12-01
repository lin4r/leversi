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
 * Unit tests for ReversiAction.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "ReversiAction.hpp"
#include "illegal_action_exception.hpp"
#include "actionstring_syntax_exception.hpp"

#include <set>
using std::set;

using namespace reversi;

/* Looks like this:
 *
 * #####
 * #WWW#
 * #WBW#
 * #WWW#
 * #####
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

/* Looks like this:
 *
 * BBBBB
 * BWWWB
 * BW#WB
 */
ReversiState getHoleState()
{
	ReversiState state(3,5,Player::Black);

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
ReversiState longrowState()
{
	ReversiState state(1,5,Player::Black);

	state.setTile(Position(0,1), Tile::White);
	state.setTile(Position(0,2), Tile::White);
	state.setTile(Position(0,3), Tile::White);
	state.setTile(Position(0,4), Tile::Black);

	return state;
}

TEST_CASE("Test flip searching.", "[ReversiAction, stateTransitions]")
{
	auto state = ReversiState::initialState();
	Position outside(-1,-1), occupied(3,3), illegal(4,2), legal(3,4);
	ReversiAction pass(legal, true);

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

		auto flips = ReversiAction(outside).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Cant place on an non-empty tile.")
	{
		auto flips = ReversiAction(occupied).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Cant place if all adjacent bricks have the same colour.")
	{
		auto flips = ReversiAction(illegal).searchFlips(state);
		REQUIRE(flips.empty());
	}

	SECTION("Borders are skipped and inward flips are handled.")
	{
		auto state = getSurroundedState();

		Position placement(0,0);
		Position expectedFlip(1,1);
		auto flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,2);
		expectedFlip = Position(1,2);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(0,4);
		expectedFlip = Position(1,3);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,4);
		expectedFlip = Position(2,3);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,4);
		expectedFlip = Position(3,3);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,2);
		expectedFlip = Position(3,2);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(4,0);
		expectedFlip = Position(3,1);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));

		placement = Position(2,0);
		expectedFlip = Position(2,1);
		flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(1 == flips.size());
		REQUIRE(expectedFlip == flips.at(0));
	}

	SECTION("Can flip in many directions at once")
	{
		auto state = getHoleState();

		Position placement(2,2);
		auto flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(5 == flips.size());
	}

	SECTION("Can flip multiple in row.")
	{
		auto state = longrowState();

		Position placement(0,0);
		auto flips = ReversiAction(placement).searchFlips(state);
		REQUIRE(3 == flips.size());
	}
}

TEST_CASE("Test modifications of the state"
		, "[ReversiAction, stateTransitions]")
{
	ReversiState empty;
	auto state = ReversiState::initialState();

	//3 consecutive legal moves.
	Position pos1(3,2), pos2(2,2), pos3(1,1);
	ReversiAction action1(pos1), action2(pos2), pass(pos3,true);

	SECTION("Throws illegal move exception if outside the grid.")
	{
		ReversiAction illegal1(Position(-1,-1));
		REQUIRE_THROWS_AS(illegal1.execute(state)
			, illegal_action_exception);

		ReversiAction illegal2(Position(8,8));
		REQUIRE_THROWS_AS(illegal2.execute(state)
			, illegal_action_exception);

		ReversiAction illegal3(Position(0,-1));
		REQUIRE_THROWS_AS(illegal3.execute(state)
			, illegal_action_exception);

		ReversiAction illegal4(Position(-1,0));
		REQUIRE_THROWS_AS(illegal4.execute(state)
			, illegal_action_exception);

		ReversiAction illegal5(Position(0,8));
		REQUIRE_THROWS_AS(illegal5.execute(state)
			, illegal_action_exception);

		ReversiAction illegal6(Position(8,0));
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
		ReversiAction outsidePass(Position(-1,-1), true);

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
}

TEST_CASE("Verify Game over.", "[ReversiAction, gameOver]")
{
	ReversiState state;
	auto pass = ReversiAction::pass();

	SECTION("Game Over after two pass")
	{
		pass.execute(state);
		REQUIRE(! state.isGameOver());
		pass.execute(state);
		REQUIRE(state.isGameOver());
	}

	SECTION("Not game over if placement ocurrs between two pass.")
	{
		pass.execute(state);

		//Make a legal placement possible.
		state.setTile(Position(0,1), Tile::Black);
		state.setTile(Position(0,2), Tile::White);
		ReversiAction legal(Position(0,0));

		legal.execute(state);
		REQUIRE(! state.isGameOver());

		//Remove the bricks so that no move is possible again.
		state.setTile(Position(0,0), Tile::Empty);
		state.setTile(Position(0,1), Tile::Empty);
		state.setTile(Position(0,2), Tile::Empty);

		pass.execute(state);

		REQUIRE(! state.isGameOver());
	}

	SECTION("Throws game_over_exception if the game is over.")
	{
		state.setGameOver(true);
		REQUIRE_THROWS_AS(pass.execute(state), illegal_action_exception);
	}
}

TEST_CASE("Test operators", "[ReversiAction, operators]")
{
	ReversiAction action(Position(1,2)), equalAction(Position(1,2))
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
		ReversiAction p1(Position(2,3)), p2(Position(3,2));
		REQUIRE(p1 < p2);
	}
}

TEST_CASE("Test placement search.", "[ReversiAction, placementSearch]")
{
	auto state = ReversiState::initialState();

	SECTION("Finds exactly the legal placements.")
	{
		auto outcomes
			= ReversiAction::findLegalPlacements(state);

		REQUIRE(4 == outcomes.size());

		/* Insert to set so that we easily can test membership. */
//		set<ReversiAction> placementsSet(
//			placementsVector.begin(), placementsVector.end());
		set<ReversiAction> placements;
		for (auto outcome : outcomes) {
			placements.insert(outcome.action);
		}
		

		const auto has = [&] (ReversiAction action) {
			return placements.find(action) != placements.end();
		};

		/* Just check that the elements was evaluated correctly. */
		CHECK(4 == placements.size());

		/* These are the legal moves on the first turn of the game. */
		REQUIRE(has(ReversiAction(Position(3,2))));
		REQUIRE(has(ReversiAction(Position(2,3))));
		REQUIRE(has(ReversiAction(Position(4,5))));
		REQUIRE(has(ReversiAction(Position(5,4))));
	}
}


TEST_CASE("Test action string conversion.", "[ReversiAction, actionString]")
{
	ReversiAction pass(Position(1,2),true);
	ReversiAction put(Position(3,4));

	SECTION ("Verify pass format")
	{
		REQUIRE("pass" == pass.actionString());
	}

	SECTION ("Verify move format")
	{
		REQUIRE("(3,4)" == put.actionString());
	}
}

TEST_CASE("Test action string parseing", "[ReversiAction, actionString]")
{
	using namespace std;

	SECTION("Throws if misspelled.")
	{
		REQUIRE_THROWS_AS(ReversiAction::parse("pards")
			, actionstring_syntax_exception);
	}

	SECTION("Throws if we add tail")
	{
		REQUIRE_THROWS_AS(ReversiAction::parse("pardsasdf")
			, actionstring_syntax_exception);
	}

	SECTION("Throws if we add head")
	{
		REQUIRE_THROWS_AS(ReversiAction::parse("asdfpass")
			, actionstring_syntax_exception);
	}

	SECTION("Can parse pass")
	{
		auto pass = ReversiAction::parse("pass");

		REQUIRE(pass.isPass());
	}

	SECTION("Can parse a non-pass")
	{
		auto nonPass1 = ReversiAction::parse("(3,4)");
		Position excpected = {3,4};

		REQUIRE(excpected == nonPass1.getPosition());

		/* TODO Robuster matching allowing this and whitespaces in the
		 * parantheses will be implemented once gcc supports regex (4.9)
		 */
//		/* Obviusly not a real Reversi position. I want to test more than one
//		 * digit numbers.
//		 */
//		ReversiAction nonPass2("(12,1337)");
//
//		REQUIRE(12 == nonPass2.get_row());
//		REQUIRE(1337 == nonPass2.get_column());
	}
}
