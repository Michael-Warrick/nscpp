#include "Foundation/String.hpp"

namespace NS {

String *String::alloc() {
    return Object::alloc<String>(objc_lookUpClass("NSString"));
}

String *String::init() { return Object::init<String>(); }

String *String::initWithFormat(String *format, const va_list arguments) {
    using func = id (*)(id, SEL, id, va_list);

    id result = reinterpret_cast<func>(objc_msgSend)(
        reinterpret_cast<id>(this),
        sel_registerName("initWithFormat:arguments:"),
        reinterpret_cast<id>(format), arguments);

    return reinterpret_cast<String *>(result);
}

String *String::stringWithCString(const char *pString,
                                  StringEncoding encoding) {
    return Object::sendMessage<String *>(
        objc_lookUpClass("NSString"),
        sel_registerName("stringWithCString:encoding:"), pString, encoding);
}

String *String::stringWithUTF8String(const char *pString) {
    return Object::sendMessage<String *>(
        objc_lookUpClass("NSString"),
        sel_registerName("stringWithUTF8String:"), pString);
}

const char *String::cString(const StringEncoding encoding) const {
    return Object::sendMessage<const char *>(
        this, sel_registerName("cStringUsingEncoding:"), encoding);
}

}  // namespace NS