#include <Foundation/Foundation.hpp>
#include "Car.hpp"

int main(int argc, char *argv[]) {
    autoreleasepool {
        // Car *car = [[[Car alloc] init] autorelease];
        Car *car = Car::alloc()->init()->autorelease();

        // [car drive];
        car->drive();
    }

    return 0;
}