
// Operating system includes
#include <dlfcn.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <string>

// project includes
#include "abc.h"



// set default global namespace
using namespace std;


int main(int argc, char** argv)
{

    cout << "Opening libabc.so...\n";
	void* handle=dlopen("./libabc.so", RTLD_LAZY);
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }


	Abc* (*create)();
	void (*destroy)(Abc*);

    // reset errors
    dlerror();

	create=(Abc* (*)())dlsym(handle, "create");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'create': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }



	destroy=(void (*)(Abc*))dlsym(handle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'destroy': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }


	Abc* abc=(Abc*)create();
	abc->do_something();
	destroy(abc);

    // close the library
    cout << "Closing library...\n";
    dlclose(handle);

	return 0;
}


