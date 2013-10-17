
// Operating system includes
#include <dlfcn.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <string>

// project includes
#include "base.h"



// set default global namespace
using namespace std;


int main(int argc, char** argv)
{

    cout << "Opening libderived.so...\n";
	void* handle=dlopen("./libderived.so", RTLD_LAZY);
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();


    // load the symbols
    create_t* create_derived = (create_t*) dlsym(handle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return 1;
    }

    destroy_t* destroy_derived = (destroy_t*) dlsym(handle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return 1;
    }



    // create instance
    Base* base=create_derived();
    //use
    base->do_something();
    destroy_derived(base);

    // close the library
    cout << "Closing library...\n";
    dlclose(handle);

	return 0;
}


