#include <Foundation/Foundation.hpp>

int main(int argc, char *argv[]) {
    autoreleasepool {
        NS::String *message = NS::String::stringWithUTF8String("Hello, World!");
        NS::Log("%@", message);
    }

    return 0;
}