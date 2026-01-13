#include "Car.hpp"

#include <objc/message.h>
#include <objc/runtime.h>

#include <mutex>

namespace {

Class g_carClass = nullptr;
std::once_flag g_registerOnce;

void Car_drive(id self, SEL command) { NS::Log("Vroom!"); }

}  // anonymous namespace

static void registerCarClass() {
    Class NSObjectClass = objc_getClass("NSObject");
    g_carClass = objc_allocateClassPair(NSObjectClass, "Car", 0);

    class_addMethod(g_carClass, sel_registerName("drive"),
                    reinterpret_cast<IMP>(Car_drive), "v@:");

    objc_registerClassPair(g_carClass);
}

Car *Car::alloc() {
    std::call_once(g_registerOnce, registerCarClass);

    return NS::Object::alloc<Car>(g_carClass);
}

Car *Car::init() { return NS::Object::init<Car>(); }

Car *Car::autorelease() {
    return reinterpret_cast<Car *>(NS::Object::autorelease());
}

void Car::drive() {
    using func = void (*)(id, SEL);
    static SEL selector = sel_registerName("drive");

    reinterpret_cast<func>(objc_msgSend)(static_cast<id>(this), selector);
}
