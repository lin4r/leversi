/* Uses iteratove deepening to timebox BestActionFinder.
 *
 * Linus Narva
 */
#ifndef TIME_BOXED_ACTION_FINDER_HPP_
#define TIME_BOXED_ACTION_FINDER_HPP_

#include "MaximinSearcher.hpp"
#include "OthelloAction.hpp"

namespace othello {

class TimeBoxedActionFinder : public MaximinSearcher
{
public:

	TimeBoxedActionFinder(int minDepth, int maxTime_ms, MaximinSearcher finder)
			: MaximinSearcher(finder)
			, minDepth{minDepth}
			, maxTime_ms{maxTime_ms}
	{}

	virtual ~TimeBoxedActionFinder() = default;

	virtual OthelloAction maximinAction() override;

private:

	bool predictTime(int ellapsed_ms, int depth, int branchingFactor)
		const noexcept;

	int minDepth;
	int maxTime_ms;
};

} //namespace othello

#endif //TIME_BOXED_ACTION_FINDER_HPP_
