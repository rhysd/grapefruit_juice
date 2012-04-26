#ifndef LINDAPP_UTILITY_HPP__
#define LINDAPP_UTILITY_HPP__

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <functional>

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
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template < class Container, class... Containers >
void print_cs( Container const& head, Containers const& ... rest)
{
    print_cs( head );
    print_cs( rest... );
}

template< class Iterator,
          class Comp = std::less<typename Iterator::value_type>,
          class Pred = std::equal_to<typename Iterator::value_type>
        >
inline Iterator unique( Iterator first,
                 Iterator last,
                 Comp comp=std::less<typename Iterator::value_type>(),
                 Pred pred=std::equal_to<typename Iterator::value_type>()
               )
{
    std::sort(first, last, comp);
    return std::unique(first, last, pred);
}

template< class Func, class OutputIter, class InputIter, class... InputIters >
OutputIter zip_with( Func const& func, OutputIter result, InputIter frombegin, InputIter fromend, InputIters... rest_iters)
{
    for( auto from = frombegin;
         from!=fromend;
         ++from ){
        typename OutputIter::value_type ret = *from;
        for( auto &iter_ptr : {(&rest_iters)...} ){
            ret = func( ret, *(*iter_ptr) );
            ++(*iter_ptr);
        }
        *result = ret;
        ++result;
    }
    return result;
}

template< class Func, class OutputIter, class InputIter, class... InputIters >
OutputIter zip_with2( Func const& func, OutputIter result, InputIter from_begin, InputIter from_end, InputIters... rest_iters )
{
    for( auto from = from_begin;
         from!=from_end;
         ++from ){
        *result = func( *from, (*rest_iters)... );
        for( auto &iter_ptr : {(&rest_iters)...} ){
            ++(*iter_ptr);
        }
        ++result;
    }
    return result;
}

}
#endif // LINDAPP_UTILITY_HPP__
