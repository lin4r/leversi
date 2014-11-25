#ifndef BEST_MOVE_FINDER_
#define BEST_MOVE_FINDER_

#include "Game.hpp"
#include "OthelloAction.hpp"
#include "Evaluator.hpp"
#include "FlipsEvaluator.hpp"

#include <climits>
#include <memory>

namespace othello {

struct Effect
{
	OthelloAction action;
	score_t score;
};

struct Analysis
{
	int numNodes;
	double branchingFactor;
	score_t score;
};

class BestMoveFinder {
public:

	BestMoveFinder(Game game);
	virtual ~BestMoveFinder() = default;

	virtual OthelloAction getBestMove();

	virtual int getMaxDepth() const noexcept { return maxDepth; }

	//XXX Should guard agins invalid values.
	virtual void setMaxDepth(int newDepth) noexcept
			{ maxDepth = newDepth; }

	virtual void setEvaluator(const Evaluator& newEvaluator)
		{ evaluator = std::move(newEvaluator.clone()); }

	virtual Analysis getAnalysis() const noexcept
		{ return analysis; }

private:

	std::vector<Effect> orderActions(
		const std::vector<std::pair<OthelloAction, flips_t>>&
			actionFlipsPairs);

	std::pair<OthelloAction, score_t> _getBestMove(score_t alpha
		, score_t beta, int depth);

	int maxDepth{5};

	Game game;

	Analysis analysis;

	std::unique_ptr<Evaluator> evaluator{new FlipsEvaluator()};
};

} //namespace othello

#endif //BEST_MOVE_FINDER_
