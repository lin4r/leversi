#include "SimpleEvaluator.hpp"

using std::unique_ptr;

namespace othello {

score_t SimpleEvaluator::moveUtility(const Outcome& outcome
		, const OthelloState& beforeAction) const
{
	if (outcome.action.isPass()) {

		/* A pass gives zero points because no brick is flipped. */
		return 0;

	} else {

		/* The direct increase in bricks if tha action is chosen. */
		return outcome.flips.size()*2 + 1;
	}
}

score_t SimpleEvaluator::utility(Player player
		, const OthelloState& state) const
{
	score_t blackScore{0};
	for (auto tile : state.constBoardIterator()) {

		switch (tile) {
		case Tile::Black: blackScore++; break;
		case Tile::White: blackScore--; break;
		default: ;
		}
	}

	/* Use the zero sum rule. */
	return (player == Player::Black) ? blackScore : -blackScore;
}

unique_ptr<Evaluator> SimpleEvaluator::clone() const
{
	return unique_ptr<Evaluator>(new SimpleEvaluator(*this));
}

} //namespace othello
