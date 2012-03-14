#ifndef LINDAPP_INDEX_TUPLE_HPP__
#define LINDAPP_INDEX_TUPLE_HPP__

#include <cstddef>

namespace lindapp{

    template< std::size_t... Indices >
    struct index_tuple{};

    template < std::size_t Start,
               std::size_t Last,
               class Acc = index_tuple<>,
               bool Finish = (Start>=Last) >
    struct index_range{
        typedef Acc type;
    };

    template < std::size_t Start,
               std::size_t Last,
               std::size_t... Indices >
    struct index_range< Start, Last, index_tuple<Indices...>, false >
             : index_range<Start+1, Last, index_tuple<Indices..., Start>>
    {};
}

#endif // LINDAPP_INDEX_TUPLE_HPP__
