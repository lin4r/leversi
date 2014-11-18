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
 * Unit tests for the Observer Observable pattern.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Observer.hpp"
#include "Observable.hpp"

#include <memory>

using namespace lut;
using namespace std;

class MockObserver : public Observer
{
public:

	void notify(const int* arg_p) override
	{
		hasReceived = true;
		receivedArg = *arg_p;
	}

	bool hasReceived{false};
	int receivedArg{-1};
};

class MockObservable : public Observable
{
public:

	const int* getNotifyData() const override
	{
		return &myValue;
	}

	int myValue{1337};
};

TEST_CASE("Testing Observer Observable notifications"
		, "[Observer, Observable]")
{
	/* I call them receiver emmiter for better readability. */
	shared_ptr<MockObserver> receiver1{new MockObserver()};
	shared_ptr<MockObserver> receiver2{new MockObserver()};

	shared_ptr<MockObservable> emitter{new MockObservable()};
	emitter->addObserver(receiver1);

	SECTION ("Notify gets called in observers.")
	{
		emitter->notify(receiver1);
		REQUIRE(receiver1->hasReceived);
	}
}
