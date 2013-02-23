#if !defined GFJ_ARRAY_MAP_HPP_INCLUDED
#define      GFJ_ARRAY_MAP_HPP_INCLUDED

#include <array>
#include <type_traits>
#include "../index_tuple.hpp"

namespace gfj {

    namespace detail {

        template<class T, std::size_t N, class Func, std::size_t... Indices, class R = typename std::result_of<Func(T)>::type>
        inline constexpr std::array<R, N> map_impl( Func f, std::array<T, N> const& a, gfj::index_tuple<Indices...> )
        {
            return {{ std::forward<R>( f( std::get<Indices>(a) ) )... }};
        }
    } // namespace detail

    template<class T, std::size_t N, class Func, class R = typename std::result_of<Func(T)>::type>
    inline constexpr std::array<R, N> map( Func f, std::array<T, N> const& a )
    {
        return detail::map_impl( f, a, gfj::idx_range<0, N>() );
    }
} // namespace gfj

#endif    // GFJ_ARRAY_MAP_HPP_INCLUDED
