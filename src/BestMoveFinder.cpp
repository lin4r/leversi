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
using std::pow;

namespace othello {

static inline bool isBetter(Effect e1, Effect e2) noexcept;

BestMoveFinder::BestMoveFinder(Game game) : game(game)
{}

OthelloAction BestMoveFinder::getBestMove()
{
	analysis = {0,.0,0};

	auto actionAndScore = _getBestMove(SCORE_INFIMUM, SCORE_SUPERMUM, 0);

	//Approximative.
	analysis.branchingFactor = pow(analysis.numNodes, 1.0/maxDepth);

	analysis.score = actionAndScore.second;

	return actionAndScore.first;
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

	analysis.numNodes++;

	auto actionFlipsPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (actionFlipsPairs.empty()) {

		const pair<OthelloAction,flips_t> passPair(OthelloAction::pass()
			, flips_t());

		actionFlipsPairs.push_back(passPair);
	}

	auto effects = orderActions(actionFlipsPairs);

	auto predictedScore = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto effect : effects) {

		game.commitAction(effect.action);
		const auto advisaryScore = _getBestMove(-beta, -alpha, depth+1).second;
		game.undoLastAction();

		predictedScore = max(predictedScore, effect.score - advisaryScore);

		if (predictedScore >= beta) {
			//The action doesn't matter since it won't be chosen.
			break;
		} else if (predictedScore > alpha) {
			alpha = max(alpha, predictedScore);
			bestAction = effect.action;
		}
	}

	return pair<OthelloAction,score_t>(bestAction, predictedScore);
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
