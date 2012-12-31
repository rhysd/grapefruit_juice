#if !defined GFJ_ARRAY_FILLED_HPP_INCLUDED
#define      GFJ_ARRAY_FILLED_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"

namespace gfj {

    namespace detail {
        template<std::size_t N, class T, std::size_t... Indices>
        inline constexpr std::array<T, N> filled_array_impl(T && item, gfj::index_tuple<Indices...>)
        {
            return {{ std::forward<T>((static_cast<void>(Indices), item))... }};
        }
    } // namespace detail

    template<std::size_t N, class T>
    inline constexpr std::array<T, N> filled_array(T && item)
    {
        return detail::filled_array_impl<N>( std::forward<T>(item), gfj::idx_range<0, N>() );
    }
} // namespace gfj

#endif    // GFJ_ARRAY_FILLED_HPP_INCLUDED
