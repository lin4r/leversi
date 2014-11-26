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

	BestMoveFinder(Player player, Game game);
	virtual ~BestMoveFinder() = default;

	BestMoveFinder(const BestMoveFinder& org);
	virtual const BestMoveFinder& operator=(const BestMoveFinder& org);

	virtual OthelloAction getBestMove(); //XXX Rename getBestAction

	virtual int getMaxDepth() const noexcept { return maxDepth; }

	//XXX Should guard agins invalid values.
	virtual void setMaxDepth(int newDepth) noexcept
		{ maxDepth = newDepth; }

	virtual void setEvaluator(const Evaluator& newEvaluator)
		{ evaluator = std::move(newEvaluator.clone()); }

	virtual Analysis getAnalysis() const noexcept
		{ return analysis; }

	virtual Player getPlayer() const noexcept
		{ return player; }

	virtual void setPlayer(Player newPlayer) noexcept
		{ player = newPlayer; }

private:

	std::vector<Effect> orderActions(
		const std::vector<std::pair<OthelloAction, flips_t>>&
			actionFlipsPairs);

	Effect _getBestMove(score_t alpha
		, score_t beta, int depth, Player pl);

	Effect maxValue(score_t alpha, score_t beta, int depth
		, const std::vector<Effect>& effects, Player pl);
	Effect minValue(score_t alpha, score_t beta, int depth
		, const std::vector<Effect>& effects, Player pl);

	int maxDepth{5};

	Player player;

	Game game;

	Analysis analysis;

	std::unique_ptr<Evaluator> evaluator{new FlipsEvaluator()};
};

} //namespace othello

#endif //BEST_MOVE_FINDER_
