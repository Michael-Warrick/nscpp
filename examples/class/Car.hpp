#ifndef NSCPP_CAR_HPP
#define NSCPP_CAR_HPP

#include <Foundation/Foundation.hpp>

class Car : public NS::Object {
public:
    static Car *alloc();
    Car *init();
    Car *autorelease();

    void drive();
};

#endif  // NSCPP_CAR_HPP
