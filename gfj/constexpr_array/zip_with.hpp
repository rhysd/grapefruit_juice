#if !defined ZIP_WITH_HPP_INCLUDED
#define      ZIP_WITH_HPP_INCLUDED

#include <array>
#include "../index_tuple.hpp"

namespace gfj {

    namespace detail {

        template<class T, class U, std::size_t N, class Func, std::size_t... Indices, class R = typename std::result_of<Func(T, U)>::type>
        inline constexpr std::array<R, N> zip_with_impl( Func f, std::array<T, N> const& a, std::array<U, N> const& b, gfj::index_tuple<Indices...> )
        {
            return {{ std::forward<R>( f( std::get<Indices>(a), std::get<Indices>(b) ) )... }};
        }

    } // namespace detail

    template<class T, class U, std::size_t N, class Func, class R = typename std::result_of<Func(T, U)>::type>
    inline constexpr std::array<R, N> zip_with( Func f, std::array<T, N> const& a, std::array<U, N> const& b)
    {
        return detail::zip_with_impl( f, a, b, gfj::idx_range<0, N>() );
    }
} // namespace gfj
#endif    // ZIP_WITH_HPP_INCLUDED
