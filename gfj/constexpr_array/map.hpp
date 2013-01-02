#if !defined GFJ_ARRAY_MAP_HPP_INCLUDED
#define      GFJ_ARRAY_MAP_HPP_INCLUDED

#include <array>
#include <type_traits>
#include "../index_tuple.hpp"

namespace gfj {

    namespace detail {

        template<class T, std::size_t N, class Func, std::size_t... Indices>
        inline constexpr std::array<T, N> map_impl( Func f, std::array<T, N> && a, gfj::index_tuple<Indices...> )
        {
            return {{ std::forward<T>( f( std::get<Indices>(a) ) )... }};
        }
    } // namespace detail

    template<class T, std::size_t N, class Func>
    inline constexpr std::array<T, N> map( Func f, std::array<T, N> && a )
    {
        return detail::map_impl( f, std::forward<T>(a), gfj::idx_range<0, N>() );
    }

} // namespace gfj

#endif    // GFJ_ARRAY_MAP_HPP_INCLUDED
