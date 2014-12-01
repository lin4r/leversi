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
 * Unit tests for the Observer Observable pattern.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Observer.hpp"
#include "Observable.hpp"

#include <memory>

using namespace reversi;

class MockObserver : public Observer<int>
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

class MockObservable : public Observable<int>
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
	using std::shared_ptr;

	/* I call them receiver emmiter for better readability. */
	shared_ptr<MockObserver> receiver1{new MockObserver()};
	shared_ptr<MockObserver> receiver2{new MockObserver()};
	shared_ptr<MockObserver> nonReceiver{new MockObserver()};

	shared_ptr<MockObservable> emitter{new MockObservable()};
	emitter->addObserver(receiver1);
	emitter->addObserver(receiver2);

	SECTION("Two observers were added.")
	{
		REQUIRE(2 == emitter->numObservers());
	}

	SECTION("Notifies the specified observer.")
	{
		auto flag = emitter->notify(receiver1);
		REQUIRE(receiver1->hasReceived);
		REQUIRE(flag);
	}

	SECTION("Notifies all the added observers.")
	{
		emitter->notifyAll();
		REQUIRE(receiver1->hasReceived);
		REQUIRE(receiver2->hasReceived);
	}

	SECTION("Can't remove non-receiver.")
	{
		auto flag = emitter->removeObserver(nonReceiver);
		REQUIRE(! flag);
		REQUIRE(2 == emitter->numObservers());
	}

	SECTION("The emitted value is received")
	{
		emitter->notify(receiver1);
		REQUIRE(1337 == receiver1->receivedArg);
	}

	SECTION("Can't add duplicates.")
	{
		auto duplicate1 = receiver1;
		auto flag = emitter->addObserver(duplicate1);
		REQUIRE(2 == emitter->numObservers());
		REQUIRE(! flag);
	}

	bool flag = emitter->removeObserver(receiver1);

	SECTION("Can remove observer.")
	{
		REQUIRE(flag);
		REQUIRE(1 == emitter->numObservers());
	}

	SECTION("Can't notify removed observer.")
	{
		auto flag = emitter->notify(receiver1);
		REQUIRE(! receiver1->hasReceived);
		REQUIRE(! flag);
	}
}
