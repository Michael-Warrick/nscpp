#ifndef FOUNDATION_HPP
#define FOUNDATION_HPP

#include <iostream>

#include "Autoreleasepool.hpp"
#include "String.hpp"

#define autoreleasepool \
for (bool _once = true; _once; _once = false) \
for (NS::AutoreleasePool* _pool = NS::AutoreleasePool::alloc()->init(); \
    _once; \
    _pool->release(), _once = false)

namespace NS {

void Log(const char *format, ...);
} // namespace NS

#endif  // FOUNDATION_HPP