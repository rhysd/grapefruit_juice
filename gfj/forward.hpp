#ifndef __LINDAPP_FORWARD_HPP__
#define __LINDAPP_FORWARD_HPP__

// std::forward の2つめのシグネチャを delete したバージョン
// 間違ったキャストが起きないように．

namespace gfj{

    template <class T>
    constexpr T &&forward( typename remove_reference<T>::type &t) noexcept
    {
        return std::move(t);
    }

    template <class T>
    T &&forward( typename remove_reference<T>::type &&) = delete;
}

#endif // __LINDAPP_FORWARD_HPP__
