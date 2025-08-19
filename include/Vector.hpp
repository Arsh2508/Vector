#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = std::size_t;

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
    friend bool operator==(const Vector& lhs, const Vector& rhs);

    template <typename U>
    friend bool operator!=(const Vector& lhs, const Vector& rhs);

    template <typename U>
    friend void swap(Vector& lhs, Vector& rhs);

private:
    pointer m_data;
    size_type m_size;
    size_type m_capacity;
};

#include "../src/Vector.tpp"
#endif