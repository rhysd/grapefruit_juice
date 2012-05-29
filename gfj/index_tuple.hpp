#ifndef LINDAPP_INDEX_TUPLE_HPP__
#define LINDAPP_INDEX_TUPLE_HPP__

#include <cstddef>

namespace gfj{

    template< std::size_t... Indices >
    struct index_tuple{};

    template < std::size_t Start,
               std::size_t Last,
               std::size_t Step = 1,
               class Acc = index_tuple<>,
               bool Finish = (Start>=Last) >
    struct index_range{
        typedef Acc type;
    };

    template < std::size_t Start,
               std::size_t Last,
               std::size_t Step,
               std::size_t... Indices >
    struct index_range< Start, Last, Step, index_tuple<Indices...>, false >
             : index_range<Start+Step, Last, Step, index_tuple<Indices..., Start>>
    {};

    template < std::size_t Start, std::size_t Last, std::size_t Step = 1 >
    using idx_range = typename index_range< Start, Last, Step >::type;

}

#endif // LINDAPP_INDEX_TUPLE_HPP__
