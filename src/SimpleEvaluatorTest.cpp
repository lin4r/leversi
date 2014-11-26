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

TEST_CASE("The score is #black - #white.", "[SimpleEvaluator]")
{
	SimpleEvaluator evaluator;
	auto state = OthelloState::initialState();
	OthelloAction legal(Position(3,2));

	auto flips = legal.execute(state);

	auto score = evaluator.moveUtility(legal, flips, state);

	REQUIRE(3 == score);
}

TEST_CASE("Pass gives 0 score", "[SimpleEvaluator]")
{
	SimpleEvaluator evaluator;
	OthelloState empty;
	auto pass = OthelloAction::pass();

	auto flips = pass.execute(empty);

	auto score = evaluator.moveUtility(pass, flips, empty);

	REQUIRE(0 == score);
}
