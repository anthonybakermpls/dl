#include "base.h"
#include <iostream>


using namespace std;


class Derived : public Base {
public:
    virtual double do_something() const {
       cout << "Hello world!" << endl; 
	return 1;
    }
};


// the class factories
extern "C" Base* create()
{
    return new Derived;
}

extern "C" void destroy(Base* p)
{
    delete p;
}
