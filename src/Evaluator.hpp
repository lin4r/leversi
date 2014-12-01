/**
 * Interface for evaluating reversi actions.
 * Linus Narva
 */
#ifndef EVALUATOR_HPP_
#define EVALUATOR_HPP_

#include "ReversiState.hpp"
#include "ReversiAction.hpp"
#include "Cloneable.hpp"

#include <climits>

namespace reversi {

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
	 * params:
	 *	outcome - containing an action and its flips.
	 *	beforeAction - The state before the action was applied.
	 * return:	An utility score used to order the actions (not the same score
	 *			that is returned bu utility()).
	 */
	virtual score_t moveUtility(const Outcome& outcome
		, const ReversiState& beforeAction) const = 0;

	/**
	 * Utility function for evaluating an reversi state.
	 * params:
	 *	player - The player to calculate the score for.
	 *	state - The state to evaluate.
	 * Return:	The utility score determinig how desireable the state is for
	 *			the player.
	 */
	virtual score_t utility(Player player
		, const ReversiState& state) const = 0;

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

} //namespace reversi

#endif //EVALUATOR_HPP_
