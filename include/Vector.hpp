#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iterator>

template <typename T>
class Vector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = std::size_t;

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    iterator begin() noexcept { return iterator(m_data); }
    iterator end() noexcept { return iterator(m_data + m_size); }

    const_iterator begin() const noexcept { return const_iterator(m_data); }
    const_iterator end() const noexcept { return const_iterator(m_data + m_size); }

    const_iterator cbegin() const noexcept { return const_iterator(m_data); }
    const_iterator cend() const noexcept { return const_iterator(m_data + m_size); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
    

    Vector();
    explicit Vector(size_type size, const_reference val = T());
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    ~Vector();

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;

    void assign(size_type count, const_reference val);
    
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    reference at(size_type index);
    const_reference at(size_type index) const;
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);

    void clear();
    void insert(size_type pos, const T& val);
    void insert(size_type pos, T&& val);
    void insert(size_type pos, size_type count, const T& val);
    template <typename... Args>
    void emplace(size_type pos, Args &&...arg);
    void erase(size_type pos);
    void erase(size_type first, size_type last);
    void push_back(const_reference val);
    void push_back(T&& val);
    template <typename... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    void resize(size_type count, const_reference val = T());
    void swap(Vector& other) noexcept;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

    template <typename U>
    friend bool operator==(const Vector<U>& lhs, const Vector<U>& rhs);

    template <typename U>
    friend bool operator!=(const Vector<U>& lhs, const Vector<U>& rhs);

    template <typename U>
    friend void swap(Vector<U>& lhs, Vector<U>& rhs);

    class iterator{
    public:
        using value_type = Vector::value_type;
        using pointer = Vector::pointer;
        using reference = Vector::reference;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        iterator(pointer ptr = nullptr) : m_ptr{ptr} {}

        reference operator*() const {return *m_ptr;}
        pointer operator->() const {return m_ptr;}

        iterator& operator++() {
            ++m_ptr;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(m_ptr);
            ++m_ptr;
            return tmp;
        }
        iterator& operator--() {
            --m_ptr;
            return *this;
        }
        iterator operator--(int) {
            iterator tmp(m_ptr);
            --m_ptr;
            return tmp;
        }

        iterator operator+(difference_type n) const {
            return iterator(m_ptr + n);
        }
        iterator operator-(difference_type n) const {
            return iterator(m_ptr - n);
        }
        difference_type operator-(const iterator& other) const {
            return m_ptr - other.m_ptr;
        }

        iterator& operator+=(difference_type n) {
            m_ptr += n;
            return *this;
        }
        iterator& operator-=(difference_type n) {
            m_ptr -= n;
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const iterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator<(const iterator& rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator>(const iterator& rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator>=(const iterator& rhs) const {
            return m_ptr >= rhs.m_ptr;
        }
        bool operator<=(const iterator& rhs) const {
            return m_ptr <= rhs.m_ptr;  
        }

        reference operator[](size_type index) const {
            return *(m_ptr + index); 
        }

    private:
        pointer m_ptr;
    };
    
    class const_iterator{
    public: 
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator(pointer ptr = nullptr) : m_ptr{ptr} {}
        const_iterator(const iterator& it) : m_ptr{it.m_ptr} {}

        reference operator*() const {return *m_ptr;}
        pointer operator->() const {return m_ptr;}

        const_iterator& operator++() {
            ++m_ptr;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(m_ptr);
            ++m_ptr;
            return tmp;
        }
        const_iterator& operator--() {
            --m_ptr;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator tmp(m_ptr);
            --m_ptr;
            return tmp;
        }

        const_iterator operator+(difference_type n) const {
            return const_iterator(m_ptr + n);
        }
        const_iterator operator-(difference_type n) const {
            return const_iterator(m_ptr - n);
        }
        difference_type operator-(const const_iterator& other) const {
            return m_ptr - other.m_ptr;
        }

        const_iterator& operator+=(difference_type n) {
            m_ptr += n;
            return *this;
        }
        const_iterator& operator-=(difference_type n) {
            m_ptr -= n;
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const const_iterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator<(const const_iterator& rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator>(const const_iterator& rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator>=(const const_iterator& rhs) const {
            return m_ptr >= rhs.m_ptr;
        }
        bool operator<=(const const_iterator& rhs) const {
            return m_ptr <= rhs.m_ptr;  
        }

        reference operator[](size_type index) const {
            return *(m_ptr + index); 
        }

    private:
        pointer m_ptr;
    };

    class reverse_iterator{
    public:
        using iterator_type     = const_iterator;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        reverse_iterator() : m_it{nullptr} {}
        explicit reverse_iterator(iterator_type it) : m_it{it} {}

        iterator_type base() const {return m_it;}

        reference operator*() const {
            iterator_type tmp = m_it;
            --tmp;
            return *tmp;
        }
        
        pointer operator->() const {
            iterator_type tmp = m_it;
            --tmp;
            return &(*tmp);
        }

        reverse_iterator& operator++() {
            --m_it;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            --m_it;
            return tmp;
        }
    
        reverse_iterator& operator--() {
            ++m_it;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp(*this);
            ++m_it;
            return tmp;
        }
        
        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(m_it - n);
        }
        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(m_it + n);
        }
        difference_type operator-(const reverse_iterator& other) const {
            return other.m_it - m_it;
        }

        reverse_iterator& operator+=(difference_type n) {
            m_it -= n;
            return *this;
        }

        reverse_iterator& operator-=(difference_type n) {
            m_it += n;
            return *this;
        }

        reference operator[](difference_type index) {
            return *(*this + index);
        }
        
        bool operator==(const reverse_iterator& rhs) const {
            return m_it == rhs.m_it;
        }
        bool operator!=(const reverse_iterator& rhs) const {
            return m_it != rhs.m_it;
        }
        bool operator<(const reverse_iterator& rhs) const {
            return m_it > rhs.m_it;
        }
        bool operator>(const reverse_iterator& rhs) const {
            return m_it < rhs.m_it;
        }
        bool operator>=(const reverse_iterator& rhs) const {
            return m_it <= rhs.m_it;
        }
        bool operator<=(const reverse_iterator& rhs) const {
            return m_it >= rhs.m_it;  
        }

    private:
        iterator_type m_it;
    };

    class const_reverse_iterator{
    public:
        using iterator_type     = const_iterator;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        const_reverse_iterator() : m_it{nullptr} {}
        explicit const_reverse_iterator(iterator_type it) : m_it{it} {}
        const_reverse_iterator(const reverse_iterator& other) : m_it{other.base()} {}

        iterator_type base() const {return m_it;}

        reference operator*() const {
            iterator_type tmp = m_it;
            --tmp;
            return *tmp;
        }
        
        pointer operator->() const {
            iterator_type tmp = m_it;
            --tmp;
            return &(*tmp);
        }

        const_reverse_iterator& operator++() {
            --m_it;
            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator tmp(*this);
            --m_it;
            return tmp;
        }
    
        const_reverse_iterator& operator--() {
            ++m_it;
            return *this;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator tmp(*this);
            ++m_it;
            return tmp;
        }
        
        const_reverse_iterator operator+(difference_type n) const {
            return const_reverse_iterator(m_it - n);
        }
        const_reverse_iterator operator-(difference_type n) const {
            return const_reverse_iterator(m_it + n);
        }
        difference_type operator-(const const_reverse_iterator& other) const {
            return other.m_it - m_it;
        }

        const_reverse_iterator& operator+=(difference_type n) {
            m_it -= n;
            return *this;
        }

        const_reverse_iterator& operator-=(difference_type n) {
            m_it += n;
            return *this;
        }

        reference operator[](difference_type index) {
            return *(*this + index);
        }
        
        bool operator==(const const_reverse_iterator& rhs) const {
            return m_it == rhs.m_it;
        }
        bool operator!=(const const_reverse_iterator& rhs) const {
            return m_it != rhs.m_it;
        }
        bool operator<(const const_reverse_iterator& rhs) const {
            return m_it > rhs.m_it;
        }
        bool operator>(const const_reverse_iterator& rhs) const {
            return m_it < rhs.m_it;
        }
        bool operator>=(const const_reverse_iterator& rhs) const {
            return m_it <= rhs.m_it;
        }
        bool operator<=(const const_reverse_iterator& rhs) const {
            return m_it >= rhs.m_it;  
        }

    private:
        iterator_type m_it;
    };

private:
    pointer m_data;
    size_type m_size;
    size_type m_capacity;
};

#include "../src/Vector.tpp"
#endif
