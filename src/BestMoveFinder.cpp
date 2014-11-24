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

static inline bool isBetter(Effect e1, Effect e2) noexcept;

BestMoveFinder::BestMoveFinder(Game game) : game(game)
{}

pair<OthelloAction, score_t> BestMoveFinder::getBestMove()
{
	return _getBestMove(SCORE_INFIMUM, SCORE_SUPERMUM, 0);
}

pair<OthelloAction, score_t> BestMoveFinder::_getBestMove(
		score_t alpha, score_t beta, int depth)
{
	/* If the maximum depth is surpassed or the game is over just return. */
	if (depth > maxDepth || game.getState().isGameOver()) {
		/* The 'action is irrelevant since it will never be executed
		 * so long as the maxDepth is valid.' */
		return pair<OthelloAction, score_t>(OthelloAction::pass(), 0);
	}

	auto actionFlipsPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (actionFlipsPairs.empty()) {

		const pair<OthelloAction,flips_t> passPair(OthelloAction::pass()
			, flips_t());

		actionFlipsPairs.push_back(passPair);
	}

	auto effects = orderActions(actionFlipsPairs);

	auto bestScore = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Just a dummy position.

	for (auto effect : effects) {

		/* Perform the action. */
		game.commitAction(effect.action);

		/* The best score the advisary can make. By swaping beta and alpha we
		 * solve the dual problem of MIN-VALUE. */
		const auto advisaryScore = _getBestMove(beta, alpha, depth+1).second;

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

	return pair<OthelloAction,score_t>(bestAction, bestScore);
}

vector<Effect> BestMoveFinder::orderActions(
		const vector<pair<OthelloAction, flips_t>>& actionFlipsPairs)
{
	using std::sort;

	/* Computes the score obtained by each of the actions. */
	vector<Effect> effects;
	for (auto actionFlipsPair : actionFlipsPairs) {

		/* Unpack. */
		const auto& action = actionFlipsPair.first;
		const auto& flips = actionFlipsPair.second;

		const auto score = evaluator->evaluateAction(action, flips
			, game.refState());

		const Effect effect = {action, score};

		effects.push_back(effect);
	}

	/* Sort the vector so that moves with high scores comes first. */
	sort(effects.begin(), effects.end(), isBetter);

	return effects;
}

/* Large effects are desireable and therefore comes first. */
bool isBetter(Effect e1, Effect e2) noexcept
{
	return e1.score > e2.score;
}

} //namespace othello
