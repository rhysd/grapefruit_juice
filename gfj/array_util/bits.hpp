#if !defined LINDAPP_BITS_HPP_INCLUDED
#define LINDAPP_BITS_HPP_INCLUDED

#include <array>
#include <type_traits>
#include "../index_tuple.hpp"

namespace gfj{

    // constexpr 化されていないので苦肉の策．
    // constexpr に対応次第消す

    template< class T, std::size_t N >
    inline constexpr T const& at(std::array<T, N> const& arr, std::size_t pos)
    {
        return arr._M_instance[pos];
    }

}
#endif // LINDAPP_BITS_HPP_INCLUDED
