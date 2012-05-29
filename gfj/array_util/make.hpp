#if !defined LINDAPP_MAKE_HPP_INCLUDED__
#define LINDAPP_MAKE_HPP_INCLUDED__

#include <array>
#include <type_traits>
#include "../index_tuple.hpp"
#include "../types/traits_util.hpp"

namespace gfj{

    // make_array: element type is common type of args
    template <class T, class Array>
    inline constexpr std::array<T, 0> make_array()
    {
        return std::array<T, 0>{{}};
    }

    template <
                class... Args, 
                class ElemType = typename std::decay<typename std::common_type<Args...>::type>::type
             >
    inline constexpr std::array<ElemType, sizeof...(Args)> make_array(Args &&... args)
    {
        return {{ std::forward<ElemType>(args)... }};
    }

    // make_array2: element type is a type of first element of args
    template <class T>
    inline constexpr std::array<T, 0> make_array2()
    {
        return {{}};
    }

    template < class First, class... Rest >
    inline constexpr std::array<First, sizeof...(Rest)+1> make_array2(First && f, Rest &&... rest)
    {
        return {{ std::forward<First>(f), std::forward<Rest>(rest)... }};
    }

    template < class Func, class... Args, class ElemType = typename std::result_of<Func(gfj::first_of<Args...>)>::type >
    inline constexpr auto make_array_with(Func && f, Args &&... args)
        -> std::array< ElemType, sizeof...(Args) >
    {
        return {{ std::forward<ElemType>(f(args))... }};
    }

    namespace detail{
        template <class T, std::size_t N, std::size_t... Indices>
        constexpr std::array<T, N> to_array_impl( T const(& native_array)[N], gfj::index_tuple<Indices...>)
        {
            return {{ native_array[Indices]... }};
        }
    }

    template <class T, std::size_t N>
    constexpr std::array<T, N> to_array( T const(& native_array)[N])
    {
        return detail::to_array_impl( native_array, typename gfj::index_range<0, N>::type() );
    }

    namespace detail{
        template< class T, std::size_t N, std::size_t... Indices >
        inline constexpr std::array<T, N> taken_impl( gfj::index_tuple<Indices...> )
        {
            return {{ Indices... }};
        }
    }

    template<class T, size_t N>
    inline constexpr std::array<T, N> taken()
    {
        return detail::taken_impl<T, N>( gfj::idx_range<0, N>() );
    }

    namespace detail{
        template< std::size_t N, std::size_t... Indices, class Func,
                  class ResultType = typename std::result_of<Func(std::size_t)>::type >
        inline constexpr std::array<ResultType, N> taken_with_impl( Func && f, gfj::index_tuple<Indices...> )
        {
            return {{ std::forward<ResultType>(f(Indices))... }};
        }
    }

    template<size_t N, class Func>
    inline constexpr auto taken_with(Func && f)
        -> std::array<typename std::result_of<Func(std::size_t)>::type, N>
    {
        return detail::taken_with_impl<N>( std::forward<Func>(f), gfj::idx_range<0, N>() );
    }

}
#endif // LINDAPP_MAKE_HPP_INCLUDED__