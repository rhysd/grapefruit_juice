#if !defined LINDAPP_COMPARE_HPP_INCLUDED
#define LINDAPP_COMPARE_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace gfj{

namespace detail{
    template< class T, class U, std::size_t N >
    inline constexpr bool equal_impl(std::array<T,N> && arr1, std::array<U,N> && arr2, std::size_t idx)
    {
        return N==0 ? at(arr1, idx) == at(arr2, idx) :
                      (at(arr1, idx) == at(arr2, idx)) && equal_impl(std::forward<std::array<T,N>>(arr1), std::forward<std::array<U,N>>(arr2), idx-1);
    }
}

template< class T, class U, std::size_t N >
inline constexpr bool equal(std::array<T,N> && arr1, std::array<U,N> && arr2)
{
    return detail::equal_impl(std::forward<std::array<T,N>>(arr1), std::forward<std::array<U,N>>(arr2), N-1);
}

}
#endif // LINDAPP_COMPARE_HPP_INCLUDED
