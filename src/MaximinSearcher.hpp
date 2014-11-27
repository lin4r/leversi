/**
 * Maximin search for the most rational action, considering a given amount of
 * steps in the future. The implementation uses alpha-beta pruning with move
 * ordering.
 *
 * Linus Narva
 */
#ifndef MAXIMIN_SEARCHER_HPP_
#define MAXIMIN_SEARCHER_HPP_

#include "Game.hpp"
#include "OthelloAction.hpp"
#include "Evaluator.hpp"
#include "SimpleEvaluator.hpp"

#include <memory>

namespace othello {

struct RankedAction
{
	OthelloAction action;
	score_t score;
};

/* Analysis data for a run of the algorithm. */
struct Analysis
{
	int numNodes;			/* Number of expanded nodes (including root). */
	double branchingFactor; /* Aproximative branching factor nodes^(1/depth) */
	score_t predictedScore;	/* Predicted score of the action. */
	int reachedDepth;		/* The max depth that ocurred. */
};

class MaximinSearcher {
public:

	/**
	 * params:
	 *	game - The game to search the next maximin optimal action in.
	 */
	MaximinSearcher(Game game);
	virtual ~MaximinSearcher() = default;

	MaximinSearcher(const MaximinSearcher& org);
	virtual const MaximinSearcher& operator=(const MaximinSearcher& org);

	/**
	 * Computes the maximin action.
	 * Return:	The maximin action.
	 */
	virtual OthelloAction maximinAction(); //XXX Rename getBestAction

	/**
	 * Gets the maximum recursive depth.
	 * Return:	max depth.
	 */
	virtual int getMaxDepth() const noexcept { return maxDepth; }

	/** 
	 * Sets the maximum recursive depth.
	 * param:	max depth.
	 */
	virtual void setMaxDepth(int newDepth) noexcept
		{ maxDepth = newDepth; }

	/**
	 * Sets the evaluator.
	 * param:	Polumorphic reference to an evaluator. The set value will be a
	 *			clone.
	 */
	virtual void setEvaluator(const Evaluator& newEvaluator)
		{ evaluator = std::move(newEvaluator.clone()); }

	/**
	 * Gets the analysis of the last minmaxAction() call.
	 */
	virtual Analysis getAnalysis() const noexcept
		{ return analysis; }

	/**
	 * Gets the max maxPlayer. The player is whoever's tur it is in the game.
	 * return:	The maxPlayer.
	 */
	virtual Player getPlayer() const noexcept
		{ return maxPlayer; }

private:

	/**
	 * Performs move ordering. The evaluator will assign each action a score
	 * used for the ordering.
	 * param:	Outcomes of the actions (the action itself and flips).
	 * return:	The actions along eith their assigned score.
	 */
	std::vector<RankedAction> orderActions(
		const std::vector<Outcome>& outcomes);

	/**
	 * Subfunction of maximinAction(). It takes care of termination and move
	 * ordering and then calls maxValue() or minValue().
	 * params:
	 *	alpha -	Alpha value in alpha-beta pruning.
	 *	beta - Beta value in alpha-beta pruning.
	 *	depth - Recursive depth.
	 * return:	The maximin action along with it's predicted score.
	 */
	RankedAction _maximinAction(score_t alpha, score_t beta, int depth);

	/**
	 * Expands a max node.
	 * params:
	 *	alpha -	Alpha value in alpha-beta pruning.
	 *	beta - Beta value in alpha-beta pruning.
	 *	depth - Recursive depth.
	 *	rankedActions - actions search in along with an arbitrary score.
	 */
	RankedAction maxValue(score_t alpha, score_t beta, int depth
		, const std::vector<RankedAction>& rankedActions);


	/**
	 * Expands a min node.
	 * params:
	 *	alpha -	Alpha value in alpha-beta pruning.
	 *	beta - Beta value in alpha-beta pruning.
	 *	depth - Recursive depth.
	 *	rankedActions - actions search in along with an arbitrary score.
	 */
	RankedAction minValue(score_t alpha, score_t beta, int depth
		, const std::vector<RankedAction>& rankedActions);

	/**
	 * Maximum recursive depth.
	 */
	int maxDepth{5};

	/**
	 * The max maxPlayer.
	 */
	Player maxPlayer;

	/**
	 * The game to search in.
	 */
	Game game;

	/**
	 * Analysis data for the latest run of minimaxAction.
	 */
	Analysis analysis;

	/**
	 * Polumorphic evaluator pointer.
	 */
	std::unique_ptr<Evaluator> evaluator{new SimpleEvaluator()};
};

} //namespace othello

#endif //MAXIMIN_SEARCHER_HPP_
