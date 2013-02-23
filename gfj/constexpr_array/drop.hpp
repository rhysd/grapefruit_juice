#if !defined GFJ_ARRAY_DROP_HPP_INCLUDED
#define      GFJ_ARRAY_DROP_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"
#include "detail/partial_array.hpp"

namespace gfj {

    template<std::size_t I, class T, std::size_t N>
    inline constexpr std::array<T, N-I> drop(std::array<T, N> const& a)
    {
        return detail::partial_array(a, gfj::idx_range<I, N>());
    }
} // namespace gfj

#endif    // GFJ_ARRAY_DROP_HPP_INCLUDED
