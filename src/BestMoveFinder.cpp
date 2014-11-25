#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;
using std::max;
using std::min;
using std::pow;

namespace othello {

static inline bool isBetter(Effect e1, Effect e2) noexcept;

BestMoveFinder::BestMoveFinder(Player player, Game game)
		: player{player}
		, game(game)
{}

OthelloAction BestMoveFinder::getBestMove()
{
	analysis = {0,.0,0};

	auto effect = _getBestMove(SCORE_INFIMUM, SCORE_SUPERMUM, 0, player);

	//Approximative.
	analysis.branchingFactor = pow(analysis.numNodes, 1.0/maxDepth);

	analysis.score = effect.score;

	return effect.action;
}

Effect BestMoveFinder::_getBestMove(
		score_t alpha, score_t beta, int depth, Player pl)
{
	analysis.numNodes++;

	/* If the maximum depth is surpassed or the game is over just return. */
	if (depth > maxDepth || game.getState().isGameOver()) {
		/* The 'action is irrelevant since it will never be executed
		 * so long as the maxDepth is valid.' */

		/* XXX Utility function, Evaluators duty! */
		score_t blackScore{0};
		for (auto tile : game.refState().constBoardIterator()) {

			switch (tile) {
			case Tile::Black: blackScore++; break;
			case Tile::White: blackScore--; break;
			default: ;
			}
		}

		/* Zero sum rule. */
		const auto score = (player == Player::Black)
			? blackScore : -blackScore;

		/* The action is arbitrary. */
		Effect result = {OthelloAction::pass(), score};
		return result;
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

	Effect bestEffect = {OthelloAction::pass(), 0};
	if (player == pl) {
		bestEffect = maxValue(alpha, beta, depth, effects, pl);
	} else {
		bestEffect = minValue(alpha, beta, depth, effects, pl);
	}

	return bestEffect;
}

Effect BestMoveFinder::maxValue(score_t alpha, score_t beta, int depth
		, const vector<Effect>& effects, Player pl)
{
	auto value = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto effect : effects) {

		value = max(value
			, _getBestMove(alpha, beta, depth+1, advisary(pl)).score);

		if (value >= beta) {
			//The Action doesn't matter.
			break;
		} else if (value > alpha) {
			alpha = value;
			bestAction = effect.action;
		}
	}

	const Effect bestEffect = {bestAction, value};
	return bestEffect;
}

Effect BestMoveFinder::minValue(score_t alpha, score_t beta, int depth
		, const vector<Effect>& effects, Player pl)
{
	auto value = SCORE_SUPERMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto effect : effects) {

		value = min(value
			, _getBestMove(alpha, beta, depth+1, advisary(pl)).score);

		if (value <= alpha) {
			//The Action doesn't matter.
			break;
		} else if (value < beta) {
			beta = value;
			bestAction = effect.action;
		}
	}

	const Effect bestEffect = {bestAction, value};
	return bestEffect;
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
