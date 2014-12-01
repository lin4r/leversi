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
 * Observer in the Observer-Observer design pattern.
 *
 * Observer-Observable is useful an update in the state of some objects affects
 * the state a set of objects, according to the change.
 *
 * A good example is in grafical user interfaces when the state of a model
 * object e.g. the state of the reversi game, is reflected in a set of view
 * of the graphical user interface.
 *
 * Linus Narva.
 */
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

namespace reversi {

template<typename T>
class Observer
{
public:

	virtual ~Observer() = default;

	/* Called by Observable when a state changed occurred. Be careful when using
	 * the state pointer. Depending on the implementation the object pointed to
	 * might go out of scope after the call, so extract the relevant data.
	 * params:	Raw pointer to the state object.
	 */
	virtual void notify(const T* state) = 0;
};

} //namespace reversi

#endif //OBSERVER_HPP_
