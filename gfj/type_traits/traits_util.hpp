#if !defined LINDAPP_TRAITS_UTIL_HPP_INCLUDED__
#define LINDAPP_TRAITS_UTIL_HPP_INCLUDED__

namespace gfj{

    template <class T>
    using eval = typename T::type;

    template <class T>
    using remove_cvr = typename std::remove_cv< typename std::remove_reference< T >::type >::type;

}

#endif // LINDAPP_TRAITS_UTIL_HPP_INCLUDED__
