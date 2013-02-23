#if !defined ADD_HPP_INCLUDED
#define      ADD_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"

namespace gfj{

namespace detail{

    template< class T, std::size_t N, std::size_t... Indices>
    inline constexpr std::array<T, N+1> add_impl( std::array<T, N> const& a, T && item, gfj::index_tuple<Indices...>)
    {
        return {{ std::get<Indices>(a)..., std::forward<T>(item) }};
    }

}

template<class T, std::size_t N>
inline constexpr std::array<T, N+1> add( std::array<T, N> const& a, T && item )
{
    return detail::add_impl(a, std::forward<T>(item), gfj::idx_range<0, N>());
}

}

#endif    // ADD_HPP_INCLUDED
