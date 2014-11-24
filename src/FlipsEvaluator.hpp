/*
 * Evaluator based on hom many flips are caused.
 *
 * Linus Narva
 */
#ifndef FLIPS_EVALUATOR_HPP_
#define FLIPS_EVALUATOR_HPP_

#include "Evaluator.hpp"

namespace othello {

class FlipsEvaluator : public Evaluator
{
public:

	virtual ~FlipsEvaluator() = default;

	/* Counts the flips and adds one (because the placed tile gives one point). */
	virtual score_t evaluateAction(const OthelloAction& action
		, const flips_t& flips, const OthelloState& beforeAction) override;
};

} //namespace othello

#endif //FLIPS_EVALUATOR_HPP_
