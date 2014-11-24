#ifndef BEST_MOVE_FINDER_
#define BEST_MOVE_FINDER_

#include "Game.hpp"
#include "OthelloAction.hpp"
#include "Evaluator.hpp"
#include "FlipsEvaluator.hpp"

#include <climits>
#include <memory>

namespace othello {

class BestMoveFinder {
public:

	BestMoveFinder(Game game);
	virtual ~BestMoveFinder() = default;

	virtual std::pair<OthelloAction, score_t> getBestMove();

	virtual int getMaxDepth() const noexcept { return maxDepth; }

	//XXX Should guard agins invalid values.
	virtual void setMaxDepth(int newDepth) noexcept
			{ maxDepth = newDepth; }

private:

	virtual std::pair<OthelloAction, score_t> _getBestMove(score_t alpha
		, score_t beta);

	int currentDepth{0}; //XXX Should be a argument to _getBestMove
	int maxDepth{6};

	/* XXX Later this should be the evaluators duty. */
	static bool actionEffectPairGt(
		std::pair<OthelloAction,flips_t> p1
		, std::pair<OthelloAction,flips_t> p2);

	Game game;

	FlipsEvaluator evaluator;
};

} //namespace othello

#endif //BEST_MOVE_FINDER_
