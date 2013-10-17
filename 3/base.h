#ifndef BASE_H
#define BASE_H

class Base {
protected:
    double x;

public:
    Base()
        : x(0) {}

    virtual ~Base() {}

    void set_x(double a) {
        x = a;
    }

    virtual double do_something() const = 0;
};

// the types of the class factories
typedef Base* create_t();
typedef void destroy_t(Base*);

#endif
