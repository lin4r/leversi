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
#include "BestMoveFinder.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

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

	executePlayerAction(action);
}

/* TODO handle player pass and game over.*/
void Callback::executePlayerAction(OthelloAction action)
{
	/* The coordinates are reversed because the model uses row-col coordinates
	 * which effectively inverts x,y.
	 */

	if (model->getState().gameOver()) {

		return;
	}

	try {

		model->commitAction(action);
		cout << "Player Action> " << action << "." << endl;

		//Extra notify because the ai might take a while to choose.
		model->notifyAll();

		BestMoveFinder advisary(*model);
		auto advisaryAction = advisary.getBestMove().first;
		model->commitAction(advisaryAction);
		cout << "Computer Action> " << advisaryAction << "." << endl;

		if (model->getState().gameOver()) {

			cout << "Game Over!!!" << endl;
			cout << "Winner> " << model->getState().whoLeads() << endl;

		/* If no move is possible, then recursively execute pass. */
		} else if (! OthelloAction::existsLegalPlacement(model->getState())) {
			executePlayerAction(OthelloAction::constructPass());
		}

		model->notifyAll();
	} catch (illegal_action_exception e) {
		cerr << e.what() << endl;
	}
}

void Callback::addGameObserver(shared_ptr<Observer<OthelloState>> observer)
		noexcept
{
	model->addObserver(observer);
}

} //namespace othello
