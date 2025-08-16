#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using size_type = std::size_t;

    Vector();
    explicit Vector(size_type size);
    Vector(size_type size, const_reference val);

    ~Vector();

    Vector(const Vector&);
    Vector& operator=(const Vector&);

    Vector(Vector&&);
    Vector& operator=(Vector&&);

    void assign(size_type count, const_reference val);
    
    void push_back(const_reference val);
    void pop_back();
    
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    void clear();

    void resize(size_type count);
    void resize(size_type count, const_reference val);

    void swap(Vector& other);

    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    void reserve(size_type new_cap);

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    reference at(size_type index);
    const_reference at(size_type index) const;

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
    size_type m_capacity;
    size_type m_size;
};

#include "Vector.cpp"
#endif