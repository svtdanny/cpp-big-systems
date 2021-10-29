#include <iostream>
class A {
public:
// ...
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

template<class T>
struct _type_helper;

template<class T>
class CustomAllocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;

    CustomAllocator() noexcept{}

    template<class U>
    CustomAllocator(const CustomAllocator<U> &) noexcept {}

    template<typename U>
    struct rebind {
        typedef CustomAllocator<U> other;

    };

    T *allocate(size_t n) const {
        return static_cast<T *>(_type_helper<T>::type::operator new(n * sizeof(T)));
    }

    void deallocate(T *p, size_t n) const {
        _type_helper<T>::type::operator delete(p, n);
    }
};


template<class T>
struct _type_helper{
    using type=T;
};

template<class T>
struct _type_helper<std::__1::__shared_ptr_emplace<T, CustomAllocator<T>>>{
using type=T;
};




int main() {
    //auto sp = std::make_shared<A>();

    CustomAllocator<A> alloc;
    auto a1 = std::allocate_shared<A>(alloc);
}