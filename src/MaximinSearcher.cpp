#include "MaximinSearcher.hpp"

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

static inline bool isBetter(RankedAction e1, RankedAction e2) noexcept;

MaximinSearcher::MaximinSearcher(Game game)
		: game(game)
{
	maxPlayer = game.refState().whosTurn();
}

MaximinSearcher::MaximinSearcher(const MaximinSearcher& org)
		: maxDepth{org.maxDepth}
		, maxPlayer{org.maxPlayer}
		, game(org.game)
		, analysis(org.analysis)
{
	setEvaluator(*(org.evaluator.get()));
}

const MaximinSearcher& MaximinSearcher::operator=(const MaximinSearcher& org)
{
	maxDepth = org.maxDepth;
	maxPlayer = org.maxPlayer;
	game = org.game;
	analysis = org.analysis;
	setEvaluator(*(org.evaluator.get()));

	return *this;
}

OthelloAction MaximinSearcher::maximinAction()
{
	analysis = {0,.0,0,-1};

	auto rankedAction = _maximinAction(SCORE_INFIMUM, SCORE_SUPERMUM, 0, maxPlayer);

	//Approximative.
	analysis.branchingFactor = pow(analysis.numNodes, 1.0/maxDepth);

	analysis.predictedScore = rankedAction.score;

	return rankedAction.action;
}

RankedAction MaximinSearcher::_maximinAction(
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

		const auto blackScore = evaluator->utility(game.refState());

		/* Zero sum rule. */
		const auto score = (maxPlayer == Player::Black)
			? blackScore : -blackScore;

		assert((SCORE_INFIMUM <= score) && (score <= SCORE_SUPERMUM)
			&& "The score is outside its bounds");

		/* The action is arbitrary. */
		RankedAction result = {OthelloAction::pass(), score};

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

	auto rankedActions = orderActions(actionFlipsPairs);

	assert(std::is_sorted(rankedActions.begin(), rankedActions.end(), isBetter)
		&& "The rankedActions are not in proper order.");

	RankedAction bestRankedAction = {OthelloAction::pass(), 0};
	if (maxPlayer == pl) {
		bestRankedAction = maxValue(alpha, beta, depth, rankedActions, pl);
	} else {
		bestRankedAction = minValue(alpha, beta, depth, rankedActions, pl);
	}

	return bestRankedAction;
}

RankedAction MaximinSearcher::maxValue(score_t alpha, score_t beta, int depth
		, const vector<RankedAction>& rankedActions, Player pl)
{
	assert(maxPlayer == pl && "Not the max-maxPlayer");

	auto value = SCORE_INFIMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto rankedAction : rankedActions) {

		game.commitAction(rankedAction.action);

		const auto minval =
			_maximinAction(alpha, beta, depth+1, advisary(pl)).score;

		game.undoLastAction();

		value = max(value, minval);

		assert((value != SCORE_SUPERMUM)
			&& "The value was not set!");

		if (value >= beta) {
			//The Action doesn't matter.
			break;
		} else if (value > alpha) {
			alpha = value;
			bestAction = rankedAction.action;
		}
	}

	assert(!((depth == 0) && (value >= beta)) 
		&& "The root node is never truncated.");

	assert(((alpha != SCORE_INFIMUM) || (value >= beta))
		&& "Either alpha must be set or the iteration truncated.");

	const RankedAction bestRankedAction = {bestAction, value};
	return bestRankedAction;
}

RankedAction MaximinSearcher::minValue(score_t alpha, score_t beta, int depth
		, const vector<RankedAction>& rankedActions, Player pl)
{
	assert(maxPlayer != pl && "Not the min-maxPlayer");

	auto value = SCORE_SUPERMUM;
	OthelloAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto rankedAction : rankedActions) {

		game.commitAction(rankedAction.action);

		const auto maxval =
			_maximinAction(alpha, beta, depth+1, advisary(pl)).score;

		game.undoLastAction();

		value = min(value, maxval);

		assert((value != SCORE_SUPERMUM)
			&& "The value was not set!");

		if (value <= alpha) {
			//The Action doesn't matter.
			break;
		} else if (value < beta) {
			beta = value;
			bestAction = rankedAction.action;
		}
	}

	assert(((beta != SCORE_SUPERMUM) || (value <= alpha))
		&& "Either beta must be set or the iteration truncated.");

	const RankedAction bestRankedAction = {bestAction, value};
	return bestRankedAction;
}

vector<RankedAction> MaximinSearcher::orderActions(
		const vector<pair<OthelloAction, flips_t>>& actionFlipsPairs)
{
	using std::sort;

	/* Computes the score obtained by each of the actions. */
	vector<RankedAction> rankedActions;
	for (auto actionFlipsPair : actionFlipsPairs) {

		/* Unpack. */
		const auto& action = actionFlipsPair.first;
		const auto& flips = actionFlipsPair.second;

		const auto score = evaluator->moveUtility(action, flips
			, game.refState());

		const RankedAction rankedAction = {action, score};

		rankedActions.push_back(rankedAction);
	}

	/* Sort the vector so that moves with high scores comes first. */
	sort(rankedActions.begin(), rankedActions.end(), isBetter);

	return rankedActions;
}

/* Large rankedActions are desireable and therefore comes first. */
bool isBetter(RankedAction e1, RankedAction e2) noexcept
{
	return e1.score > e2.score;
}

} //namespace othello
