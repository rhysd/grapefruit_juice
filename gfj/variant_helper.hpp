#if !defined GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED
#define      GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/optional.hpp>

#include <utility>

namespace gfj {
namespace variant {

namespace detail {

    template<class T>
    struct static_getter : public boost::static_visitor<boost::optional<T>> {
        typedef boost::optional<T> return_type;

        return_type operator()(T const& val) const
        {
            return val;
        }

        template<class U>
        return_type operator()(U const&) const
        {
            return boost::none;
        }
    };

} // namespace detail

template<class T, class Variant>
inline boost::optional<T> get(Variant const& v)
{
    return boost::apply_visitor(detail::static_getter<T>{}, v);
}

namespace detail {

    template<class T, class Func, class RetType = decltype(std::declval<Func>()(std::declval<T>()))>
    struct apply_impl{
        template<class Variant>
        static boost::optional<RetType> call(Variant const& v, Func const& f)
        {
            if(auto opt = get<T>(v)) {
                return f(*opt);
            } else {
                return boost::none;
            }
        }
    };

    template<class T, class Func>
    struct apply_impl<T, Func, void>{
        template<class Variant>
        static bool call(Variant const& v, Func const& f)
        {
            if(auto opt = get<T>(v)) {
                f(*opt);
                return true;
            } else {
                return false;
            }
        }
    };

} // namespace detail

template<class T, class Func, class Variant>
inline auto apply(Variant const& v, Func const& f)
    -> decltype(apply_impl<T, Func>::call(v, f))
{
    return apply_impl<T, Func>::call(v, f);
}

} // namespace variant
} // namespace gfj

#endif    // GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED
