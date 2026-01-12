#include "Foundation/Foundation.hpp"

#include <iostream>

#include <cstdarg>

extern "C" void NSLog(void* format, ...);

namespace NS {

void Log(const char* format, ...) {
    if (!format) return;

    // NSString *fmt = [NSString stringWithUTF8String:format];
    NS::String* fmt = NS::String::stringWithUTF8String(format);

    va_list args;
    va_start(args, format);

    // NSString *msg = [[NSString alloc] initWithFormat:fmt arguments:args];
    NS::String* msg = NS::String::alloc()->initWithFormat(fmt, args);

    va_end(args);

    // NSLog(@"%@", msg);
    NS::String* percentAt = NS::String::stringWithCString("%@", NS::UTF8StringEncoding);
    ::NSLog(static_cast<void *>(percentAt), static_cast<void*>(msg));

    msg->release(); // must manually release as using alloc/init
}

} // namespace NS