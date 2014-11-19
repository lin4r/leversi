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
 * MVC Controller interface for othello.
 *
 * Linus Narva.
 */
#ifndef OTHELLO_CONTROLLER_HPP_
#define OTHELLO_CONTROLLER_HPP_

#include "Observer.hpp"
#include "OthelloState.hpp"

#include <memory>

namespace othello {

class OthelloController
{
public:

	virtual void pressedTile(int indexX, int indexY) = 0;

	/* XXX Ugly forwarding solution, Ill fix a consistent construction logic
	 * later.
	 */
	virtual void addGameObserver(std::shared_ptr<Observer<OthelloState>> observer)
		noexcept = 0;
};

} //namespace othello

#endif //OTHELLO_CONTROLLER_HPP_
