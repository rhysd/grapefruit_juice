#ifndef LINDAPP_UTILITY_HPP
#define LINDAPP_UTILITY_HPP

#include <cstddef>
#include <type_traits>
#include <algorithm>

namespace gfj{

template< class Func, class... Args >
void times(std::size_t const n, Func const& func, Args &&... args)
{
    for(std::size_t i=0; i<n; ++i){
        func( std::forward<Args>(args)...);
    }
}

template< class T >
constexpr T max_many( T const& a, T const& b)
{
    return a>b ? a : b;
}

template< class T, class... Rest >
constexpr T max_many( T const& head, Rest... rest )
{
    return std::max( head, max_many( rest... ) );
}

template< class T >
constexpr T min_many( T const& a, T const& b)
{
    return a<b ? a : b;
}

template< class T, class... Rest >
constexpr T min_many( T const& head, Rest... rest)
{
    return std::min( head, min_many( rest... ) );
}

namespace impl{
    template< class T >
    constexpr T between_impl( T && value, T && floor, T && ceiling )
    {
        return std::max( std::min( std::forward<T>(value), std::forward<T>(ceiling) ), std::forward<T>(floor) );
    }
}

template< class T, class U, class V,
          class R = typename std::decay< typename std::common_type< T, U, V >::type >::type
        >
constexpr R between( T && value, U && floor, V && ceiling )
{
    return impl::between_impl( std::forward<R>( static_cast<R>(value) ),
                               std::forward<R>( static_cast<R>(floor) ),
                               std::forward<R>( static_cast<R>(ceiling) )
                             );
}

template< class Result = std::vector<std::string> >
Result args(int const argc, char const * const * const argv)
{
    Result result;
    for(int i=0; i<argc; ++i){
        result.push_back(argv[i]);
    }
    return result;
}

#define GFRUIT_RETURN(...) -> decltype(__VA_ARGS__) { return (__VA_ARGS__); }
#define static_assert_(expr) static_assert(expr, #expr)

tempalte <class T>
class in{
    T const& v_;
    bool const rv_;
public:
    in(T const& l) : v_(l), rv_(false){}
    in(T&& r) : v_(r), rv_(true){}

    bool lvalue() const { return !rv_; }
    bool rvalue() const { return rv_; }

    operator T const&() const { return v_; }
    T const& get() const { return v_; }
    T&& rget() const { return std::move(const_cast<T&>(v_)); }

    T move() const
    {
        return rv_ ? rget() : v_;
    }
};

}
#endif // LINDAPP_UTILITY_HPP
