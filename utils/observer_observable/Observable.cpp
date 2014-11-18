/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of lut-assignment.
 * 
 * lut-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Implements Observable.hpp
 *
 * Linus Narva.
 */
#include "Observable.hpp"

using std::shared_ptr;

namespace lut {

bool Observable::addObserver(shared_ptr<Observer> observer) noexcept
{
	return observers.insert(observer).second;
}

bool Observable::removeObserver(shared_ptr<Observer> observer) noexcept
{
	return observers.erase(observer) == 1;
}

bool Observable::notify(shared_ptr<Observer> toNotify)
{
	bool foundMember{false};

	if (observers.find(toNotify) != observers.end()) {

		toNotify->notify(getNotifyData());
		foundMember = true;
	}

	return foundMember;
}

void Observable::notifyAll()
{
	for (auto observer : observers) {
		notify(observer);
	}
}

int Observable::numObservers() const noexcept
{
	return observers.size();
}

} //namespace lut
