#include "Foundation/Foundation.hpp"

#include <iostream>

#include <cstdarg>

extern "C" void NSLog(void* format, ...);

namespace NS {

void Log(const char* format, ...) {
    if (!format) return;

    // NSString *fmt = [NSString stringWithUTF8String:utf8Format];
    NS::String* fmt = NS::String::string(format, NS::UTF8StringEncoding);

    va_list args;
    va_start(args, format);

    // NSString *msg = [[NSString alloc] initWithFormat:fmt arguments:args];
    NS::String* msg = NS::String::alloc()->initWithFormatArguments(fmt, args);

    va_end(args);

    // NSLog(@"%@", msg);
    NS::String* percentAt = NS::String::string("%@", NS::UTF8StringEncoding);
    ::NSLog(static_cast<void *>(percentAt), static_cast<void*>(msg));

    msg->release(); // must manually release as using alloc/init
}

} // namespace NS