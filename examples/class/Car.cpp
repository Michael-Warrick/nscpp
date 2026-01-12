#include "Car.hpp"

#include <mutex>

#include <objc/runtime.h>
#include <objc/message.h>

namespace {

Class g_carClass = nullptr;
std::once_flag g_registerOnce;

void Car_drive(id self, SEL command) {
    NS::Log("Vroom!");
}

} // anonymous namespace

static void registerCarClass() {
    Class NSObjectClass = (Class)objc_getClass("NSObject");
    g_carClass = objc_allocateClassPair(NSObjectClass, "Car", 0);

    class_addMethod(g_carClass, sel_registerName("drive"), (IMP)Car_drive, "v@:");

    objc_registerClassPair(g_carClass);
}

Car *Car::alloc() {
    std::call_once(g_registerOnce, registerCarClass);

    return NS::Object::alloc<Car>((void *)g_carClass);
}

Car *Car::init() {
    return NS::Object::init<Car>();
}

Car *Car::autorelease() {
    return reinterpret_cast<Car *>(NS::Object::autorelease());
}


void Car::drive() {
using func = void (*)(id, SEL);
    static SEL selector = sel_registerName("drive");

    ((func)objc_msgSend)((id)this, selector);
}

