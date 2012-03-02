#ifndef __LINDAPP_FORWARD_HPP__
#define __LINDAPP_FORWARD_HPP__

namespace lindapp{

    template <class T>
    constexpr T &&forward( typename remove_reference<T>::type &t) noexcept
    {
        return std::move(t);
    }

    template <class T>
    T &&forward( typename remove_reference<T>::type &&) = delete;
}

#endif // __LINDAPP_FORWARD_HPP__
