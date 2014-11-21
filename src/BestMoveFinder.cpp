#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;
using std::max;

namespace othello {

BestMoveFinder::BestMoveFinder(Game game) : game(game)
{}

pair<OthelloAction, score_t> BestMoveFinder::getBestMove()
{
	/* This is a safety precursion. Because the subfunction might leave the
	 * class in an inconsistent state, if the recursion terminates due to an
	 * unexpected exception.
	 */
	currentDepth = 0;
	return _getBestMove(SCORE_INFIMUM, SCORE_SUPERMUM);
}


pair<OthelloAction, score_t> BestMoveFinder::_getBestMove(
		score_t alpha, score_t beta)
{
	using std::sort;

	/* If the maximum depth is surpassed or the game is over just return. */
	if (currentDepth >= maxDepth || game.getState().gameOver()) {
		/* The 'action is irrelevant since it will never be executed
		 * so long as the maxDepth is valid.' */
		return pair<OthelloAction, score_t>(OthelloAction::constructPass(), 0);
	}

	currentDepth++; //Decend.

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

	auto earnedScore = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1));

	for (auto placementEffectPair : placementEffectPairs) {

		/* Unpack. */
		const auto& action = placementEffectPair.first;
		const auto& flips = placementEffectPair.second;

		/* The value of the action. */ //XXX Evaluator task.
		const score_t actionValue = flips.size()+1; //One for the placed brick.

		/* Perform the action. */
		game.commitAction(action);

		/* The best score the advisary can make. By swaping beta and alpha we
		 * solve the dual problem of MIN-VALUE. */
		const auto advisaryEarnedScore = _getBestMove(beta, alpha).second;

		/* The score if the player shoul choose the action. */
		const auto actionScore = actionValue - advisaryEarnedScore;

		/* Restore the original state. */
		game.undoLastAction();

		/* Analyse the result. */

		/* It the score is better than any previously evaluated, choose it. */
		if (actionScore > earnedScore) {
			earnedScore = actionScore;
			bestAction = action;
		}

		/* If it is also better tham beta, then break the loop. */
		if (earnedScore >= beta) {
			break;
		}

		alpha = max(alpha, earnedScore);
	}

	//XXX Consider a try block, to guarantee that the depth is consistent.
	currentDepth--; //Ascend.

	return pair<OthelloAction,score_t>(bestAction, earnedScore);
}

bool BestMoveFinder::actionEffectPairLt(pair<OthelloAction,vector<Position>> p1
		, pair<OthelloAction,vector<Position>> p2)
{
	return p1.second.size() < p2.second.size();
}

} //namespace othello
