:/*******************************************************
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
 * Interface for an algorithm playing the othello game.
 *
 * Linus Narva.
 */
#ifndef REVERSI_ALGORITHM_HPP_
#define REVERSI_ALGORITHM_HPP_

#include "ReversiEvaluator.hpp"
#include "ReversiAction.hpp"
#include "ReversiPosition.hpp"

namespace othello {

class ReversiAlgorithm
{	
public:

	virtual ~ReversiAlgorithm() = default;

	/* Sets the evalueator, used to heuristically evaluate actions.
	 */
	void setEvaluator(ReversiEvaluator evaluator) = 0;

	/* Returns the best action (as evaluated by the algorithm).
	 */
	void ReversiAction evaluate(ReversiPosition position) = 0;

	/* Sets the search.
	 */
	void setSearchDepth(int depth) = 0;

} //namespace othello

#endif //REVERSI_ALGORITHM_HPP_
