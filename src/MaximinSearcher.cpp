#include "MaximinSearcher.hpp"

#include <vector>
#include <algorithm>

#include <cassert>

using std::vector;
using std::max;
using std::min;
using std::pow;

namespace reversi {

static bool rankedActionOrder(const RankedAction& action1
	, const RankedAction& action2) noexcept;

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

ReversiAction MaximinSearcher::maximinAction()
{
	analysis = {0,.0,0,-1}; /* Clear the previous analysis (if any). */

	auto rankedAction = _maximinAction(SCORE_INFIMUM, SCORE_SUPERMUM, 0);

	//Approximative.
	analysis.branchingFactor = pow(analysis.numNodes, 1.0/maxDepth);
	analysis.predictedScore = rankedAction.score;

	return rankedAction.action;
}

RankedAction MaximinSearcher::_maximinAction(score_t alpha, score_t beta
		, int depth)
{
	analysis.numNodes++;

	assert( ((alpha == SCORE_INFIMUM) || (beta == SCORE_SUPERMUM)
		|| (alpha <= beta))
		&& "If both are initialized then beta cant be lower than alpha.");

	/* If the maximum depth is surpassed or the game is over just return. */
	if (depth >= maxDepth || game.refState().isGameOver()) {

		const auto score = evaluator->utility(maxPlayer, game.refState());

		ReversiAction arbitraryAction(Position(-1,-1));
		RankedAction result = {arbitraryAction, score};

		analysis.reachedDepth = max(depth, analysis.reachedDepth);

		return result;
	}

	auto outcomes = ReversiAction::findLegalPlacements(game.getState());

	/* Handle pass. */
	if (outcomes.empty()) {

		const auto pass = ReversiAction::pass();
		const flips_t noFlips;

		const Outcome outcome = {pass, noFlips};

		outcomes.push_back(outcome);
	}

	auto rankedActions = orderActions(outcomes);

	assert(std::is_sorted(rankedActions.begin(), rankedActions.end()
		, rankedActionOrder)
		&& "The rankedActions are not in proper order.");

	RankedAction bestRankedAction = {ReversiAction::pass(), 0};
	if (maxPlayer == game.refState().whosTurn()) {
		bestRankedAction = maxValue(alpha, beta, depth, rankedActions);
	} else {
		bestRankedAction = minValue(alpha, beta, depth, rankedActions);
	}

	return bestRankedAction;
}

RankedAction MaximinSearcher::maxValue(score_t alpha, score_t beta, int depth
		, const vector<RankedAction>& rankedActions)
{
	assert(maxPlayer == game.refState().whosTurn()
		&& "Must be the max players turn in a max node.");

	auto value = SCORE_INFIMUM;
	ReversiAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto rankedAction : rankedActions) {

		game.commitAction(rankedAction.action);

		const auto minval = _maximinAction(alpha, beta, depth+1).score;

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
		, const vector<RankedAction>& rankedActions)
{
	assert(maxPlayer != game.refState().whosTurn()
		&& "Must be the minplayers turn in a min node.");

	auto value = SCORE_SUPERMUM;
	ReversiAction bestAction(Position(-1,-1)); //Dummy action.

	for (auto rankedAction : rankedActions) {

		game.commitAction(rankedAction.action);

		const auto maxval = _maximinAction(alpha, beta, depth+1).score;

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
		const vector<Outcome>& outcomes)
{
	using std::sort;

	/* Computes the score obtained by each of the actions. */
	vector<RankedAction> rankedActions;
	for (auto outcome : outcomes) {

		const auto score = evaluator->moveUtility(outcome, game.refState());

		const RankedAction rankedAction = {outcome.action, score};

		rankedActions.push_back(rankedAction);
	}

	/* Sort the vector so that moves with high scores comes first. */
	sort(rankedActions.begin(), rankedActions.end(), rankedActionOrder);

	return rankedActions;
}

/* Large rankedActions are desireable and therefore comes first. */
bool rankedActionOrder(const RankedAction& action1
		, const RankedAction& action2) noexcept
{
	return action1.score > action2.score;
}

} //namespace reversi
