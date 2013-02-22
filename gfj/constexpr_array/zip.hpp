#if !defined ZIP_HPP_INCLUDED
#define      ZIP_HPP_INCLUDED

#include <array>
#include "../index_tuple.hpp"

namespace gfj {

namespace detail {

    template< class T, class U, std::size_t N, std::size_t... Indices >
    inline constexpr std::array<std::pair<T, U>, N> zip_impl( std::array<T, N> a1, std::array<U, N> a2, gfj::index_tuple<Indices...> )
    {
        return {{ std::make_pair(std::get<Indices>(a1), std::get<Indices>(a2))... }};
    }
} // namespace detail

template< class T, class U, std::size_t N >
inline constexpr std::array<std::pair<T, U>, N> zip(std::array<T, N> a1, std::array<U, N> a2)
{
    return detail::zip_impl( a1, a2, gfj::idx_range<0, N>() );
}


} // namespace gfj
#endif    // ZIP_HPP_INCLUDED
