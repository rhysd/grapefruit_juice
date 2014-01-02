#if !defined GRAPEFRUIT_JUICE_OPTIONAL_HELPER_HPP_INCLUDED
#define      GRAPEFRUIT_JUICE_OPTIONAL_HELPER_HPP_INCLUDED

#include <boost/optional.hpp>

namespace gfj {
namespace optional {
namespace detail {

template<class T, class Func, class RetType = decltype(std::declval<Func>()(std::declval<T>()))>
struct fmap_impl{
    template<class Optional>
    static boost::optional<RetType> call(Optional const& o, Func const& f)
    {
        if(o) {
            return f(*o);
        } else {
            return boost::none;
        }
    }
};

template<class T, class Func>
struct fmap_impl<T, Func, void>{
    template<class Optional>
    static bool call(Optional const& o, Func const& f)
    {
        if(o) {
            f(*o);
            return true;
        } else {
            return false;
        }
    }
};

} // namespace detail

template<class T, class Func>
inline auto fmap(boost::optional<T> const& o, Func const& f)
    -> decltype(fmap_impl<T, Func>::call(o, f))
{
    return detail::fmap_impl<T, Func>::call(o, f);
}

} // namespace optional
} // namespace gfj

#endif    // GRAPEFRUIT_JUICE_OPTIONAL_HELPER_HPP_INCLUDED
