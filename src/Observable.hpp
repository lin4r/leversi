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
 * Observable in the Observer-Observable design pattern.
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
#ifndef OBSERVABLE_HPP_
#define OBSERVABLE_HPP_

#include "Observer.hpp"
#include <set>
#include <memory>

namespace reversi {

template<typename T>
class Observable
{
public:
	virtual ~Observable() = default;

	/* Adds observer to be called on notifications. An observer can only be
	 * added once.
	 * param:	Smart pointer to the observer to add.
	 * return:	True iff the observer was added. Otherwise false if it was
	 *			already added.
	 */
	virtual bool addObserver(std::shared_ptr<Observer<T>> observer) noexcept;

	/* Removes an observer, so that it is not called on notifications.
	 * param:	Smart pointer to the observer to remove.
	 * return:	True iff the observer was successfully removed. Otherwise false
	 *			if it was never added to begin with.
	 */
	virtual bool removeObserver(std::shared_ptr<Observer<T>> observer)
		noexcept;

	/* Calls the specific observers notify() function.
	 * param:	Smart pointer to the observer to notify.
	 * return:	True iff toNotify was notified. Otherwise false if it was not
	 *			added.
	 */
	virtual bool notify(std::shared_ptr<Observer<T>> toNotify);

	/* Notifies all observers of the object.
	 */
	virtual void notifyAll();

	/* Gets the notification data, which is sent to all observers when
	 * notified.
	 * return:	A non modifiable pointer state data.
	 */
	virtual const T* getNotifyData() const = 0;

	/* Gets the number of observers of the object.
	 * return:	The number of observers.
	 */
	virtual int numObservers() const noexcept;

	/* Gets the set of observers of the object.
	 * return:	The set of observers.
	 */
	virtual std::set<std::shared_ptr<Observer<T>>> getObservers();

private:

	/* The set of observers observing the object. */
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

template<typename T>
std::set<std::shared_ptr<Observer<T>>> Observable<T>::getObservers()
{
	return observers;
}

} //namespace reversi

#endif //OBSERVABLE_HPP_
