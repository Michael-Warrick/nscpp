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
    static String* string(const char* pString, StringEncoding encoding);

    static String *alloc();
    String *init();
    String *initWithFormatArguments(String *format, va_list args);

    [[nodiscard]] const char *cString(StringEncoding encoding) const;
};
} // namespace ns

#endif // NSCPP_STRING_HPP
