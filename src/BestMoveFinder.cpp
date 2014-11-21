#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>

using std::pair;

namespace othello {

BestMoveFinder::BestMoveFinder(Game game) : game(game)
{}

pair<OthelloAction, score_t> BestMoveFinder::getBestMove()
{
	using std::vector;

	auto placementEffectPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (placementEffectPairs.empty()) {
		const score_t score{0}; //Evaluator pass.
		const auto action = OthelloAction::constructPass();

		return pair<OthelloAction,score_t>(action, score);
	}

	auto earnedScore = getScoreInfimum();
	OthelloAction bestAction(Position(-1,-1));

	//TODO at the time being, just return a legal action.
	auto action = placementEffectPairs.at(0).first;
	auto flips = game.commitAction(action);
	earnedScore = flips.size()+1;
	game.undoLastAction();

	return pair<OthelloAction,score_t>(action, earnedScore);
}

score_t BestMoveFinder::getScoreInfimum()
{
	return SCORE_INFIMUM;
}

} //namespace othello
