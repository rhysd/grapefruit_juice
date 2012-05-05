#ifndef LINDAPP_TYPE_TRAITS_ALIASES_HPP_INCLUDED__
#define LINDAPP_TYPE_TRAITS_ALIASES_HPP_INCLUDED__

#include <type_traits>

namespace gfj{
    template <class T>
    using remove_cv = typename std::remove_cv<T>::type;

    template <class T>
    using remove_const = typename std::remove_const<T>::type;

    template <class T>
    using remove_volatile = typename std::remove_volatile<T>::type;

    template <class T>
    using add_cv = typename std::add_cv<T>::type;

    template <class T>
    using add_const = typename std::add_const<T>::type;

    template <class T>
    using add_volatile = typename std::add_volatile<T>::type;

    template <class T>
    using remove_reference = typename std::remove_reference<T>::type;

    template <class T>
    using add_pointer = typename std::add_pointer<T>::type;

    template <class T>
    using make_signed = typename std::make_signed<T>::type;

    template <class T>
    using make_unsigned = typename std::make_unsigned<T>::type;

    template <class T>
    using remove_extent = typename std::remove_extent<T>::type;

    template <class T>
    using remove_all_extents = typename std::remove_all_extents<T>::type;

    template <std::size_t Len, std::size_t Align>
    using aligned_storage = typename std::aligned_storage<Len, Align>::type;

    template<class T>
    using decay = typename std::decay<T>::type;

    template<bool B, class T = void>
    using enable_if = typename std::enable_if<B, T>::type;

    template<bool B, class T, class U>
    using conditional = typename std::conditional<B, T, U>::type;

    template <class... T>
    using common_type = typename std::common_type<T...>::type;

    template <class T>
    using underlying_type = typename std::underlying_type<T>::type;

    template <class F, class... Args >
    using result_of = typename std::result_of<F(Args...)>::type;
}

#endif // LINDAPP_TYPE_TRAITS_ALIASES_HPP_INCLUDED__
