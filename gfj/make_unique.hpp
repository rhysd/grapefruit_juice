#ifndef __LINDA_PP_MAKE_UNIQUE_HPP__
#define __LINDA_PP_MAKE_UNIQUE_HPP__

// std::unique_ptr を生成

#include <memory>

namespace gfj{

    template<class T>
    inline std::unique_ptr<T> make_unique()
    {
        return std::unique_ptr<T>( new T() );
    }

    template<class T, class... Args>
    inline std::unique_ptr<T> make_unique( Args &&... args )
    {
        return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }

}
#endif // __LINDA_PP_MAKE_UNIQUE_HPP__