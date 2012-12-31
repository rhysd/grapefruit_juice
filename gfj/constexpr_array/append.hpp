#if !defined GFJ_ARRAY_APPEND_HPP_INCLUDED
#define      GFJ_ARRAY_APPEND_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <utility>
#include "../index_tuple.hpp"

namespace gfj{

namespace detail{
    template< std::size_t Sep, class T, std::size_t N,
                std::size_t... Indices1, std::size_t... Indices2 >
    inline constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> >
            split_at_impl( std::array<T, N> a, gfj::index_tuple<Indices1...>, gfj::index_tuple<Indices2...> )
    {
        return std::make_pair( std::array<T, Sep>{{ std::get<Indices1>(a)... }},
                                std::array<T, N-Sep>{{ std::get<Indices2>(a)... }} );
    }
}

template< std::size_t Sep, class T, std::size_t N >
inline constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> > split_at( std::array<T, N> a )
{
    return detail::split_at_impl<Sep>( a, typename gfj::index_range<0, Sep>::type(),
                                        typename gfj::index_range<Sep, N>::type() );
}

}
#endif // GFJ_ARRAY_APPEND_HPP_INCLUDED
