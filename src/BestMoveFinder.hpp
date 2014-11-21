#ifndef BEST_MOVE_FINDER_
#define BEST_MOVE_FINDER_

#include "Game.hpp"
#include "OthelloAction.hpp"

#include <climits>

namespace othello {

typedef int score_t;
const score_t SCORE_INFIMUM{INT_MIN};

class BestMoveFinder {
public:

	BestMoveFinder(Game game);
	virtual ~BestMoveFinder() = default;

	virtual std::pair<OthelloAction, score_t> getBestMove();

private:

	/* XXX Later this should be the evaluators duty. */
	static bool actionEffectPairLt(
		std::pair<OthelloAction,std::vector<Position>> p1
		, std::pair<OthelloAction,std::vector<Position>> p2);

	static score_t getScoreInfimum();

	Game game;
};

} //namespace othello

#endif //BEST_MOVE_FINDER_
