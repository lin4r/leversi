/* Uses iteratove deepening to timebox BestActionFinder.
 *
 * Linus Narva
 */
#ifndef TIMEBOXED_MAXIMIN_SEARCHER_HPP_
#define TIMEBOXED_MAXIMIN_SEARCHER_HPP_

#include "MaximinSearcher.hpp"
#include "OthelloAction.hpp"

namespace othello {

class TimeboxedMaximinSearcher : public MaximinSearcher
{
public:

	TimeboxedMaximinSearcher(int minDepth, int maxTime_ms
			, MaximinSearcher finder)
			: MaximinSearcher(finder)
			, minDepth{minDepth}
			, maxTime_ms{maxTime_ms}
	{}

	virtual ~TimeboxedMaximinSearcher() = default;

	virtual OthelloAction maximinAction() override;

private:

	bool predictTime(int ellapsed_ms, int depth, int branchingFactor)
		const noexcept;

	int minDepth;
	int maxTime_ms;
};

} //namespace othello

#endif //TIMEBOXED_MAXIMIN_SEARCHER_HPP_
