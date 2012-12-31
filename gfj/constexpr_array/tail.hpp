#if !defined GFJ_ARRAY_TAIL_HPP_INCLUDED
#define      GFJ_ARRAY_TAIL_HPP_INCLUDED

#include <array>
#include <cstddef>
#include "../index_tuple.hpp"
#include "detail/partial_array.hpp"

namespace gfj {

    template< class T, std::size_t N >
    inline constexpr std::array<T, N-1> tail(std::array<T, N> a)
    {
        return detail::partial_array(a, gfj::idx_range<0, N-1>());
    }

} // namespace gfj

#endif // GFJ_ARRAY_TAIL_HPP_INCLUDED
