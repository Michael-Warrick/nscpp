#include "Foundation/Autoreleasepool.hpp"

#include <objc/runtime.h>

namespace NS {

AutoreleasePool *AutoreleasePool::alloc() {
    return Object::alloc<AutoreleasePool>(objc_lookUpClass("NSAutoReleasePool"));
}


AutoreleasePool *AutoreleasePool::init() {
    return Object::init<AutoreleasePool>();
}


void AutoreleasePool::drain() const {
    Object::sendMessage<void>(this, sel_registerName("drain"));
}

void AutoreleasePool::addObject(Object *pObject) const {
    Object::sendMessage<void>(this, sel_registerName("addObject:"), pObject);
}

void AutoreleasePool::showPools() {
    Object::sendMessage<void>(objc_lookUpClass("NSAutoReleasePool"), sel_registerName("showPools"));
}

}