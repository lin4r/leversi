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
 * Observable in the Observer-Observable design pattern.
 *
 * TODO Info on how to use the pattern.
 *
 * TODO Delete objects which are unique in the shared pointers. They are
 * useless because no client uses them. Using weak ptr's are not an option
 * because they dont have relational operators, and would yield an inconsistent
 * set state, should the objects pointed to bee deleted.
 *
 * Linus Narva.
 */
#ifndef OBSERVABLE_HPP_
#define OBSERVABLE_HPP_

#include "Observer.hpp"
#include <set>
#include <memory>

namespace lut {

class Observable
{
public:
	virtual ~Observable() = default;

	virtual bool addObserver(std::shared_ptr<Observer> observer) noexcept;
	virtual bool removeObserver(std::shared_ptr<Observer> observer) noexcept;

	virtual bool notify(std::shared_ptr<Observer> toNotify);
	virtual void notifyAll();

	virtual const int* getNotifyData() const = 0; //int is a dummy type, will be a template.

	virtual int numObservers() const noexcept;

private:

	std::set<std::shared_ptr<Observer>> observers;
};

} //namespace lut

#endif //OBSERVABLE_HPP_
