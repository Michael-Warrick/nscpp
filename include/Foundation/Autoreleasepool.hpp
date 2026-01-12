#ifndef NS_AUTORELEASEPOOL_HPP
#define NS_AUTORELEASEPOOL_HPP

#include "Object.hpp"

namespace NS
{
    
class AutoreleasePool : public Object
{
public:
    static AutoreleasePool *alloc();

    AutoreleasePool *init();

    void drain() const;

    void addObject(Object *pObject) const;

    static void showPools();
};


} // namespace NS_AUTORELEASEPOOL_HPP


#endif // NSAUTORELEASEPOOL