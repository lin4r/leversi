/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of reversi-assignment.
 * 
 * reversi-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Enum class specifying a tile on the reversi board.
 *
 * Linus Narva.
 */
#ifndef TILE_HPP_
#define TILE_HPP_

#include <iostream>

namespace reversi {

enum class Tile
{
	Empty, Black, White
};

/* Returns the opposite colour of t, or Empty if t=Empty.
 */
inline Tile oppositeColor(Tile t)
{
	switch (t) {
	case Tile::Black: return Tile::White;
	case Tile::White: return Tile::Black;
	default: return t; /* Empty has no opposite, so it is just returned. */
	}
}

} //namespace reversi

inline std::ostream& operator<<(std::ostream& os, reversi::Tile tile)
{
	std::string stringRepresentation;

	switch (tile) {
	case reversi::Tile::Black: stringRepresentation = "Tile::Black";
	case reversi::Tile::White: stringRepresentation = "Tile::White";
	default: stringRepresentation = "Tile::Empty";
	}

	return os << stringRepresentation;
}

#endif //TILE_HPP_
