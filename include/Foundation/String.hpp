#ifndef NSCPP_STRING_HPP
#define NSCPP_STRING_HPP

#include "Foundation/Object.hpp"

namespace NS {
enum StringEncoding : uintptr_t {
    AsciiStringEncoding = 1,
    UTF8StringEncoding = 4
};

class String : public Copying<String> {
public:
    static String *alloc();
    String *init();
    String *initWithFormat(String *format, va_list arguments);

    static String *stringWithCString(const char *pString, StringEncoding encoding);
    static String *stringWithUTF8String(const char *pString);

    [[nodiscard]] const char *cString(StringEncoding encoding) const;
};
} // namespace ns

#endif // NSCPP_STRING_HPP
