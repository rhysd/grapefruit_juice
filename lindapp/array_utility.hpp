#ifndef __LINDAPP_MAKE_ARRAY_HPP__
#define __LINDAPP_MAKE_ARRAY_HPP__

// make_array:  引数を要素に取る std::array を生成
// make_array2: 型を最初の要素から推測するver
// to_array:    生配列から std::array を生成
// joint:       std::array の結合

#include <array>
#include <type_traits>

namespace lindapp {

    // make_array: element type is common type of args
    template <class T>
    inline std::array<T, 0> make_array()
    {
        return std::array<T, 0>{{}};
    }

    template <
                class... Args, 
                class Result = std::array<
                typename std::decay<typename std::common_type<Args...>::type>::type,
                sizeof...(Args)>
             >
    inline Result make_array(Args &&... args)
    {
        return Result{{ std::forward<Args>(args)... }};
    }

    // make_array2: element type is a type of first element of args
    template <class T>
    inline std::array<T, 0> make_array2()
    {
        return std::array<T, 0>{{}};
    }

    template <
                class First,
                class... Rest,
                class Result = std::array<First, sizeof...(Rest)+1>
             >
    inline Result make_array2(First && f, Rest &&... rest)
    {
        return Result{{ std::forward<First>(f), std::forward<Rest>(rest)... }};
    }

    template <class T, std::size_t N, class Result = std::array<T, N>>
    Result to_array( T const(& native_array)[N] )
    {
        Result ret;
        for(std::size_t i = 0; i < N; ++i){
            ret[i] = native_array[i];
        }
        return std::move( ret );
    }

    namespace detail{

        // operator[] や data() は constexpr 化されていないので苦肉の策．
        // constexpr に対応次第消す
        template< class T, std::size_t N>
        constexpr T const& at(std::array<T, N> const& arr, std::size_t pos)
        {
            return arr._M_instance[pos];
        }

        template< std::size_t... Indices >
        struct index_tuple{};

        template < std::size_t Start,
                   std::size_t Last,
                   class Acc = index_tuple<>,
                   bool Finish = (Start>=Last) >
        struct index_range{
            typedef Acc type;
        };

        template < std::size_t Start,
                   std::size_t Last,
                   std::size_t... Indices >
        struct index_range< Start, Last, index_tuple<Indices...>, false >
                : index_range<Start+1, Last, index_tuple<Indices..., Start>>
        {};

        template< class T,
                  std::size_t N1, std::size_t... Indices1,
                  std::size_t N2, std::size_t... Indices2
                >
        constexpr std::array<T, N1+N2> joint_array_impl( std::array<T, N1> const& a1, index_tuple<Indices1...>,
                                              std::array<T, N2> const& a2, index_tuple<Indices2...> )
        {
            return {{ at(a1, Indices1)..., at(a2, Indices2)... }};
        }

    } // namespace detail

    template< class T, std::size_t N1, std::size_t N2 >
    constexpr std::array<T, N1+N2> joint_array( std::array<T, N1> const& a1,
                                                std::array<T, N2> const& a2 )
    {
        return detail::joint_array_impl( a1, typename detail::index_range<0, N1>::type(),
                                         a2, typename detail::index_range<0, N2>::type() );
    }

    namespace detail{
        template< class T, std::size_t N, std::size_t Sep,
                  std::size_t... Indices1, std::size_t... Indices2 >
        constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> > 
                split_array_impl( std::array<T, N> const& a, index_tuple<Indices1...>, index_tuple<Indices2...> )
        {
            return std::make_pair( std::array<T, Sep>{{ at(a, Indices1)... }},
                                   std::array<T, N-Sep>{{ at(a, Indices2)... }} );
        }
    }

    template< std::size_t Sep, class T, std::size_t N >
    constexpr std::pair< std::array<T, Sep>, std::array<T, N-Sep> > split_array( std::array<T, N> const& a )
    {
        static_assert( 0<Sep&&Sep<=N, "split_array: separater is out of bounds.");
        return detail::split_array_impl( a, typename detail::index_range<0, Sep>::type(),
                                            typename detail::index_range<Sep, N>::type() );
    }

} // namespace lindapp

#endif // __LINDAPP_MAKE_ARRAY_HPP__
