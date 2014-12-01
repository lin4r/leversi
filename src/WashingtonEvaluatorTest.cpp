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

using namespace reversi;

TEST_CASE("The deffault values are set", "[WashingtonEvaluator, default]")
{
	WashingtonEvaluator evaluator;
	auto weights = evaluator.getWeights();

	REQUIRE(30.0 == weights.corner);
	REQUIRE(5.0 == weights.mobility);
	REQUIRE(25.0 == weights.stability);
	REQUIRE(25.0 == weights.coinParity);
}

// The new utility are to complex for it to be possible to predict the value.
// If the inherited utility is used, it is already tested in SimpleEvaluator.
//
//TEST_CASE("The move score is the gain in bricks."
//		, "[WashingtonEvaluator, moveOrdering]")
//{
//	WashingtonEvaluator evaluator;
//	auto state = ReversiState::initialState();
//	ReversiAction legal(Position(3,2));
//
//	auto flips = legal.execute(state);
//	Outcome outcome = {legal, flips};
//
//	auto score = evaluator.moveUtility(outcome, state);
//
//	REQUIRE(3 == score);
//}

TEST_CASE("Pass gives 0 move score", "[WashingtonEvaluator, moveOrdering]")
{
	WashingtonEvaluator evaluator;
	ReversiState empty;
	auto pass = ReversiAction::pass();

	auto flips = pass.execute(empty);
	Outcome outcome = {pass, flips};

	auto score = evaluator.moveUtility(outcome, empty);

	REQUIRE(0 == score);
}

TEST_CASE("Some trivial property test."
		, "[WashingtonEvaluator, utility]")
{
	WashingtonEvaluator evaluator;
	auto state = ReversiState::initialState();
	ReversiAction legal(Position(3,2));

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
