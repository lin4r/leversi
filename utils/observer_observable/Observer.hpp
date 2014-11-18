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
 * Observer in the Observer-Observer design pattern.
 *
 * TODO info on how to use the pattern
 *
 * Linus Narva.
 */
#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

namespace lut {

class Observer
{
public:

	virtual ~Observer() = default;

	virtual void notify(const int* state) = 0; //XXX The int is a dummy object, it will be a template when done
};

} //namespace lut

#endif //OBSERVER_HPP_
