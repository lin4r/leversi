/*
 * Implements TemiBoxedActionFinder.hpp
 *
 * Linus Narva
 */
#include "TimeBoxedActionFinder.hpp"

#include <chrono>
#include <cmath>

namespace othello {

OthelloAction TimeBoxedActionFinder::getBestMove()
{
	using std::pow;
	using namespace std::chrono;

	auto maxDuration = duration_cast<high_resolution_clock::duration>(
		milliseconds(maxTime_ms));

	const auto t0 = high_resolution_clock::now();
	const auto tExit = t0 + maxDuration;

	auto depth = minDepth;
	auto action = OthelloAction::pass(); //Dummy action.
	time_point<high_resolution_clock> tPredict;

	do {

		setMaxDepth(depth);

		const auto tStart = high_resolution_clock::now();
		action = BestMoveFinder::getBestMove();
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

	} while ((tPredict < tExit) && (! action.isPass()));

// Useful code for debugging.
//	const auto analysis = getAnalysis();
//	const auto usedTime = high_resolution_clock::now() - t0;
//	cerr << "*** Analysis ***" << endl
//		<<  "player:           " << getPlayer() << endl
//		<<  "nodes:            " << analysis.numNodes << endl
//		<<  "branching factor: " << analysis.branchingFactor << endl
//		<<  "score:            " << analysis.score << endl
//		<<  "Time used (s):    "
//			<< duration_cast<milliseconds>(usedTime).count()/1000.0 << endl
//		<<  "Depth:               " << analysis.reachedDepth << endl
//		<<  "MaxDepth:            " << getMaxDepth() << endl
//		<<  "****************" << endl;

	return action;
}

} //namespace othello
