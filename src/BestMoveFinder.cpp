#include "BestMoveFinder.hpp"

#include <utility>
#include <vector>
#include <algorithm>

#include <cassert>

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

BestMoveFinder::BestMoveFinder(const BestMoveFinder& org)
		: maxDepth{org.maxDepth}
		, player{org.player}
		, game(org.game)
		, analysis(org.analysis)
{
	setEvaluator(*(org.evaluator.get()));
}

const BestMoveFinder& BestMoveFinder::operator=(const BestMoveFinder& org)
{
	maxDepth = org.maxDepth;
	player = org.player;
	game = org.game;
	analysis = org.analysis;
	setEvaluator(*(org.evaluator.get()));

	return *this;
}

OthelloAction BestMoveFinder::getBestMove()
{
	analysis = {0,.0,0,-1};

	auto effect = _getBestMove(SCORE_INFIMUM, SCORE_SUPERMUM, 0, player);

	//Approximative.
	analysis.branchingFactor = pow(analysis.numNodes, 1.0/maxDepth);

	analysis.score = effect.score;

	return effect.action;
}

Effect BestMoveFinder::_getBestMove(
		score_t alpha, score_t beta, int depth, Player pl)
{
	assert((SCORE_INFIMUM <= alpha) && (beta <= SCORE_SUPERMUM)
		&& "Alpha and beta are within bounds.");

	assert( ((alpha == SCORE_INFIMUM) || (beta == SCORE_SUPERMUM)
		|| (alpha <= beta))
		&& "Alpha and beta are both initialized, but alpha is larger.");

	analysis.numNodes++;

	/* If the maximum depth is surpassed or the game is over just return. */
	if (depth >= maxDepth || game.refState().isGameOver()) {
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

		assert((SCORE_INFIMUM <= score) && (score <= SCORE_SUPERMUM)
			&& "The score is outside its bounds");

		/* The action is arbitrary. */
		Effect result = {OthelloAction::pass(), score};

		analysis.reachedDepth = max(depth, analysis.reachedDepth);

		return result;
	}

	assert(! game.refState().isGameOver()
		&& "Game over but not a leaf node!");

	auto actionFlipsPairs =
		OthelloAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (actionFlipsPairs.empty()) {

		const pair<OthelloAction,flips_t> passPair(OthelloAction::pass()
			, flips_t());

		actionFlipsPairs.push_back(passPair);
	}

	auto effects = orderActions(actionFlipsPairs);

	assert(std::is_sorted(effects.begin(), effects.end(), isBetter)
		&& "The effects are not in proper order.");

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
	assert(player == pl && "Not the max-player");

	auto value = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto effect : effects) {

		game.commitAction(effect.action);

		const auto minval =
			_getBestMove(alpha, beta, depth+1, advisary(pl)).score;

		game.undoLastAction();

		value = max(value, minval);

		assert((value != SCORE_SUPERMUM)
			&& "The value was not set!");

		if (value >= beta) {
			//The Action doesn't matter.
			break;
		} else if (value > alpha) {
			alpha = value;
			bestAction = effect.action;
		}
	}

	assert(!((depth == 0) && (value >= beta)) 
		&& "The root node is never truncated.");

	assert(((alpha != SCORE_INFIMUM) || (value >= beta))
		&& "Either alpha must be set or the iteration truncated.");

	const Effect bestEffect = {bestAction, value};
	return bestEffect;
}

Effect BestMoveFinder::minValue(score_t alpha, score_t beta, int depth
		, const vector<Effect>& effects, Player pl)
{
	assert(player != pl && "Not the min-player");

	auto value = SCORE_SUPERMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto effect : effects) {

		game.commitAction(effect.action);

		const auto maxval =
			_getBestMove(alpha, beta, depth+1, advisary(pl)).score;

		game.undoLastAction();

		value = min(value, maxval);

		assert((value != SCORE_SUPERMUM)
			&& "The value was not set!");

		if (value <= alpha) {
			//The Action doesn't matter.
			break;
		} else if (value < beta) {
			beta = value;
			bestAction = effect.action;
		}
	}

	assert(((beta != SCORE_SUPERMUM) || (value <= alpha))
		&& "Either beta must be set or the iteration truncated.");

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
