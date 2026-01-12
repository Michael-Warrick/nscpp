#include <Foundation/Foundation.hpp>

int main(int argc, char *argv[]) {
    autoreleasepool {
        NS::String *message =
            NS::String::string("Hello, World!", NS::AsciiStringEncoding);
        NS::Log("%s", message->cString(NS::AsciiStringEncoding));
    }

    return 0;
}