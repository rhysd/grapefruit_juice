#if !defined GFJ_ARRAY_DETAIL_PARTIAL_ARRAY_HPP_INCLUDED
#define      GFJ_ARRAY_DETAIL_PARTIAL_ARRAY_HPP_INCLUDED

#include "../../index_tuple.hpp"

namespace gfj {

    namespace detail {

        template< class T, std::size_t N, std::size_t... Indices >
        inline constexpr std::array<T, sizeof...(Indices)> partial_array(std::array<T, N> const& a, gfj::index_tuple<Indices...>)
        {
            return {{ std::get<Indices>(a)... }};
        }

    } // namespace detail

}

#endif    // GFJ_ARRAY_DETAIL_PARTIAL_ARRAY_HPP_INCLUDED
