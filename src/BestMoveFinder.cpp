#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;

namespace othello {

BestMoveFinder::BestMoveFinder(Game game) : game(game)
{}

pair<OthelloAction, score_t> BestMoveFinder::getBestMove()
{
	using std::sort;

	auto placementEffectPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (placementEffectPairs.empty()) {
		const score_t score{0}; //Evaluator pass.
		const auto action = OthelloAction::constructPass();

		return pair<OthelloAction,score_t>(action, score);
	}

	/* Sort the vector according to direct effect. */
	sort(placementEffectPairs.begin(), placementEffectPairs.end()
		, actionEffectPairLt);

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

bool BestMoveFinder::actionEffectPairLt(pair<OthelloAction,vector<Position>> p1
		, pair<OthelloAction,vector<Position>> p2)
{
	return p1.second.size() < p2.second.size();
}

} //namespace othello
