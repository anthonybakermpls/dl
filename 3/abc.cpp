#include "abc.h"
#include <iostream>

using namespace std;



Abc::Abc()
{
	x=20;
}

Abc::~Abc()
{

}

void Abc::do_something()
{
	cout << "Hello World!" << endl;
}


extern "C"
{
	Abc* create()
	{
		return new Abc;
	}

	void destroy(Abc* p)
	{
		delete p;
	}
}
