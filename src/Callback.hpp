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
 * Defines callback for user input.
 *
 * Linus Narva.
 */
#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include "ReversiController.hpp"
#include "Game.hpp"
#include "ReversiState.hpp"
#include "Observer.hpp"

#include <memory>
#include <string>

namespace reversi {

class Callback : public ReversiController
{
public:

	Callback();
	virtual ~Callback() = default;

	virtual void pressedTile(int indexX, int indexY) override;

	/* XXX Ugly forwarding solution, Ill fix a consistent construction logic
	 * later.
	 */
	virtual void addGameObserver(
		std::shared_ptr<Observer<ReversiState>> observer) noexcept override;

private:

	virtual std::string winnerMessage() const noexcept;

	void executePlayerAction(ReversiAction action);

	std::unique_ptr<Game> model;
};

} //namespace reversi

#endif //CALLBACK_HPP_
