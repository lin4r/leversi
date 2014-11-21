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
#ifndef OTHELLO_ACTION_HPP_
#define OTHELLO_ACTION_HPP_

#include "getter_setter.hpp"
#include "Position.hpp"
#include "OthelloState.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <utility>

namespace othello {

class OthelloAction
{	
private:
	Position position = {-1,-1};
	bool pass{false};

public:

	OthelloAction(Position position) noexcept;
	OthelloAction(Position position, bool pass) noexcept;
	OthelloAction(std::string action);

	//XXX I really want it's name to be pass. It looks prettier when its called.
	static OthelloAction constructPass() noexcept;

	virtual ~OthelloAction() = default;

	GETTER(Position, position);

	virtual bool isPass() const noexcept;

	virtual std::string actionString() const noexcept;

	virtual std::vector<Position> execute(OthelloState& state);

	static bool existsLegalPlacement(const OthelloState& state) noexcept;

	/* Searches for legal placements. Also returns the corresponding flips
	 * since the algorithm basically gets them for free.
	 */
	static std::vector<std::pair<OthelloAction,std::vector<Position>>>
		findLegalPlacements(const OthelloState& state) noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */ 
	virtual std::vector<Position> searchFlips(const OthelloState& state) const;
};

/* This operator is defined so that the actions can be put in a set. Passes are
 * considered lower than non-passes. If pass is equal the position < determines
 * order.
 */
bool operator<(const OthelloAction& a1, const OthelloAction& a2);
bool operator==(const OthelloAction& a1, const OthelloAction& a2);
std::ostream& operator<<(std::ostream& os, const OthelloAction& action);

} //namespace othello



#endif //OTHELLO_ACTION_HPP_