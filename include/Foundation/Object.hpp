#ifndef NS_OBJECT
#define NS_OBJECT

#include <objc/message.h>
#include <objc/objc.h>

#include <iostream>
#include <type_traits>

namespace NS {

// Forward declarations to avoid circular includes
class Object;
class String;

template <class T, class Super = class Object>
class ReferenceCounted : public Super {
public:
    T *retain() noexcept;
    void release() noexcept;

    T *autorelease() noexcept;
    [[nodiscard]] std::uintptr_t retainCount() const noexcept;
};

template <class T, class Super = class Object>
class Copying : public ReferenceCounted<T, Super> {
public:
    T* copy() const;
};

class Object : public ReferenceCounted<Object, objc_object> {
public:
    [[nodiscard]] std::uintptr_t hash() const;
    [[nodiscard]] bool isEqual(const Object *pObject) const;

    [[nodiscard]] String *description() const;
    [[nodiscard]] String *debugDescription() const;

protected:
    friend class ReferenceCounted<Object, objc_object>;

    template <class T>
    static T *alloc(const char *pClassName);

    template <class T>
    static T *alloc(void *pClass);

    template <class T>
    T *init();

    template <class T>
    static T bridgingCast(const void *pObject);

    template <typename T, typename ...Args>
    static T sendMessage(const void *pObject, SEL selector, Args ...args);

    template <typename T, typename ...Args>
    static T sendMessageSafely(const void *pObject, SEL selector, Args ...args);

    template <typename T>
    static constexpr bool requiresMsgSendStret();

    static bool respondsToSelector(const void *pObject, SEL selector);

    static class MethodSignature *methodSignatureForSelector(
        const void *pObject, SEL selector);

private:
    Object() = delete;
    Object(const Object &) = delete;
    ~Object() = delete;

    Object &operator=(const Object &) = delete;
};

template <class T, class Super>
T *ReferenceCounted<T, Super>::retain() noexcept {
    return Object::sendMessage<T *>(this, sel_registerName("retain"));
}

template <class T, class Super>
void ReferenceCounted<T, Super>::release() noexcept {
    return Object::sendMessage<void>(this, sel_registerName("release"));
}

template <class T, class Super>
T *ReferenceCounted<T, Super>::autorelease() noexcept {
    return Object::sendMessage<T *>(this, sel_registerName("autorelease"));
}

template <class T, class Super>
std::uintptr_t ReferenceCounted<T, Super>::retainCount() const noexcept {
    return Object::sendMessage<uintptr_t>(this,
                                          sel_registerName("retainCount"));
}

template <class T, class Super>
T *Copying<T, Super>::copy() const {
    return Object::sendMessage<std::uintptr_t>(this, sel_registerName("copy"));
}

template <class T>
T *Object::alloc(const char *pClassName) {
    return sendMessage<T *>(objc_lookUpClass(pClassName),
                            sel_registerName("alloc"));
}

template <class T>
T *Object::alloc(void *pClass) {
    return sendMessage<T *>(pClass, sel_registerName("alloc"));
}

template <class T>
T *Object::init() {
    return sendMessage<T *>(this, sel_registerName("init"));
}

template <class T>
T Object::bridgingCast(const void *pObject) {
    static_assert(std::is_pointer_v<T>,
                  "bridgingCast<T> requires T to be a pointer type");
    return reinterpret_cast<T>(pObject);
}

template <typename T, typename... Args>
T Object::sendMessage(const void *pObject, SEL selector, Args... args) {
#if (defined(__i386__) || defined(__x86_64__))
    if constexpr (std::is_floating_point<T>) {
        using ObjcMsgSendFpretFn = T (*)(const void *, SEL, Args...);
        const ObjcMsgSendFpretFn func =
            reinterpret_cast<ObjcMsgSendFpretFn>(&objc_msgSend_fpret);

        return (*func)(pObject, selector, args);
    }
#endif
#if !defined(__arm64__)
    if constexpr (requiresMsgSendStret<T>()) {
        using ObjcMsgSendStretFn = void (*)(const void *, SEL, Args...);
        const ObjcMsgSendStretFn func =
            reinterpret_cast<ObjcMsgSendStretFn>(&objc_msgSend_stret);

        T returnType;
        (*func)(&returnType, pObject, selector, args...);

        return returnType;
    }
#endif
    // if defined(__arm64__)
    {
        using ObjcMsgSendFn = T (*)(const void *, SEL, Args...);
        const ObjcMsgSendFn func =
            reinterpret_cast<ObjcMsgSendFn>(&objc_msgSend);

        return (*func)(pObject, selector, args...);
    }
}

template <typename T, typename... Args>
T Object::sendMessageSafely(const void *pObject, SEL selector, Args... args) {
    if ((respondsToSelector(pObject, selector)) ||
        (nullptr != methodSignatureForSelector(pObject, selector))) {
        return sendMessage<T>(pObject, selector, args...);
    }

    if constexpr (!std::is_void_v<T>) {
        return 0;
    }

    return 0;
}

template <typename T>
constexpr bool Object::requiresMsgSendStret() {
#if (defined(__i386__) || defined(__x86_64__))
    constexpr size_t kStructLimit = (sizeof(std::uintptr_t) << 1);

    return sizeof(T) > kStructLimit;
#elif defined(__arm64__)
    return false;
#elif defined(__arm__)
    constexpr size_t kStructLimit = sizeof(std::uintptr_t);

    return std::is_class(T) && (sizeof(T) > kStructLimit);
#else
#error "Unsupported architecture!"
#endif
}

}  // namespace ns

#endif  // NS_OBJECT