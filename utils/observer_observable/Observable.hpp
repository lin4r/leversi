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
 * Linus Narva.
 */
#ifndef OBSERVABLE_HPP_
#define OBSERVABLE_HPP_

#include "Observer.hpp"
#include <set>
#include <memory>

namespace lut {

template<typename T>
class Observable
{
public:
	virtual ~Observable() = default;

	virtual bool addObserver(std::shared_ptr<Observer<T>> observer) noexcept;
	virtual bool removeObserver(std::shared_ptr<Observer<T>> observer)
		noexcept;

	virtual bool notify(std::shared_ptr<Observer<T>> toNotify);
	virtual void notifyAll();

	virtual const T* getNotifyData() const = 0;

	virtual int numObservers() const noexcept;

	//TODO get observers function.

private:

	std::set<std::shared_ptr<Observer<T>>> observers;
};

template<typename T>
bool Observable<T>::addObserver(std::shared_ptr<Observer<T>> observer) noexcept
{
	return observers.insert(observer).second;
}

template<typename T>
bool Observable<T>::removeObserver(std::shared_ptr<Observer<T>> observer)
		noexcept
{
	return observers.erase(observer) == 1;
}

template<typename T>
bool Observable<T>::notify(std::shared_ptr<Observer<T>> toNotify)
{
	bool foundMember{false};

	if (observers.find(toNotify) != observers.end()) {

		toNotify->notify(getNotifyData());
		foundMember = true;
	}

	return foundMember;
}

template<typename T>
void Observable<T>::notifyAll()
{
	for (auto observer : observers) {
		notify(observer);
	}
}

template<typename T>
int Observable<T>::numObservers() const noexcept
{
	return observers.size();
}

} //namespace lut

#endif //OBSERVABLE_HPP_
