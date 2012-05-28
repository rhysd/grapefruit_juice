#if !defined LINDAPP_MODIFY_HPP_INCLUDED__
#define LINDAPP_MODIFY_HPP_INCLUDED__

#include <array>
#include "bits.hpp"
#include "../index_tuple.hpp"

namespace gfj{

    namespace detail{

       template< class T,
                  std::size_t N1, std::size_t... Indices1,
                  std::size_t N2, std::size_t... Indices2
                >
        constexpr std::array<T, N1+N2> joint_array_impl( std::array<T, N1> const& a1, gfj::index_tuple<Indices1...>,
                                              std::array<T, N2> const& a2, gfj::index_tuple<Indices2...> )
        {
            return {{ at(a1, Indices1)..., at(a2, Indices2)... }};
        }

    } // namespace detail

    template< class T, std::size_t N1, std::size_t N2 >
    constexpr std::array<T, N1+N2> joint_array( std::array<T, N1> const& a1,
                                                std::array<T, N2> const& a2 )
    {
        return detail::joint_array_impl( a1, typename gfj::index_range<0, N1>::type(),
                                         a2, typename gfj::index_range<0, N2>::type() );
    }

    /* 引数解決ができずコンパイルエラー．
    namespace detail{
        template< class T, std::size_t N, std::size_t Sep,
                  std::size_t... Indices1, std::size_t... Indices2 >
        constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> > 
                split_array_impl( std::array<T, N> const& a, gfj::index_tuple<Indices1...>, gfj::index_tuple<Indices2...> )
        {
            return std::make_pair( std::array<T, Sep>{{ at(a, Indices1)... }},
                                   std::array<T, N-Sep>{{ at(a, Indices2)... }} );
        }
    }

    template< std::size_t Sep, class T, std::size_t N >
    constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> > split_array( std::array<T, N> const& a )
    {
        return detail::split_array_impl( a, typename gfj::index_range<0, Sep>::type(),
                                            typename gfj::index_range<Sep, N>::type() );
    }
    */
}
#endif // LINDAPP_MODIFY_HPP_INCLUDED__
