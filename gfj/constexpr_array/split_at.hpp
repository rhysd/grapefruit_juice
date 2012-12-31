#if !defined GFJ_ARRAY_SPLIT_AT_HPP_INCLUDED
#define      GFJ_ARRAY_SPLIT_AT_HPP_INCLUDED

#include <array>
#include "../index_tuple.hpp"

namespace gfj{

namespace detail{

    template< class T,
                std::size_t N1, std::size_t... Indices1,
                std::size_t N2, std::size_t... Indices2
            >
    constexpr std::array<T, N1+N2> append_impl( std::array<T, N1> const& a1, gfj::index_tuple<Indices1...>,
                                            std::array<T, N2> const& a2, gfj::index_tuple<Indices2...> )
    {
        return {{ std::get<Indices1>(a1)..., std::get<Indices2>(a2)... }};
    }

} // namespace detail

template< class T, std::size_t N1, std::size_t N2 >
constexpr std::array<T, N1+N2> append( std::array<T, N1> const& a1,
                                            std::array<T, N2> const& a2 )
{
    return detail::append_impl( a1, typename gfj::index_range<0, N1>::type(),
                                        a2, typename gfj::index_range<0, N2>::type() );
}

}
#endif // GFJ_ARRAY_SPLIT_AT_HPP_INCLUDED
