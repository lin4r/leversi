/*
 * Unit test for WashingtonEvaluator.
 *
 * The test are not sufficient. More-sophisticated-than-unit-tests are needed
 * to properly evaluate the utility function.
 *
 * Linus Narva
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "WashingtonEvaluator.hpp"
#include "Position.hpp"

using namespace othello;

TEST_CASE("The move score is the gain in bricks."
		, "[WashingtonEvaluator, moveOrdering]")
{
	WashingtonEvaluator evaluator;
	auto state = OthelloState::initialState();
	OthelloAction legal(Position(3,2));

	auto flips = legal.execute(state);
	Outcome outcome = {legal, flips};

	auto score = evaluator.moveUtility(outcome, state);

	REQUIRE(3 == score);
}

TEST_CASE("Pass gives 0 move score", "[WashingtonEvaluator, moveOrdering]")
{
	WashingtonEvaluator evaluator;
	OthelloState empty;
	auto pass = OthelloAction::pass();

	auto flips = pass.execute(empty);
	Outcome outcome = {pass, flips};

	auto score = evaluator.moveUtility(outcome, empty);

	REQUIRE(0 == score);
}

TEST_CASE("Some trivial property test."
		, "[WashingtonEvaluator, utility]")
{
	WashingtonEvaluator evaluator;
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

	SECTION("Taking a brick increases score, white looses what black gains.")
	{
		auto blackScore = evaluator.utility(Player::Black, state);
		REQUIRE(0 < blackScore);

		auto whiteScore = evaluator.utility(Player::White, state);
		REQUIRE(0 > whiteScore);
	}
}
