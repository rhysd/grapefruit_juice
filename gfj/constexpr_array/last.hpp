#if !defined GFJ_ARRAY_LAST_HPP_INCLUDED
#define      GFJ_ARRAY_LAST_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace gfj {

    template<class T, std::size_t N>
    inline constexpr T last(std::array<T, N> const& a)
    {
        return std::get<N-1>(a);
    }

} // namespace gfj

#endif // GFJ_ARRAY_LAST_HPP_INCLUDED
