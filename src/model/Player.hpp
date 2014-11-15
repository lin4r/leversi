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
 * Enum class specifying a player.
 *
 * Linus Narva.
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Tile.hpp"

namespace othello {

enum class Player
{
	Black, White
};

inline Tile playerBrickColour(Player player)
{
	switch (player) {
	case Player::Black: return Tile::Black;
	case Player::White:
	default: return Tile::White;
	}
}

} //namespace othello

#endif //PLAYER_HPP_
