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

/*
 * A othello action i.e. putting the othello brick on some position on the
 * board.
 *
 * Linus Narva.
 */
//FIXME Replace the pair's with a struct.
#ifndef OTHELLO_ACTION_HPP_
#define OTHELLO_ACTION_HPP_

#include "Position.hpp"
#include "OthelloState.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace othello {

typedef std::vector<Position> flips_t;

/* The action and the flips it causes. */
struct Outcome;

class OthelloAction
{
public:

	OthelloAction(Position position) noexcept
		: OthelloAction(position, false)
	{}

	OthelloAction(Position position, bool ispass) noexcept
		: position(position), ispass{ispass}
	{}

	virtual ~OthelloAction() = default;

	static OthelloAction pass() noexcept;

	static OthelloAction parse(std::string actionstring);

	virtual std::string actionString() const noexcept;

	virtual flips_t execute(OthelloState& state) const;

	static bool existsLegalPlacement(const OthelloState& state) noexcept;

	/* Searches for legal placements. Also returns the corresponding flips
	 * since the algorithm basically gets them for free.
	 */
	static std::vector<Outcome> findLegalPlacements(
		const OthelloState& state) noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */ 
	virtual flips_t searchFlips(const OthelloState& state) const;

	virtual Position getPosition() const noexcept
		{ return position; }

	virtual bool isPass() const noexcept
		{ return ispass; }

private:

	void updateGameOverStaus(bool wasPass, OthelloState& state) const noexcept;

	Position position = {-1,-1};
	bool ispass{false};

};

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
