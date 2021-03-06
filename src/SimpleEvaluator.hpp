/**
 * Evaluator conunting how many more bricks the player has than the adviary.
 *
 * Linus Narva
 */
#ifndef SIMPLE_EVALUATOR_HPP_
#define SIMPLE_EVALUATOR_HPP_

#include "Evaluator.hpp"

namespace reversi {

class SimpleEvaluator : public Evaluator
{
public:

	virtual ~SimpleEvaluator() = default;

	/**
	 * Counts the increase in tiles of the colour (1 + 2*#flips).
	 */
	virtual score_t moveUtility(const Outcome& outcome
			, const ReversiState& beforeAction)
			const override;

	/**
	 * Simply calculates #player bricks - #adisary bricks.
	 */
	virtual score_t utility(Player player, const ReversiState& state)
			const override;

	virtual std::unique_ptr<Evaluator> clone() const override;
};

} //namespace reversi

#endif //SIMPLE_EVALUATOR_HPP_
