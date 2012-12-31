#if !defined GFJ_ARRAY_FILL_HPP_INCLUDED
#define      GFJ_ARRAY_FILL_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"

namespace gfj {

    namespace detail {
        template<std::size_t N, class T, std::size_t... Indices>
        inline constexpr std::array<T, N> fill_impl(T && item, gfj::index_tuple<Indices...>)
        {
            return {{ std::forward<T>((static_cast<void>(Indices), item))... }};
        }
    } // namespace detail

    template<class T, std::size_t N>
    inline constexpr std::array<T, N> fill(std::array<T, N>, T && item)
    {
        return detail::fill_impl<N>( std::forward<T>(item), gfj::idx_range<0, N>() );
    }
} // namespace gfj

#endif    // GFJ_ARRAY_FILL_HPP_INCLUDED
