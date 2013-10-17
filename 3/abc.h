#ifndef ABC_H
#define ABC_H 



#include <iostream> 
using namespace std;


class Abc{

	public:
	Abc();
	virtual ~Abc();
	
	virtual void do_something();
	
	private:
	int x;	
};

// class factory "C" functions
typedef Abc* create_t;
typedef void destroy_t(Abc*);






#endif
