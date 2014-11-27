#include "SimpleEvaluator.hpp"

using std::unique_ptr;

namespace othello {

score_t SimpleEvaluator::moveUtility(const OthelloAction& action
		, const flips_t& flips, const OthelloState& beforeAction) const
{
	if (action.isPass()) {

		/* A pass gives zero points because no brick is flipped. */
		return 0;

	} else {

		return flips.size()*2 + 1;
	}
}

score_t SimpleEvaluator::utility(const OthelloState& state) const
{
	score_t blackScore{0};
	for (auto tile : state.constBoardIterator()) {

		switch (tile) {
		case Tile::Black: blackScore++; break;
		case Tile::White: blackScore--; break;
		default: ;
		}
	}

	return blackScore;
}

unique_ptr<Evaluator> SimpleEvaluator::clone() const
{
	return unique_ptr<Evaluator>(new SimpleEvaluator(*this));
}

} //namespace othello