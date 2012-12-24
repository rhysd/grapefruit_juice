#if !defined LINDAPP_TRAITS_UTIL_HPP_INCLUDED
#define LINDAPP_TRAITS_UTIL_HPP_INCLUDED

#include <type_traits>

namespace gfj{

    template <class T>
    using eval = typename T::type;

    template <class T>
    using remove_cvr = typename std::remove_cv< typename std::remove_reference< T >::type >::type;

    template <class Container>
    using value_t = typename Container::value_type;

    template <class Container>
    using length_t = typename Container::size_type;

    template <class Container>
    using diff_t = typename Container::difference_type;

    template <class Container>
    using ref_t = typename Container::reference;

    template <class Container>
    using const_ref_t = typename Container::const_reference;

    template <class Container>
    using ptr_t = typename Container::pointer;

    template <class Container>
    using const_ptr_t = typename Container::const_pointer;

    template <class Container>
    using iter_t = typename Container::iterator;

    template <class Container>
    using const_iter_t = typename Container::const_iterator;

    template <class Container>
    using reverse_iter_t = typename Container::reverse_iterator;

    template <class Container>
    using const_reverse_iter_t = typename Container::const_reverse_iterator;

    template <class Container>
    using alloc_t = typename Container::allocator_type;

    template <class Set>
    using key_t = typename Set::key_type;

    template <class Map>
    using mapped_t = typename Map::mapped_type;

    template <class Pair>
    using first_t = typename Pair::first_type;

    template <class Pair>
    using second_t = typename Pair::second_type;

    template <class Function>
    using result_t = typename Function::result_type;

    template <class Function>
    using arg_t = typename Function::argument_type;

    template <class Function>
    using arg1_t = typename Function::first_argument_type;

    template <class Function>
    using arg2_t = typename Function::second_argument_type;

    template <class Function>
    using target_t = typename Function::target_type;

    template <class T, class... Rest>
    struct first_of_{
        typedef T type;
    };

    template < class... Types >
    using first_of = typename first_of_<Types...>::type;
}

#endif // LINDAPP_TRAITS_UTIL_HPP_INCLUDED
