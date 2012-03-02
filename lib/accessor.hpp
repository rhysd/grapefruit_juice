#ifndef __ACCESSOR_HPP__
#define __ACCESSOR_HPP__

#include <functional>

namespace lindapp{

    enum struct access{ getter = 0, setter };

    template<class T>
    class accessor_base{
    public:
        T value;
        accessor_base() = default;
        accessor_base(T const& t) : value(t){};
        accessor_base(T && t) : value(t){};
    };

    template< class T, access... Access >
    class accessor;

    template< class T >
    class accessor< T, access::getter > : private accessor_base<T>{
    public:
        accessor() = default;
        accessor(T const& t) : accessor_base<T>(t) {};
        accessor(T && t) : accessor_base<T>(std::forward<T>(t)) {};

        T get() const { return accessor_base<T>::value; }
    };

    template< class T >
    class accessor< T, access::setter > : private accessor_base<T>{
    public:
        accessor(T const& t) : accessor_base<T>(t) {};
        accessor(T && t) : accessor_base<T>(std::forward(t)) {};

        void set(T const& t){ accessor_base<T>::value = t; }
    };

    template< class T, access Access >
    class accessor< T, Access, Access >;

    template< class T, access Access1, access Access2 >
    class accessor< T, Access1, Access2 > : private accessor_base<T>{
    public:
        accessor(T const& t) : accessor_base<T>(t) {};
        accessor(T && t) : accessor_base<T>(std::forward<T>(t)) {};

        T get() const { return accessor_base<T>::value; }
        void set(T const& t){ accessor_base<T>::value = t; }
    };

}

#endif // __ACCESSOR_HPP__
