#include "Foundation/Object.hpp"

#include <objc/message.h>

#include <type_traits>

namespace NS {

std::uintptr_t Object::hash() const {
    return sendMessage<uintptr_t>(this, sel_registerName("hash"));
}

bool Object::isEqual(const Object *pObject) const {
    return sendMessage<bool>(this, sel_registerName("isEqual:"), pObject);
}

String *Object::description() const {
    return sendMessage<String *>(this, sel_registerName("description"));
}

String *Object::debugDescription() const {
    return sendMessageSafely<String *>(this,
                                       sel_registerName("debugDescription"));
}

bool Object::respondsToSelector(const void *pObject, SEL selector) {
    return sendMessage<bool>(pObject, sel_registerName("respondsToSelector:"),
                             selector);
}

class MethodSignature *Object::methodSignatureForSelector(const void *pObject,
                                                          SEL selector) {
    return sendMessage<MethodSignature *>(
        pObject, sel_registerName("methodSignatureForSelector:"), selector);
}

}  // namespace ns