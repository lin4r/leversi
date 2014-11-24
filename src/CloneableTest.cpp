/* Unit test for cloneable.
 *
 * Linus Narva.
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Cloneable.hpp"

using std::unique_ptr;

class MyInteger : public Cloneable<MyInteger>
{
public:

	MyInteger(int val) : val{val} {}
	virtual ~MyInteger() = default;

	virtual int getValue() const noexcept { return val; }

	virtual std::unique_ptr<MyInteger> clone() const override
		{ return unique_ptr<MyInteger>(new MyInteger(val)); };

private:

	int val;
};

class Successor : public MyInteger
{
public:

	Successor(int val) : MyInteger(val) {}
	virtual ~Successor() = default;

	virtual int getValue() const noexcept override
		{ return MyInteger::getValue()+1; }

	virtual std::unique_ptr<MyInteger> clone() const override
		{ return unique_ptr<MyInteger>(new Successor(MyInteger::getValue())); }
};

TEST_CASE("Test cloneable", "[Cloneable, virtualConstructor]")
{
	Successor s(3);
	std::unique_ptr<MyInteger> p = s.clone();

	REQUIRE(4 == p->getValue());
}
