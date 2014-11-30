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

	/**
	 * Gets the execution time of last run.
	 * return:	The execution time of the last run in millisecounds or -1
	 *			no run has been executed by this evaluator yet.
	 */
	virtual int getLastRuntime_ms() const noexcept
		{ return lastRuntime_ms; };

private:

	int minDepth;
	int maxTime_ms;
	int lastRuntime_ms{-1};
};

} //namespace othello

#endif //TIMEBOXED_MAXIMIN_SEARCHER_HPP_
