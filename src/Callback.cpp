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
#include "MaximinSearcher.hpp"
#include "TimeboxedMaximinSearcher.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

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

	if (model->getState().isGameOver()) {

		return;
	}

	try {

		model->commitAction(action);
		cout << "Player Action> " << action << "." << endl;

		//Extra notify because the ai might take a while to choose.
		model->notifyAll();

		TimeboxedMaximinSearcher advisary(4, 5000
			, MaximinSearcher(*model));

		auto advisaryAction = advisary.maximinAction();

		auto analysis = advisary.getAnalysis();
		cout << "Computer Action> " << advisaryAction << "." << endl;
		cout << "*** Analysis ***" << endl
			<<  "nodes:            " << analysis.numNodes << endl
			<<  "branching factor: " << analysis.branchingFactor << endl
			<<  "score:            " << analysis.predictedScore << endl
			<<  "****************" << endl;

		model->commitAction(advisaryAction);

		if (model->getState().isGameOver()) {

			cout << "Game Over!!!" << endl;
			cout << "Winner> " << winnerMessage() << endl;

		/* If no move is possible, then recursively execute pass. */
		} else if (! OthelloAction::existsLegalPlacement(model->getState())) {
			executePlayerAction(OthelloAction::pass());
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

string Callback::winnerMessage() const noexcept
{
	const auto state = model->getState();
	int numWhite{0}, numBlack{0};
	
	for (auto row = 0; row < state.getBoardRows(); row++) {
		for (auto col = 0; col < state.getBoardColumns(); col++) {
			const Position pos(row,col);
			switch (state.inspectTile(pos)) {
			case Tile::White: numWhite++; break;
			case Tile::Black: numBlack++; break;
			default: ;
			}
		}
	}

	if (numWhite > numBlack) {
		return "White player won!";
	} else if (numBlack > numWhite) {
		return "Black player won!";
	} else {
		return "Tie, you are both loosers.";
	}
}

} //namespace othello
