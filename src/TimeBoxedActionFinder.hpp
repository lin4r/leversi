/* Uses iteratove deepening to timebox BestActionFinder.
 *
 * Linus Narva
 */
#ifndef TIME_BOXED_ACTION_FINDER_HPP_
#define TIME_BOXED_ACTION_FINDER_HPP_

#include "BestMoveFinder.hpp"
#include "OthelloAction.hpp"

namespace othello {

class TimeBoxedActionFinder : public BestMoveFinder
{
public:

	TimeBoxedActionFinder(int minDepth, int maxTime_ms, BestMoveFinder finder)
			: BestMoveFinder(finder)
			, minDepth{minDepth}
			, maxTime_ms{maxTime_ms}
	{}

	virtual ~TimeBoxedActionFinder() = default;

	//XXX Rename getBestAction.
	virtual OthelloAction getBestMove() override;

private:

	bool predictTime(int ellapsed_ms, int depth, int branchingFactor)
		const noexcept;

	int minDepth;
	int maxTime_ms;
};

} //namespace othello

#endif //TIME_BOXED_ACTION_FINDER_HPP_
