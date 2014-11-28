/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of othello-assignment.
 * 
 * othello-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/**
 * A othello action i.e. putting the othello brick on some position on the
 * board.
 *
 * Linus Narva.
 */
#ifndef OTHELLO_ACTION_HPP_
#define OTHELLO_ACTION_HPP_

#include "Position.hpp"
#include "OthelloState.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace othello {

typedef std::vector<Position> flips_t;

struct Outcome;

class OthelloAction
{
public:

	/**
	 * param:	Position for placement.
	 */
	OthelloAction(Position position) noexcept
		: OthelloAction(position, false)
	{}

	/**
	 * params:
	 *	position - Position of placement. Doesn't matter if ispass==true.
	 *	ispass - Flags if the action is pass.
	 */
	OthelloAction(Position position, bool ispass) noexcept
		: position(position), ispass{ispass}
	{}

	virtual ~OthelloAction() = default;

	/**
	 * Creates a pass action.
	 * return:	A pass action.
	 */
	static OthelloAction pass() noexcept;

	/**
	 * Parses an action string.
	 * param:	String representation of action.
	 * return:	Action corresponding to the string.
	 * throws:	actionstring_syntax_exception, if the string is ill formed.
	 */
	static OthelloAction parse(std::string actionstring);

	/**
	 * Creates a string representation of the action.
	 * return:	String representation.
	 */
	virtual std::string actionString() const noexcept;

	/**
	 * Executes the action on the state.
	 * param:	State to apply action to.
	 * throws:	illegal_action_exception, if the action breakes othello rules.
	 */
	virtual flips_t execute(OthelloState& state) const;

	/**
	 * Checks if non-pass actions are avalible for the player at the given
	 * state. It is more efficient than findLegalPlacements() because the serch
	 * is terminated as soon as a legal placement is found.
	 * param:	State te search for actions in.
	 * return:	True iff a legal action exists.
	 */
	static bool existsLegalPlacement(const OthelloState& state) noexcept;

	/**
	 * Searches for legal placements.
	 * param:	State te search for actions in.
	 * return:	Outcomes of the legal actions i.e. the action and the flips it
	 *			will cause.
	 */
	static std::vector<Outcome> findLegalPlacements(
		const OthelloState& state) noexcept;

	/**
	 * Lists which bricks are fliped by the action.
	 * param:	State to check for flips in.
	 * return:	A vector of positions where the bricks where turned
	 */ 
	virtual flips_t searchFlips(const OthelloState& state) const; //XXX Should be noexcept.

	/**
	 * Gets the position of placement.
	 * return:	position.
	 */
	virtual Position getPosition() const noexcept
		{ return position; }

	/**
	 * Checks if pass.
	 * return true iff the action is pass.
	 */
	virtual bool isPass() const noexcept
		{ return ispass; }

private:

	/**
	 * Updates the game over status of state (true after two passes in a row).
	 * param:	State to update.
	 */
	void updateGameOverStaus(OthelloState& state) const noexcept;

	/**
	 * Position of the placement.
	 */
	Position position = {-1,-1};

	/**
	 * Flag indicating if pass.
	 */
	bool ispass{false};

};

/**
 * The action and the flips it causes.
 */
struct Outcome
{
	OthelloAction action; // The action.
	flips_t flips; //Flips caused by the action in context of the state.
};


/* This operator is defined so that the actions can be put in a set. Passes are
 * considered lower than non-passes. If pass is equal the position < determines
 * order.
 */
bool operator<(const OthelloAction& a1, const OthelloAction& a2) noexcept;

bool operator==(const OthelloAction& a1, const OthelloAction& a2) noexcept;

inline bool operator!=(const OthelloAction& a1, const OthelloAction& a2)
		noexcept
	{ return !(a1 == a2); }

std::ostream& operator<<(std::ostream& os, const OthelloAction& action);

} //namespace othello



#endif //OTHELLO_ACTION_HPP_
