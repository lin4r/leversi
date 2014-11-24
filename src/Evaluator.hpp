/*
 * Interface for evaluating othello actions.
 * Linus Narva
 */
#ifndef EVALUATOR_HPP_
#define EVALUATOR_HPP_

#include "OthelloState.hpp"
#include "OthelloAction.hpp"
#include "Cloneable.hpp"

#include <climits>

namespace othello {

typedef int score_t;
const score_t SCORE_INFIMUM{INT_MIN};
const score_t SCORE_SUPERMUM{INT_MAX};

class Evaluator : Cloneable<Evaluator>
{
public:

	virtual ~Evaluator() = default;

	virtual score_t evaluateAction(const OthelloAction& action
		, const flips_t& flips, const OthelloState& beforeAction) = 0;

	virtual std::unique_ptr<Evaluator> clone() const override = 0;
};

} //namespace othello

#endif //EVALUATOR_HPP_
