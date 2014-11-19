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
 * A state of the othello game.
 *
 * Linus Narva.
 */
#ifndef OTHELLO_STATE_HPP_
#define OTHELLO_STATE_HPP_

#include "Tile.hpp"
#include "Player.hpp"
#include "getter_setter.hpp"
#include "Position.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace othello {

class OthelloState
{	
public:

	OthelloState() noexcept;
	OthelloState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~OthelloState() = default;

	static OthelloState initialState() noexcept;

	GETTER(int, boardRows)
	GETTER(int, boardColumns)

	virtual Player whosTurn() const noexcept;
	virtual Tile inspectTile(Position position) const;
	virtual void setTile(Position position, Tile value);
	virtual void changeTurn() noexcept;
	virtual void flipBrick(Position position);
	virtual bool isInsideGrid(Position position) const noexcept;
	virtual void updateGameStatus(bool actionWasPass) noexcept;
	virtual bool gameOver() const noexcept;

	virtual std::string toString() const noexcept;
	virtual std::string gridString() const noexcept;


private:

	bool gameIsOver{false};
	bool previousActionWasPass{false};

	Player playersTurn;

	int boardRows;
	int boardColumns;
	std::vector<std::vector<Tile>> grid;

//Friends

	friend bool operator==(const OthelloState& state1
		, const OthelloState& state2);

	friend std::ostream& operator<<(std::ostream& os
		, const OthelloState& state);
};

bool operator==(const OthelloState& state1, const OthelloState& state2);
bool operator!=(const OthelloState& state1, const OthelloState& state2);

std::ostream& operator<<(std::ostream& os, const OthelloState& state);

} //namespace othello

#endif //OTHELLO_STATE_HPP_
