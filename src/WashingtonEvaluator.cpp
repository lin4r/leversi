#include "WashingtonEvaluator.hpp"

#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <cassert>

using std::unique_ptr;
using std::vector;
using std::ostream;
using std::endl;
using std::setw;

namespace othello {

StabilityLookupTable StabilityLookupTable::defaultTable() noexcept
{
	StabilityLookupTable lookuptable(8,8);

	static const vector<int> col1 = { 4, -3,  2,  2,  2,  2, -3,  4};
	static const vector<int> col2 = {-3, -4, -1, -1, -1, -1, -4, -3};
	static const vector<int> col3 = { 2, -1,  1,  0,  0,  1, -1,  2};
	static const vector<int> col4 = { 2, -1,  0,  1,  1,  0, -1,  2};
	static const auto col5 = col4;
	static const auto col6 = col3;
	static const auto col7 = col2;
	static const auto col8 = col1;

	static const vector<vector<int>> table =
		{col1, col2, col3, col4, col5, col6, col7, col8};

	lookuptable.lookuptable = table;

	return lookuptable;
}

ostream& operator<<(ostream& os, const StabilityLookupTable& table)
{
	const auto rows = table.numRows();
	const auto cols = table.numColumns();

	os << "StabilityLookupTable=[";
	for (auto row = 0; row < rows; row++) {

		os << endl;

		for (auto col = 0; col < cols; col++) {

			const Position pos(row,col);

			os << setw(4) << table.lookupStability(pos);
		}
	}

	os << "]";

	return os;
}

WashingtonEvaluator::WashingtonEvaluator(StabilityLookupTable stabilityTable)
		: stabilityTable{stabilityTable}
{
	const auto rows = stabilityTable.numRows();
	const auto cols = stabilityTable.numColumns();

	const Position northWestCorner(0, 0);
	const Position northEastCorner(0, cols-1);
	const Position southEastCorner(rows-1, cols-1);
	const Position southWestCorner(rows-1, 0);

	corners.insert(northWestCorner);
	corners.insert(northEastCorner);
	corners.insert(southEastCorner);
	corners.insert(southWestCorner);
}

#ifdef USE_WASHINGTON_MOVE_UTILITY
score_t WashingtonEvaluator::moveUtility(const Outcome& outcome
		, const OthelloState& beforeAction) const
{
	#define isCorner(position) (corners.find((position)) != corners.end())

	if (outcome.action.isPass()) {

		/* A pass gives zero points because no brick is flipped. */
		return 0;

	}

	const auto position = outcome.action.getPosition();
	const double cornerUtility = isCorner(position)
		? 25.0 : 0.0;

	/* Truncation of may ocurr here, but the size of flips */
	const double coinUtility = 1.0 + 2.0*outcome.flips.size();

	double stabilityUtility{0};
	for (auto flip : outcome.flips) {
		stabilityUtility += stabilityTable.lookupStability(flip);
	}

	/* Double the stability increase due to flips, because the oponent looses
	 * as much in stability.
	 */
	stabilityUtility *= 2.0;

	/* Add stability for the placement. */
	stabilityUtility += stabilityTable.lookupStability(position);

	/* The move utility is skipped, because it costs too much to compute. */
	const auto utilityValue =
		weights.corner*cornerUtility
		+ weights.stability*stabilityUtility
		+ weights.coinParity*coinUtility;

	return utilityValue;

	#undef isCorner
}
#endif //USE_WASHINGTON_MOVE_UTILITY

score_t WashingtonEvaluator::utility(Player player
		, const OthelloState& state) const
{
	using std::round;

	const auto coinpar = coinParityUtility(player, state);
	const auto mobility = mobilityUtility(player, state);
	const auto corner = cornerUtility(player, state);
	const auto stability = stabilityUtility(player, state);

//	//DEBUG >>
//	using std::cerr;
//	#define pr(v) #v << ": " << v
//	cerr << pr(coinpar) << endl << pr(mobility) << endl << pr(corner)
//		<< endl << pr(stability) << endl;
//	#undef pr
//	//DEBUG <<

	/* Weights from the article (see header file). */
	return round(
		weights.corner*corner
		+ weights.mobility*mobility
		+ weights.stability*stability
		+ weights.coinParity*coinpar
	);
}

double WashingtonEvaluator::coinParityUtility(Player player
		, const OthelloState& state) const noexcept
{
	const auto maxPlayerCoinColour = playerBrickColour(player);
	const auto minPlayerCoinColour = playerBrickColour(advisary(player));

	auto numMaxPlayerCoins = 0;
	auto numMinPlayerCoins = 0;
	for (auto tile : state.constBoardIterator()) {
		if (tile == maxPlayerCoinColour) {
			numMaxPlayerCoins++;
		} else if (tile == minPlayerCoinColour) {
			numMinPlayerCoins++;
		}
	}

	const auto denominator =
		static_cast<double>(numMaxPlayerCoins + numMinPlayerCoins);

	if (denominator == 0) {
		return .0;
	}

	const auto numerator =
		static_cast<double>(numMaxPlayerCoins - numMinPlayerCoins);

	return 100.0*numerator/denominator;
}

double WashingtonEvaluator::mobilityUtility(Player player, OthelloState state)
		const noexcept
{
	state.setTurn(player);

	/* Here an unsigned long int is truncated, although the size can't
	 * possibly be to long.
	 */
	const double numMaxPlayerMoves =
		OthelloAction::findLegalPlacements(state).size();

	state.changeTurn();

	/* Truncation, see above. */
	const double numMinPlayerMoves =
		OthelloAction::findLegalPlacements(state).size();

	const auto denominator =
		static_cast<double>(numMaxPlayerMoves + numMinPlayerMoves);

	if (denominator == 0) {
		return .0;
	}

	const auto numerator = numMaxPlayerMoves - numMinPlayerMoves;

	return 100.0*numerator/denominator;
}

double WashingtonEvaluator::cornerUtility(Player player
		, const OthelloState& state) const noexcept
{
	const auto maxPlayerCoinColour = playerBrickColour(player);
	const auto minPlayerCoinColour = playerBrickColour(advisary(player));

	assert((4 == corners.size())
		&& "All corners must have been added.");

	auto numMaxPlayerCorners = 0;
	auto numMinPlayerCorners = 0;
	for (auto position : corners)
	{
		const auto tile = state.inspectTile(position);
		if (tile == maxPlayerCoinColour) {
			numMaxPlayerCorners++;
		} else if (tile == minPlayerCoinColour) {
			numMinPlayerCorners++;
		}
	}

	const auto denominator = 
		static_cast<double>(numMaxPlayerCorners + numMinPlayerCorners);

	if (denominator == 0) {
		return .0;
	}

	const auto numerator =
		static_cast<double>(numMaxPlayerCorners - numMinPlayerCorners);

	return 100.0*numerator/denominator;
}

double WashingtonEvaluator::stabilityUtility(Player player
		, const OthelloState& state) const
{
	const auto maxPlayerCoinColour = playerBrickColour(player);
	const auto minPlayerCoinColour = playerBrickColour(advisary(player));

	const auto rows = state.numBoardRows();
	const auto cols = state.numBoardColumns();

	if ((state.numBoardRows() != stabilityTable.numRows())
			|| (state.numBoardColumns() != stabilityTable.numColumns()))
	{
		throw std::length_error(
			"StabilityLookupTable and othello board dimensions mismatch");
	}

	auto maxPlayerStabilityScore = 0;
	auto minPlayerStabilityScore = 0;
	for (auto row = 0; row < rows; row++) {
		for (auto col = 0; col < cols; col++) {

			const Position pos(row, col);

			const auto tile = state.inspectTile(pos);
			const auto positionValue = stabilityTable.lookupStability(pos);

			if (tile == maxPlayerCoinColour) {
				maxPlayerStabilityScore += positionValue;
			} else if (tile == minPlayerCoinColour) {
				minPlayerStabilityScore += positionValue;
			}
		}
	}

	/* The factor 100 is basically included in the table. */
	return maxPlayerStabilityScore - minPlayerStabilityScore;
}

unique_ptr<Evaluator> WashingtonEvaluator::clone() const
{
	auto* clone_p = new WashingtonEvaluator(*this);
	return unique_ptr<Evaluator>(clone_p);
}

} //namespace othello
