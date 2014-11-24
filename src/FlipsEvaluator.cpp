#include "FlipsEvaluator.hpp"

namespace othello {

score_t FlipsEvaluator::evaluateAction(const OthelloAction& action
		, const flips_t& flips, const OthelloState& beforeAction)
{
	if (action.isPass()) {

		/* A pass gives zero points because no brick is flipped. */
		return 0;

	} else {

		/* The score contribution is how much the number of bricks of the
		 * players colour increased. A flip gives two points e.g. one mor black
		 * brick and one less white brick on the board (if the player is
		 * black). Also one point is added for the placed brick.
		 */
		return flips.size()*2 + 1;
	}
}

} //namespace othello
