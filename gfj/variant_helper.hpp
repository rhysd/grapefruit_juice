#if !defined GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED
#define      GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED

#include <boost/variant/variant.hpp>
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

template<class T, class... Args>
inline boost::optional<T> get(boost::variant<Args...> const& v)
{
    return boost::apply_visitor(detail::static_getter<T>{}, v);
}

namespace detail {

    template<class T, class Func, class RetType = decltype(std::declval<Func>()(std::declval<T>()))>
    struct apply_impl{
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
    struct apply_impl<T, Func, void>{
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

template<class T, class Func, class Variant>
inline auto apply(Variant const& v, Func const& f)
    -> decltype(detail::apply_impl<T, Func>::call(std::declval<boost::optional<T>>(), f))
{
    return detail::apply_impl<T, Func>::call(get<T>(v), f);
}

namespace detail {

    template<class T>
    struct type_checker : boost::static_visitor<bool> {
        bool operator()(T) const
        {
            return true;
        }

        template<class U>
        bool operator()(U) const
        {
            return false;
        }
    };

} // namespace detail

template<class T, class... Args>
inline bool has_value_of(boost::variant<Args...> const& v)
{
    return boost::apply_visitor(detail::type_checker<T>{}, v);
}

} // namespace variant
} // namespace gfj

#endif    // GRAPEFRUIT_JUICE_VARIANT_HELPER_HPP_INCLUDED
