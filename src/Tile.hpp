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
 * Enum class specifying a tile on the othello board.
 *
 * Linus Narva.
 */
#ifndef TILE_HPP_
#define TILE_HPP_

#include <iostream>

namespace othello {

enum class Tile : char
{
	Empty, Black, White
};

/**
 * Returns the opposite colour of t.
 * param:	A tile.
 * return:	The opposite colour or Empty if t=Empty.
 */
inline Tile oppositeColor(Tile t)
{
	switch (t) {
	case Tile::Black: return Tile::White;
	case Tile::White: return Tile::Black;
	default: return t; /* Empty has no opposite, so it is just returned. */
	}
}

inline std::ostream& operator<<(std::ostream& os, othello::Tile tile)
{
	std::string stringRepresentation;

	switch (tile) {
	case othello::Tile::Black: stringRepresentation = "Tile::Black";
	case othello::Tile::White: stringRepresentation = "Tile::White";
	default: stringRepresentation = "Tile::Empty";
	}

	return os << stringRepresentation;
}

} //namespace othello

#endif //TILE_HPP_
