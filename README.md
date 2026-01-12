# nscpp
A library attempting to bring Objective-C NeXTSTEP-style programming to the world of C++.

> [!IMPORTANT] 
> This project has elements inspired by the metal-cpp project provided by Apple Inc. and hence the [NOTICE](NOTICE) and [LICENSE](LICENSE) files have been included.

Have you ever wanted to write C++ code as though you were writing Objective-C and all while actually calling REAL Cocoa libraries? Well look no further than libnscpp!

## Example
### Hello World - Objective-C
```objc
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *message = [NSString stringWithUTF8String:"Hello, World!"];
        
        NSLog(@"%@", message);
    }
    
    return 0;
}
```

### Hello World - C++
```cpp
#include <Foundation/Foundation.hpp>

int main(int argc, char *argv[]) {
    autoreleasepool {
        NS::String *message = NS::String::stringWithUTF8String("Hello, World!");
        
        NS::Log("%@", message);
    }
    
    return 0;
}
```
For more examples see the [examples](examples) directory.

## Building
### Prerequisites
- CMake
- macOS SDK (bundled with Xcode)

### Compiling
```shell
# Assuming cwd is nscpp root folder
mkdir build && cd build
```

```shell
cmake ..
```

```shell
cmake --build . --config Release
```

## Resources
- Apple's ["Get started with Metal-cpp"](https://developer.apple.com/metal/cpp/)
- Branimir Karadžić's [metal-cpp](https://github.com/bkaradzic/metal-cpp)
- [Ry's Objective-C Tutorial](https://fullonrager.github.io/rys-objective-c-tutorial-archive/)
