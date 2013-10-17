#include "generic.h"
#include <cmath>

class triangle : public Generic {
public:
    virtual double area() const {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};


// the class factories

extern "C" Generic* create() {
    return new triangle;
}

extern "C" void destroy(Generic* p) {
    delete p;
}
