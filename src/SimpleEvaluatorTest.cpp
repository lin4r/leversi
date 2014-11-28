/*
 * Unit test for SimpleEvaluator.
 *
 * Linus Narva
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "SimpleEvaluator.hpp"
#include "Position.hpp"

using namespace othello;

TEST_CASE("The mov score is the gain in bricks."
		, "[SimpleEvaluator, moveOrdering]")
{
	SimpleEvaluator evaluator;
	auto state = OthelloState::initialState();
	OthelloAction legal(Position(3,2));

	auto flips = legal.execute(state);
	Outcome outcome = {legal, flips};

	auto score = evaluator.moveUtility(outcome, state);

	REQUIRE(3 == score);
}

TEST_CASE("Pass gives 0 move score", "[SimpleEvaluator, moveOrdering]")
{
	SimpleEvaluator evaluator;
	OthelloState empty;
	auto pass = OthelloAction::pass();

	auto flips = pass.execute(empty);
	Outcome outcome = {pass, flips};

	auto score = evaluator.moveUtility(outcome, empty);

	REQUIRE(0 == score);
}

TEST_CASE("The utility is the advantage in # of bricks."
		, "[SimpleEvaluator, utility]")
{
	SimpleEvaluator evaluator;
	auto state = OthelloState::initialState();
	OthelloAction legal(Position(3,2));

	SECTION("Initally both players have score 0")
	{
		auto blackScore = evaluator.utility(Player::Black, state);
		REQUIRE(0 == blackScore);

		auto whiteScore = evaluator.utility(Player::White, state);
		REQUIRE(0 == whiteScore);
	}

	auto flips = legal.execute(state);
	Outcome outcome = {legal, flips};

	//Three, because one blick is placed, one is flipped so that black gains
	//one and white looses one.
	SECTION("Black gains three bricks, white looses what black gains.")
	{
		auto blackScore = evaluator.utility(Player::Black, state);
		REQUIRE(3 == blackScore);

		auto whiteScore = evaluator.utility(Player::White, state);
		REQUIRE(-blackScore == whiteScore);
	}
}
