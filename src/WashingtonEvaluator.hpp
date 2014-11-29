/**
 * Evaluator based on this article:
 *
 * An Analysis of Heuristics in Othello
 * Vaishnavi Sannidhanam and Muthukaruppan Annamalai
 * Department of Computer Science and Engineering
 * Seattle, WA-98195
 *
 * Linus Narva
 */
#ifndef WASHINGTON_EVALUATOR_HPP_
#define WASHINGTON_EVALUATOR_HPP_

#include "Evaluator.hpp"

namespace othello {

class WashingtonEvaluator : public Evaluator
{
public:

	virtual ~WashingtonEvaluator() = default;

	/**
	 * Counts the increase in tiles of the colour (1 + 2*#flips).
	 */
	virtual score_t moveUtility(const Outcome& outcome
			, const OthelloState& beforeAction)
			const override;

	/**
	 * Simply calculates #player bricks - #adisary bricks.
	 */
	virtual score_t utility(Player player, const OthelloState& state)
			const override;

	virtual std::unique_ptr<Evaluator> clone() const override;
};

} //namespace othello

#endif //WASHINGTON_EVALUATOR_HPP_
