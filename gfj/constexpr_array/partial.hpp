#if !defined GFJ_ARRAY_PARTIAL_HPP_INCLUDED
#define      GFJ_ARRAY_PARTIAL_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"
#include "detail/partial_array.hpp"

namespace gfj {

    template< std::size_t First, std::size_t Last, class T, std::size_t N >
    inline constexpr std::array<T, N-1> partial(std::array<T, N> && a)
    {
        return detail::partial_array(a, gfj::idx_range<First, Last>());
    }

} // namespace gfj

#endif    // GFJ_ARRAY_PARTIAL_HPP_INCLUDED
