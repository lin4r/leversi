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
 * Implements OthelloState.hpp
 *
 * Linus Narva.
 */
#include "OthelloState.hpp"

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;
using std::ostream;
using std::endl;

namespace othello {

OthelloState::OthelloState() noexcept : OthelloState(8,8,Player::Black)
{
}

OthelloState::OthelloState(int boardRows, int boardColumns, Player starter)
		noexcept
		: playersTurn{starter}, boardRows{boardRows}
		, boardColumns{boardColumns}
		, grid{vector<vector<Tile>>(boardRows,vector<Tile>(boardColumns
			,Tile::Empty))}
{
}

OthelloState OthelloState::initialState() noexcept
{
	OthelloState initial;

	initial.setTile(Position(3,3), Tile::White);
	initial.setTile(Position(3,4), Tile::Black);
	initial.setTile(Position(4,4), Tile::White);
	initial.setTile(Position(4,3), Tile::Black);

	return initial;
}

bool OthelloState::isInsideGrid(Position position) const noexcept
{
	return (0 <= position.row) && (position.row < boardRows)
		&& (0 <= position.column) && (position.column < boardColumns);
}

void OthelloState::flipBrick(Position position)
{
	switch (inspectTile(position)) {
	case Tile::Black: setTile(position, Tile::White); break;
	case Tile::White: setTile(position, Tile::Black); break;
	default: ; /* Do nothing if empty */
	}
}

void OthelloState::updateGameStatus(bool actionWasPass) noexcept
{
	/* If the previous player passed and pass is legal, then the game is
	 * over.
	 */
	gameIsOver = (this->actionWasPass && actionWasPass) || gameIsOver;
	this->actionWasPass = actionWasPass;
}

bool OthelloState::gameOver() const noexcept
{
	return gameIsOver;
}

void OthelloState::changeTurn() noexcept
{
	switch(playersTurn) {
	case Player::Black: playersTurn = Player::White; break;
	case Player::White:
	default: playersTurn = Player::Black;
	}
}

string OthelloState::gridString() const noexcept
{
	stringstream ss;

	const auto hline = [&]() {
		for (auto col = 0; col < boardColumns+2; col++) {
			ss << "-";
		}
	};

	hline();
	ss << " ..." << endl;
	for (auto row = 0; row < boardRows; row++) {
		ss << "|";
		for (auto col = 0; col < boardColumns; col++) {

			const Position pos(row,col);
			switch (inspectTile(pos)) {
			case Tile::White: ss << "X"; break;
			case Tile::Black: ss << "O"; break;
			default: ss << " ";
			}
		}
		ss << "| ..." << endl;
	}

	hline();

	return ss.str();
}

string OthelloState::whoLeads() const noexcept
{
	int numWhite{0}, numBlack{0};
	
	for (auto row = 0; row < boardRows; row++) {
		for (auto col = 0; col < boardColumns; col++) {
			const Position pos(row,col);
			switch (inspectTile(pos)) {
			case Tile::White: numWhite++; break;
			case Tile::Black: numBlack++; break;
			default: ;
			}
		}
	}

	if (numWhite > numBlack) {
		return "White player";
	} else if (numBlack > numWhite) {
		return "Black player";
	} else {
		return "Tie";
	}
}

string OthelloState::toString() const noexcept
{
	#define PVAR(var) #var << "{" << var << "}"

	stringstream ss;

	ss << "othello::OthelloState[" << PVAR(gameIsOver) << ", "
		<< PVAR(actionWasPass) << ", " << PVAR(playersTurn) << ", "
		<< PVAR(boardRows) << ", " << PVAR(boardColumns) << ", grid{ ..."
		<< endl << gridString() << "}]";

	#undef PVAR

	return ss.str();
}

bool operator==(const OthelloState& state1, const OthelloState& state2)
{
	const auto rows = state1.get_boardRows();
	const auto columns = state1.get_boardColumns();
	/* Check the 'simple components before the board.' */
	if ( (rows != state2.get_boardRows())
			|| (columns != state2.get_boardColumns())
			|| (state1.whosTurn() != state2.whosTurn())
			|| (state1.actionWasPass != state2.actionWasPass)
			|| (state1.gameOver() != state2.gameOver()) )
	{
		return false;
	}

	bool boardEqual{true};

	for (auto row = 0; boardEqual && (row < rows); row++) {
		for (auto col = 0; boardEqual && (col < columns); col++) {

			const Position pos(row,col);
			boardEqual = boardEqual
				&& (state1.inspectTile(pos) == state2.inspectTile(pos));
		}
	}

	return boardEqual;
}

} //namespace othello
