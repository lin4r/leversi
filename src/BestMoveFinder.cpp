#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>
#include <algorithm>

//XXX DEBUG
#include <iostream>
using namespace std;

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

struct Effect
{
	OthelloAction action;
	score_t score;
};

/* Large effects are desireable and therefore comes first. */
static inline bool isBetter(Effect e1, Effect e2) noexcept
{
	return e1.score > e2.score;
}

//TODO Refactor, Too long function.
pair<OthelloAction, score_t> BestMoveFinder::_getBestMove(
		score_t alpha, score_t beta)
{
	using std::sort;

	/* If the maximum depth is surpassed or the game is over just return. */
	if (currentDepth >= maxDepth || game.getState().isGameOver()) {
		/* The 'action is irrelevant since it will never be executed
		 * so long as the maxDepth is valid.' */
		return pair<OthelloAction, score_t>(OthelloAction::pass(), 0);
	}

	currentDepth++; //Decend.

	auto placementEffectPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (placementEffectPairs.empty()) {

		const pair<OthelloAction,flips_t> passPair(OthelloAction::pass()
			, flips_t());

		placementEffectPairs.push_back(passPair);
	}

	/* Computes the score obtained by each of the actions. */
	vector<Effect> effects;
	for (auto placementEffectPair : placementEffectPairs) {

		/* Unpack. */
		const auto& action = placementEffectPair.first;
		const auto& flips = placementEffectPair.second;
		const auto score = evaluator.evaluateAction(action, flips
			, game.refState());

		const Effect effect = {action, score};

		effects.push_back(effect);
	}

	/* Sort the vector so that moves with high scores comes first. */
	sort(effects.begin(), effects.end(), isBetter);

	auto bestScore = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Just a dummy position.

	for (auto effect : effects) {

		/* Perform the action. */
		game.commitAction(effect.action);

		/* The best score the advisary can make. By swaping beta and alpha we
		 * solve the dual problem of MIN-VALUE. */
		const auto advisaryScore = _getBestMove(beta, alpha).second;

		/* The score if the player should choose the action. */
		const auto predictedScore = effect.score - advisaryScore;

		/* Restore the original state. */
		game.undoLastAction();

		/* Analyse the result. */

		/* It the score is better than any previously evaluated, choose it. */
		if (predictedScore > bestScore) {
			bestScore = predictedScore;
			bestAction = effect.action;
		}

		/* If it is also better than beta, then break the loop. */
		if (bestScore >= beta) {
			break;
		}

		alpha = max(alpha, bestScore);
	}

	//XXX Consider a try block, to guarantee that the depth is consistent.
	currentDepth--; //Ascend.

	return pair<OthelloAction,score_t>(bestAction, bestScore);
}

bool BestMoveFinder::actionEffectPairGt(pair<OthelloAction,vector<Position>> p1
		, pair<OthelloAction,vector<Position>> p2)
{
	return p1.second.size() > p2.second.size();
}

} //namespace othello
