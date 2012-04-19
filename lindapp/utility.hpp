#ifndef LINDAPP_UTILITY_HPP__
#define LINDAPP_UTILITY_HPP__

#include <algorithm>
#include <cstddef>
#include <iostream>

namespace lindapp{

template< std::size_t N, class Func, class... Args >
void times(Func func, Args... args)
{
    for(std::size_t i=0; i<N; ++i){
        func(args...);
    }
}

template< class Func, class... Args >
void times(std::size_t const n, Func const& func, Args... args)
{
    for(std::size_t i=0; i<n; ++i){
        func(args...);
    }
}

template< class T >
T max_many( T const& a, T const& b)
{
    return a>b ? a : b;
}

template< class T, class... Rest >
T max_many( T const& head, Rest... rest)
{
    return std::max( head, max_many( rest... ) );
}

template< class T >
T min_many( T const& a, T const& b)
{
    return a<b ? a : b;
}

template< class T, class... Rest >
T min_many( T const& head, Rest... rest)
{
    return std::min( head, min_many( rest... ) );
}

template< class Container >
void print_cs( Container const& container )
{
    for(auto const& i : container){
        std::cout << i << ',';
    }
    std::cout << std::endl;
}

template < class Container, class... Containers >
void print_cs( Container const& head, Containers const& ... rest)
{
    print_cs( head );
    print_cs( rest... );
}

}
#endif // LINDAPP_UTILITY_HPP__
