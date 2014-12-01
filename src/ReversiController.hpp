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
 * MVC Controller interface for reversi.
 *
 * Linus Narva.
 */
#ifndef REVERSI_CONTROLLER_HPP_
#define REVERSI_CONTROLLER_HPP_

#include "Observer.hpp"
#include "ReversiState.hpp"

#include <memory>

namespace reversi {

class ReversiController
{
public:

	virtual void pressedTile(int indexX, int indexY) = 0;

	/* XXX Ugly forwarding solution, Ill fix a consistent construction logic
	 * later.
	 */
	virtual void addGameObserver(std::shared_ptr<Observer<ReversiState>>
		observer) noexcept = 0;
};

} //namespace reversi

#endif //REVERSI_CONTROLLER_HPP_
