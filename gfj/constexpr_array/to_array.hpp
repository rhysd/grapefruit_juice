#if !defined TO_ARRAY_HPP_INCLUDED
#define TO_ARRAY_HPP_INCLUDED

#include <array>
#include "../index_tuple.hpp"

namespace gfj{

namespace detail{
    template <class T, std::size_t N, std::size_t... Indices>
    inline constexpr std::array<T, N> to_array_impl( T const(& native_array)[N], gfj::index_tuple<Indices...>)
    {
        return {{ native_array[Indices]... }};
    }
}

template <class T, std::size_t N>
inline constexpr std::array<T, N> to_array( T const(& native_array)[N])
{
    return detail::to_array_impl( native_array, typename gfj::index_range<0, N>::type() );
}

}

#endif // TO_ARRAY_HPP_INCLUDED
