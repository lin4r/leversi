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

#include <iostream>

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

inline std::ostream& operator<<(std::ostream& os, const Player& player)
{
	std::string playerStr;

	switch (player) {
	case Player::Black: playerStr = "Player::Black"; break;
	case Player::White:
	default: playerStr = "Player::White"; break;
	}

	return os << playerStr;
}

} //namespace othello

#endif //PLAYER_HPP_
