#if !defined LINDAPP_COMPARE_HPP_INCLUDED
#define LINDAPP_COMPARE_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace gfj{

namespace detail{
    extern void* enabler;

    template< std::size_t I, class T, class U, std::size_t N, typename std::enable_if<(I>0)>::type *& = enabler >
    constexpr bool equal_impl(std::array<T,N> arr1, std::array<U,N> arr2)
    {
        return (std::get<I>(arr1) == std::get<I>(arr2)) && equal_impl<I-1>(arr1, arr2);
    }

    template< std::size_t I, class T, class U, std::size_t N, typename std::enable_if<I==0>::type *& = enabler >
    constexpr bool equal_impl(std::array<T,N> arr1, std::array<U,N> arr2)
    {
        return (std::get<I>(arr1) == std::get<I>(arr2));
    }
}

template< class T, class U, std::size_t N >
inline constexpr bool equal(std::array<T,N> arr1, std::array<U,N> arr2)
{
    return detail::equal_impl<N-1>(arr1, arr2);
}

}
#endif // LINDAPP_COMPARE_HPP_INCLUDED
