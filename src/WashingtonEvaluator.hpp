/**
 * Evaluator based on this article:
 *
 * An Analysis of Heuristics in Othello
 * Vaishnavi Sannidhanam and Muthukaruppan Annamalai
 * Department of Computer Science and Engineering
 * Seattle, WA-98195
 *
 * Linus Narva
 */
#ifndef WASHINGTON_EVALUATOR_HPP_
#define WASHINGTON_EVALUATOR_HPP_

#include "Evaluator.hpp"

#include <set>
#include <vector>
#include <iostream>

namespace othello {

/**
 * Weights for combining the utility values. The default values where
 * discovered by the authors of the article.
 */
struct WashingtonWeights
{
	double corner{30.0};		/* Corner utility weight. */
	double mobility{5.0};		/* Mobility utility weight. */
	double stability{25.0};		/* Stability utility weight. */
	double coinParity{25.0};	/* Coin parity utility weight. */
};

/**
 * To calculate the exact stability of each position would be to expensive for
 * a utility function. Therefor a static lookup table is used, as suggested
 * by the authors of the article.
 *
 * It is rekommended to use the defaultTable() for normal othello games.
 */
class StabilityLookupTable
{
public:

	/**
	 * Creates a table. Must have the same size as the othello board.
	 * params:
	 *	rows - number of table rows.
	 *	columns - number of table columns.
	 */
	StabilityLookupTable(int rows, int columns)
		: tableRows{rows}
		, tableColumns{columns}
		, lookuptable(rows, std::vector<int>(columns))
	{}

	/**
	 * Sets the lookup stability value of a position.
	 * params:
	 *	stability - new stability value.
	 *	position - position to set at.
	 * throws:	out_of_range if the position is outside the table.
	 */
	virtual void setStability(int stability, Position position)
		{ lookuptable.at(position.row).at(position.column) = stability; }

	/**
	 * Gets the lookup stabillity of a position.
	 * param:	Position to look up stability of.
	 * return:	The stability value.
	 * throws:	out_of_range if the position is outside the table.
	 */
	virtual int lookupStability(Position position) const
		{ return lookuptable.at(position.row).at(position.column); }

	/**
	 * Creates a rekommended default 8*8 lookup table.
	 * return:	A lookup table with values set.
	 */
	static StabilityLookupTable defaultTable() noexcept;

	/**
	 * The number of rows.
	 * return:	number of rows.
	 */
	virtual int numRows() const noexcept
		{ return tableRows; }

	/**
	 * The number of columns.
	 * return:	number of columns.
	 */
	virtual int numColumns() const noexcept
		{ return tableColumns; }

private:

	/* The number of rows. */
	int tableRows;

	/* The number of columns. */
	int tableColumns;

	/* The tabular data. */
	std::vector<std::vector<int>> lookuptable;
};

std::ostream& operator<<(std::ostream& os, const StabilityLookupTable& table);

class WashingtonEvaluator : public Evaluator
{
public:

	/**
	 * Creates an evaluator with default settings.
	 */
	WashingtonEvaluator()
			: WashingtonEvaluator(StabilityLookupTable::defaultTable())
	{}

	/**
	 * Creates a table with a custom stability table. It is recommended to use
	 * the other constructor for normal othello rules (especially for a 8*8
	 * board).
	 * param:	Stability lookup table to use.
	 */
	WashingtonEvaluator(StabilityLookupTable stabilityTable);

	virtual ~WashingtonEvaluator() = default;

	/* XXX The current impleemntation is to simple (it is the same as in
	 * SimpleEvaluator.)
	 */
	virtual score_t moveUtility(const Outcome& outcome
			, const OthelloState& beforeAction)
			const override;

	/**
	 * Calculates a weighted sum of the utility values compuded by the utility
	 * functions below.
	 */
	virtual score_t utility(Player player, const OthelloState& state)
			const override;

	/**
	 * Calculates the coin parity
	 * = 100*(#max coins - #min coins)/(#max coins + #min coins).
	 * params:
	 *	player - the max player.
	 *	state - state to compute utility for.
	 * return:	A utility value.
	 */
	virtual double coinParityUtility(Player player, const OthelloState& state)
		const noexcept;

	/**
	 * Calculates a move utility
	 * = 100*(#max moves - #min moves)/(#max moves + #min moves)
	 * (pass is not included in the moves).
	 * params:
	 *	player - the max player.
	 *	state - state to compute utility for.
	 * return:	A utility value.
	 */
	virtual double mobilityUtility(Player player, OthelloState state)
		const noexcept;

	/**
	 * Calculates a corner utility
	 * = 100*(#max corners - #min corners)/(#max corners + #min corners).
	 * params:
	 *	player - the max player.
	 *	state - state to compute utility for.
	 * return:	A utility value.
	 */
	virtual double cornerUtility(Player player, const OthelloState& state)
		const noexcept;

	/*
	 * Calculates a stability utility = max stability - min stability based on
	 * the lookup table.
	 * params:
	 *	player - the max player.
	 *	state - state to compute utility for.
	 * return:	A utility value.
	 * throws:	length_error if dimensions of the lookup table and othello
	 *			board mismatch.
	 */
	virtual double stabilityUtility(Player player, const OthelloState& state)
		const;

	virtual std::unique_ptr<Evaluator> clone() const override;

	/**
	 * Sets the utility value weights.
	 * param:	New weights.
	 */
	virtual void setWeights(WashingtonWeights newWeights) noexcept
		{ weights = newWeights; }

	/**
	 * Gets the utility value weights.
	 * return:	The weights.
	 */
	virtual WashingtonWeights getWeights() const noexcept
		{ return weights; }

private:

	/**
	 * The weights used to linearly combine the utility functions.
	 */
	WashingtonWeights weights;

	/**
	 * Lookuptable for calculating stability utility.
	 */
	StabilityLookupTable stabilityTable;

	/**
	 * Set containing the corner positions.
	 */
	std::set<Position> corners;
};

} //namespace othello

#endif //WASHINGTON_EVALUATOR_HPP_
