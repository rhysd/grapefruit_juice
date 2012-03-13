#ifndef LINDA_PP_CONSTEXPR_ARRAY_HPP__
#define LINDA_PP_CONSTEXPR_ARRAY_HPP__

// #include <bits/stl_algobase.h>
// #include <bits/range_access.h>
#include <algorithm>

namespace lindapp{

    template<typename T, std::size_t N>
        struct array
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
            typedef std::reverse_iterator<iterator>       reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

            value_type m_instance[N ? N : 1];

            // No explicit construct/copy/destroy for aggregate type.

            void fill(const value_type& u)
            { std::fill_n(begin(), size(), u); }

            void swap(array& other)
            { std::swap_ranges(begin(), end(), other.begin()); }


            // Iterators.
            iterator begin()
            { return iterator(std::addressof(m_instance[0])); }

            const_iterator begin() const
            { return const_iterator(std::addressof(m_instance[0])); }

            iterator end()
            { return iterator(std::addressof(m_instance[N])); }

            const_iterator end() const
            { return const_iterator(std::addressof(m_instance[N])); }

            reverse_iterator rbegin()
            { return reverse_iterator(end()); }

            const_reverse_iterator rbegin() const
            { return const_reverse_iterator(end()); }

            reverse_iterator rend()
            { return reverse_iterator(begin()); }

            const_reverse_iterator rend() const
            { return const_reverse_iterator(begin()); }

            const_iterator cbegin() const 
            { return const_iterator(m_instance); }

            const_iterator cend() const
            { return const_iterator(std::addressof(m_instance[N])); }

            const_reverse_iterator crbegin() const
            { return const_reverse_iterator(end()); }

            const_reverse_iterator crend() const
            { return const_reverse_iterator(begin()); }

            // Capacity.
            constexpr size_type size() const { return N; }

            constexpr size_type max_size() const { return N; }

            constexpr bool empty() const { return size() == 0; }

            // Element access.
            reference operator[](size_type n)
            { return m_instance[n]; }

            constexpr const_reference operator[](size_type n) const
            { 
                return m_instance[n]; 
            }

            reference at(size_type n)
            {
                if (n >= N)
                    std::__throw_out_of_range(__N("array::at"));
                return m_instance[n];
            }

            const_reference at(size_type n) const
            {
                if (n >= N)
                    std::__throw_out_of_range(__N("array::at"));
                return m_instance[n];
            }

            reference front()
            { return m_instance[0]; }

            const_reference front() const
            { return m_instance[0]; }

            reference back()
            { return N ? m_instance[N-1] : m_instance[N]; }

            constexpr const_reference back() const
            { return N ? m_instance[N-1] : m_instance[N]; }

            T* data()
            { return std::addressof(m_instance[0]); }

            constexpr const T* data() const
            { return std::addressof(m_instance[0]); }
        };

    // Array comparisons.
    template<typename T, std::size_t N>
    inline bool operator==(const array<T, N>& one, const array<T, N>& two)
    { return std::equal(one.begin(), one.end(), two.begin()); }

    template<typename T, std::size_t N>
    inline bool operator!=(const array<T, N>& one, const array<T, N>& two)
    { return !(one == two); }

    template<typename T, std::size_t N>
    inline bool operator<(const array<T, N>& a, const array<T, N>& b)
    { 
        return std::lexicographical_compare(a.begin(), a.end(),
                b.begin(), b.end()); 
    }

    template<typename T, std::size_t N>
    inline bool operator>(const array<T, N>& one, const array<T, N>& two)
    { return two < one; }

    template<typename T, std::size_t N>
    inline bool operator<=(const array<T, N>& one, const array<T, N>& two)
    { return !(one > two); }

    template<typename T, std::size_t N>
    inline bool operator>=(const array<T, N>& one, const array<T, N>& two)
    { return !(one < two); }

    // Specialized algorithms [6.2.2.2].
    template<typename T, std::size_t N>
    inline void swap(array<T, N>& one, array<T, N>& two)
    { one.swap(two); }

    // Tuple interface to class template array [6.2.2.5].

    /// tuple_size
    template<typename T> 
    class tuple_size;

    /// tuple_element
    template<std::size_t Int, typename T>
    class tuple_element;

    template<typename T, std::size_t N>
    struct tuple_size<array<T, N> >
    { static const std::size_t value = N; };

    template<typename T, std::size_t N>
    const std::size_t tuple_size<array<T, N> >::value;  

    template<std::size_t Int, typename T, std::size_t N>
    struct tuple_element<Int, array<T, N> >
    { typedef T type; };

    template<std::size_t Int, typename T, std::size_t N>
    inline T& get(array<T, N>& arr)
    { return arr[Int]; }

    template<std::size_t Int, typename T, std::size_t N>
    inline constexpr T const& get(const array<T, N>& arr)
    { return arr[Int]; }

}

#endif // LINDA_PP_CONSTEXPR_ARRAY_HPP__
