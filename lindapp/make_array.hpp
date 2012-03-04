#ifndef __LINDAPP_MAKE_ARRAY_HPP__
#define __LINDAPP_MAKE_ARRAY_HPP__

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

    template <class T, size_t N, class Result = std::array<T, N>>
    Result to_array( T const(& native_array)[N] )
    {
        Result ret;
        for(size_t i = 0; i < N; ++i){
            ret[i] = native_array[i];
        }
        return std::move( ret );
    }
}

#endif // __LINDAPP_MAKE_ARRAY_HPP__
