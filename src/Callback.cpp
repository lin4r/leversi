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
 * Implements Callback.hpp
 *
 * Linus Narva.
 */
#include "Callback.hpp"
#include "Position.hpp"
#include "OthelloAction.hpp"
#include "illegal_action_exception.hpp"

//XXX DEBUG >>
#include <iostream>
using namespace std;
//XXX DEBUG <<

using std::shared_ptr;

namespace othello {

Callback::Callback() : model{new Game()}
{
}

void Callback::pressedTile(int indexX, int indexY)
{
	/* The coordinates are reversed because the model uses row-col coordinates
	 * which effectively inverts x,y.
	 */
	Position pos(indexY, indexX);
	OthelloAction action(pos);

	try {
		model->commitAction(action);
		model->notifyAll();
	} catch (illegal_action_exception e) {
		cerr << e.what() << endl;
	}

	//XXX DEBUG
	cout << model->getState() << endl;
}

void Callback::addGameObserver(shared_ptr<Observer<OthelloState>> observer)
		noexcept
{
	model->addObserver(observer);
}

} //namespace othello
