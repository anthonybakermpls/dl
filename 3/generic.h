#ifndef GENERIC_H
#define GENERIC_H

class Generic {
protected:
    double x;

public:
    Generic()
        : x(0) {}

    virtual ~Generic() {}

    void set_x(double a) {
        x = a;
    }

    virtual double do_something() const = 0;
};

// the types of the class factories
typedef Generic* create_t();
typedef void destroy_t(Generic*);

#endif
