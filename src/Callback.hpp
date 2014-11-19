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
 * Defines callback for user input.
 *
 * Linus Narva.
 */
#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include "OthelloController.hpp"
#include "Game.hpp"
#include "OthelloState.hpp"
#include "Observer.hpp"

#include <memory>

namespace othello {

class Callback : public OthelloController
{
public:

	Callback();
	virtual ~Callback() = default;

	virtual void pressedTile(int indexX, int indexY) override;

	/* XXX Ugly forwarding solution, Ill fix a consistent construction logic
	 * later.
	 */
	virtual void addGameObserver(std::shared_ptr<Observer<OthelloState>> observer)
		noexcept override;

private:

	std::unique_ptr<Game> model;
};

} //namespace othello

#endif //CALLBACK_HPP_
