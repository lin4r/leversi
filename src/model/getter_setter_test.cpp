#include "getter_setter.hpp"

#include <iostream>

using namespace std;

class wrapper
{
	int val;

public:
	GETTERSETTER(int, val)
};

int main(void)
{
	wrapper w;
	w.set_val(10);
	cout << "Val> " << w.get_val() << endl;
}
