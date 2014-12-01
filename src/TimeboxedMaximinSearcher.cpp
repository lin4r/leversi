/*
 * Implements TemiBoxedActionFinder.hpp
 *
 * Linus Narva
 */
#include "TimeboxedMaximinSearcher.hpp"

#include <chrono>
#include <cmath>

namespace reversi {

ReversiAction TimeboxedMaximinSearcher::maximinAction()
{
	using std::pow;
	using namespace std::chrono;

	auto maxDuration = duration_cast<high_resolution_clock::duration>(
		milliseconds(maxTime_ms));

	const auto t0 = high_resolution_clock::now();
	const auto tExit = t0 + maxDuration;

	auto depth = minDepth;
	auto action = ReversiAction::pass(); //Dummy action.
	time_point<high_resolution_clock> tPredict;

	do {

		setMaxDepth(depth);

		const auto tStart = high_resolution_clock::now();
		action = MaximinSearcher::maximinAction();
		const auto tFinish = high_resolution_clock::now();
		const auto execTime = tFinish - tStart;

		const auto analysis = getAnalysis();
		const auto nodes = analysis.numNodes;
		const auto b = analysis.branchingFactor;

		const auto nodesPredict = nodes + pow(b, depth + 1);
		const auto predictedExecTime =
			duration_cast<high_resolution_clock::duration>(
				(nodesPredict/nodes)*execTime);
		tPredict = tFinish + predictedExecTime;

		depth++;

	} while ((tPredict < tExit) && !action.isPass()
			&& (getMaxDepth() == getAnalysis().reachedDepth)
	);

	const auto usedTime = high_resolution_clock::now() - t0;
	lastRuntime_ms = duration_cast<milliseconds>(usedTime).count();

	return action;
}

} //namespace reversi
