#if !defined LINDAPP_OPERATION_HPP_INCLUDED__
#define LINDAPP_OPERATION_HPP_INCLUDED__

#include <functional>
#include <algorithm>

namespace gfj{

template< class Iterator,
class Comp = std::less<typename Iterator::value_type>,
class Pred = std::equal_to<typename Iterator::value_type>
>
inline Iterator unique( Iterator first,
       Iterator last,
       Comp comp=std::less<typename Iterator::value_type>(),
       Pred pred=std::equal_to<typename Iterator::value_type>()
     )
{
std::sort(first, last, comp);
return std::unique(first, last, pred);
}

template< class Func, class OutputIter, class InputIter, class... InputIters >
OutputIter zip_with( Func const& func, OutputIter result, InputIter from_begin, InputIter from_end, InputIters... rest_iters)
{
    for( auto from = from_begin;
         from!=from_end;
         ++from ){
        typename OutputIter::value_type ret = *from;
        for( auto &iter_ptr : {(&rest_iters)...} ){
            ret = func( ret, *(*iter_ptr)++ );
        }
        *result = ret;
        ++result;
    }
    return result;
}

template< class Func, class OutputIter, class InputIter, class... InputIters >
OutputIter zip_with2( InputIter from_begin, InputIter from_end, OutputIter d_first, Func const& func, InputIters... rest_iters )
{
    for( auto from = from_begin;
         from!=from_end;
         ++from ){
        *d_first++ = func( *from, (*rest_iters++)... );
    }
    return d_first;
}

}
#endif // LINDAPP_OPERATION_HPP_INCLUDED__
