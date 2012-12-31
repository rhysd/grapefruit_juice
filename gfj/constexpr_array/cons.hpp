#if !defined GFJ_ARRAY_CONS_HPP_INCLUDED
#define      GFJ_ARRAY_CONS_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"

namespace gfj{

namespace detail{

    template< class T, std::size_t N, std::size_t... Indices>
    inline constexpr std::array<T, N+1> cons_impl(T && item, std::array<T, N> && a, gfj::index_tuple<Indices...>)
    {
        return {{ std::forward<T>(item), std::forward<T>(std::get<Indices>(a))... }};
    }

}

template<class T, std::size_t N>
inline constexpr std::array<T, N+1> cons(T && item, std::array<T, N> && a)
{
    return detail::cons_impl(std::forward<T>(item),
                             std::forward<std::array<T, N>>(a),
                             gfj::idx_range<0, N>());
}

}

#endif    // GFJ_ARRAY_CONS_HPP_INCLUDED

