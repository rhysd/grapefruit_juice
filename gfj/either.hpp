#if !defined EITHER_HPP_INCLUDED
#define EITHER_HPP_INCLUDED

#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/optional.hpp>

namespace gfj {

template<class L, class R>
using either = boost::variant<L, R>;

template<class L, class R>
boost::optional<L> left(either<L, R> e)
{
    if(e.which()==0){
        return boost::get<L>(e);
    }else{
        return boost::none;
    }
}

template<class L, class R>
boost::optional<R> right(either<L, R> e)
{
    if(e.which()==1){
        return boost::get<R>(e);
    }else{
        return boost::none;
    }
}

} // namespace gfj
#endif // EITHER_HPP_INCLUDED
