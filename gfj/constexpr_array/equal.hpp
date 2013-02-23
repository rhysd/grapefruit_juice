#if !defined LINDAPP_COMPARE_HPP_INCLUDED
#define LINDAPP_COMPARE_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace gfj{

namespace detail{

    template< std::size_t I, class T, class U, std::size_t N >
    struct equal_impl{
        constexpr bool operator()(std::array<T, N> const& arr1, std::array<U, N> const& arr2)
        {
            return (std::get<I>(arr1) == std::get<I>(arr2)) && equal_impl<I-1, T, U, N>()(arr1, arr2);
        }
    };

    template<class T, class U, std::size_t N>
    struct equal_impl<0, T, U, N>{
        constexpr bool operator()(std::array<T, N> const& arr1, std::array<U, N> const& arr2)
        {
            return (std::get<0>(arr1) == std::get<0>(arr2));
        }
    };

}

template< class T, class U, std::size_t N >
inline constexpr bool equal(std::array<T,N> const& arr1, std::array<U,N> const& arr2)
{
    return detail::equal_impl<N-1, T, U, N>()(arr1, arr2);
}

}
#endif // LINDAPP_COMPARE_HPP_INCLUDED
