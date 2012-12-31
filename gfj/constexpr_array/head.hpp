#if !defined GFJ_ARRAY_HEAD_HPP_INCLUDED
#define      GFJ_ARRAY_HEAD_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace gfj {

template<class T, std::size_t N>
inline constexpr T head(std::array<T, N> && a)
{
    return std::get<0>(a);
}

} // namespace gfj
#endif // GFJ_ARRAY_HEAD_HPP_INCLUDED
