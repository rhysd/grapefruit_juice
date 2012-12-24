#ifndef LINDAPP_FORWARD_HPP
#define LINDAPP_FORWARD_HPP

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

#endif // LINDAPP_FORWARD_HPP
