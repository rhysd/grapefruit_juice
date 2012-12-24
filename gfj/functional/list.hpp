#ifndef LINDA_PP_CONSTEXPR_ARRAY_HPP
#define LINDA_PP_CONSTEXPR_ARRAY_HPP

// #include <bits/stl_algobase.h>
// #include <bits/range_access.h>
#include <algorithm>

namespace gfj{

    template<typename T, std::size_t N>
        struct list
        {
            typedef T                                     value_type;
            typedef T*                                    pointer;
            typedef const T*                              const_pointer;
            typedef value_type&                           reference;
            typedef const value_type&                     const_reference;
            typedef value_type*                           iterator;
            typedef const value_type*                     const_iterator;
            typedef std::size_t                           size_type;
            typedef std::ptrdiff_t                        difference_type;

            value_type m_instance[N ? N : 1];

            // No explicit construct/copy/destroy for aggregate type.

            // Iterators.
            constexpr const_iterator begin() const
            { return const_iterator(std::addressof(m_instance[0])); }

            constexpr const_iterator end() const
            { return const_iterator(std::addressof(m_instance[N])); }

            constexpr const_iterator cbegin() const 
            { return const_iterator(m_instance); }

            constexpr const_iterator cend() const
            { return const_iterator(std::addressof(m_instance[N])); }

            // Capacity.
            constexpr size_type size() const { return N; }

            constexpr size_type max_size() const { return N; }

            constexpr bool empty() const { return size() == 0; }

            // Element access.
            constexpr const_reference operator[](size_type n) const
            { 
                return m_instance[n]; 
            }

            constexpr const_reference front() const
            { return m_instance[0]; }

            constexpr const_reference back() const
            { return N ? m_instance[N-1] : m_instance[N]; }

            constexpr T* data()
            { return std::addressof(m_instance[0]); }

        };

    // Array comparisons.
    // template<typename T, std::size_t N>
    // inline bool operator==(const list<T, N>& one, const list<T, N>& two)
    // { return std::equal(one.begin(), one.end(), two.begin()); }

    // template<typename T, std::size_t N>
    // inline bool operator!=(const array<T, N>& one, const array<T, N>& two)
    // { return !(one == two); }

    // template<typename T, std::size_t N>
    // inline bool operator<(const array<T, N>& a, const array<T, N>& b)
    // { 
    //     return std::lexicographical_compare(a.begin(), a.end(),
    //             b.begin(), b.end()); 
    // }

    // template<typename T, std::size_t N>
    // inline bool operator>(const array<T, N>& one, const array<T, N>& two)
    // { return two < one; }

    // template<typename T, std::size_t N>
    // inline bool operator<=(const array<T, N>& one, const array<T, N>& two)
    // { return !(one > two); }

    // template<typename T, std::size_t N>
    // inline bool operator>=(const array<T, N>& one, const array<T, N>& two)
    // { return !(one < two); }

    // Tuple interface to class template array [6.2.2.5].

    /// tuple_size
    template<typename T> 
    class tuple_size;

    /// tuple_element
    template<std::size_t Int, typename T>
    class tuple_element;

    template<typename T, std::size_t N>
    struct tuple_size<list<T, N> >
    { static const std::size_t value = N; };

    template<typename T, std::size_t N>
    const std::size_t tuple_size<list<T, N> >::value;  

    template<std::size_t Int, typename T, std::size_t N>
    struct tuple_element<Int, list<T, N> >
    { typedef T type; };

    template<std::size_t Int, typename T, std::size_t N>
    inline T& get(list<T, N>& arr)
    { return arr[Int]; }

    template<std::size_t Int, typename T, std::size_t N>
    inline constexpr T const& get(const list<T, N>& arr)
    { return arr[Int]; }

}

#endif // LINDA_PP_CONSTEXPR_ARRAY_HPP
