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
 * Enum representation of an othello player.
 *
 * Linus Narva.
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Tile.hpp"

#include <iostream>

namespace othello {

enum class Player : char
{
	Black, White
};

/**
 * Gets the coin colour associated with the player.
 * param:	A player.
 * return:	Coin colour of player.
 */
inline Tile playerBrickColour(Player player) noexcept
{
	switch (player) {
	case Player::Black: return Tile::Black;
	case Player::White:
	default: return Tile::White;
	}
}

/**
 * Gets the advisary of player.
 * param:	A player.
 * return:	The advisary of player.
 */
inline Player advisary(Player player) noexcept
{
	switch (player) {
	case Player::Black: return Player::White;
	case Player::White:
	default: return Player::Black;
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
