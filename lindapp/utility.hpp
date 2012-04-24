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

namespace impl{
    template< class Func, class Iter1, class Iter2 >
    auto zip_with_elem(Func const& func, std::size_t offset, Iter1 iter1, Iter2 iter2)->decltype(func(*(iter1+offset), *(iter2+offset)))
    // typename Iter1::value_type zip_with_elem(Func const& func, std::size_t offset, Iter1 iter1, Iter2 iter2)
    {
        return func( *(iter1+offset), *(iter2+offset) );
    }

    template< class Func, class Iter, class... Iters >
    // typename std::result_of<Func>::type zip_with_elem(Func const& func, std::size_t offset, Iter head, Iters... rest)
    auto zip_with_elem(Func const& func, std::size_t offset, Iter head, Iters... rest)->decltype(func( *(head+offset), zip_with_elem(func, offset, rest... )))
    {
        return func( *(head+offset), zip_with_elem(func, offset, rest... ));
    }
}

template< class Func, class ResultIter, class FromIter, class... Iters >
ResultIter zip_with( Func const& func, ResultIter result, FromIter frombegin, FromIter fromend, Iters... rest_iters)
{
    std::size_t offset = 0;
    for( auto from = frombegin;
         from!=fromend;
         ++from, ++offset ){
        *(result+offset) = impl::zip_with_elem( func, offset, frombegin, rest_iters... );
    }

    return result;
}

}
#endif // LINDAPP_UTILITY_HPP__
