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

/* Score type along with bound definitions. */
typedef int score_t;
const score_t SCORE_INFIMUM{INT_MIN};
const score_t SCORE_SUPERMUM{INT_MAX};

class Evaluator : Cloneable<Evaluator>
{
public:

	virtual ~Evaluator() = default;

	/**
	 * Used for move-ordering. Should be cheap compared to utility().
	 */
	virtual score_t moveUtility(const OthelloAction& action
		, const flips_t& flips, const OthelloState& beforeAction) const = 0;

	/**
	 * Utility function for evaluating an othello state. Specifically the score
	 * of the black player.
	 */
	virtual score_t utility(const OthelloState& state) const = 0;

	/**
	 * Clone can be used to implement polymorphic set functions. e.g:
	 *
	 *	std::unique_ptr<Evaluator> evaluatorPointer;
	 *
	 *	void setEvaluator(const Evaluator& polymorficReference)
	 *	{
	 *		this->evaluatorPointer = std::move(polymorficReference.clone());
	 *	}
	 */
	virtual std::unique_ptr<Evaluator> clone() const override = 0;
};

} //namespace othello

#endif //EVALUATOR_HPP_
