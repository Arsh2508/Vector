#include <iostream>
#include <ostream>
#include <exception>
#include "Vector.hpp"

template <typename T>
Vector<T>::Vector() 
    : m_data{nullptr}
    , m_size{0}
    , m_capacity{0}
{}

template <typename T>
Vector<T>::Vector(size_type size)
    : m_data{new T[size * 2]}
    , m_size{size}
    , m_capacity{size * 2}
{}

template <typename T>
Vector<T>::Vector(size_type size, const_reference val)
    : m_data{new T[size * 2]}
    , m_size{size}
    , m_capacity{size * 2}
{
    for(size_type i = 0; i < m_size; ++i) 
    {
        m_data[i] = val;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    delete []m_data;
}


template <typename T>
Vector<T>::Vector(const Vector& other)
    : m_data{new T[other.m_capacity]}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity}
{
    for(int i = 0; i < m_size; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}


template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if(this == &rhs){
        return *this;
    }

    delete []m_data;

    m_data = new T[rhs.m_capacity];
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;

    for(size_type i = 0; i < m_size; ++i) 
    {
        m_data[i] = rhs.m_data[i];
    }

    return *this;
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept
    : m_data{other.m_data}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity}
{
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&rhs) noexcept
{
    if(this == &rhs){
        return *this;
    }

    delete []m_data;

    m_data = rhs.m_data;
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;

    rhs.m_data = nullptr;
    rhs.m_size = 0;
    rhs.m_capacity = 0;

    return *this;
}

template <typename T>
void Vector<T>::assign(size_type count, const_reference val)
{
    resize(count);
    for(size_type i = 0; i < m_size; ++i) {
        m_data[i] = val;
    }
}

template <typename T>
void Vector<T>::push_back(const_reference val)
{
    if(m_size >= m_capacity)
    {
        size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* new_data = new T[new_capacity];

        for(size_type i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }

        delete []m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }

    m_data[m_size++] = val;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(m_size > 0) {
        --m_size;
    }
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type index)
{
    return m_data[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const
{
    return m_data[index];
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
}

template <typename T>
void Vector<T>::resize(size_type count)
{
    if(count == m_size) {
        return;
    }

    if(count < m_size) {
        m_size = count;
        return;
    }

    if(count > m_capacity) {
        size_type new_capacity = (count > m_capacity * 2) ? count : m_capacity * 2;
        T* new_data = new T[new_capacity];

        for(size_type i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }

        for(size_type i = m_size; i < count; ++i) {
            new_data[i] = T();
        }

        delete []m_data;
        m_data = new_data;
        m_size = count;
        m_capacity = new_capacity;
    }
    else {
        for(size_type i = m_size; i < count; ++i) {
            m_data[i] = T();
        }
        m_size = count;
    }
}

template <typename T>
void Vector<T>::resize(size_type count, const_reference val)
{
    if(count == m_size) {
        return;
    }
 
    if(count < m_size) {
        m_size = count;
        return;
    }

    if(count > m_capacity) {
        size_type new_capacity = (count > m_capacity * 2) ? count : m_capacity * 2;
        T* new_data = new T[new_capacity];

        for(size_type i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }

        for(size_type i = m_size; i < count; ++i) {
            new_data[i] = val;
        }

        delete []m_data;
        m_data = new_data;
        m_size = count;
        m_capacity = new_capacity;
    }
    else {
        for(size_type i = m_size; i < count; ++i) {
            m_data[i] = val;
        }
        m_size = count;
    }
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept
{
    T* tmp = other.m_data;
    other.m_data = m_data;
    m_data = tmp;

    size_type tmp_size = m_size;
    m_size = other.m_size;
    other.m_size = tmp_size;

    size_type tmp_capacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tmp_capacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const
{
    return m_size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap)
{
    if(new_cap <= m_capacity) {
        return;
    }

    T* new_data = new T[new_cap];
    
    for(size_type i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }

    delete []m_data;
    m_data = new_data;
    m_capacity = new_cap;
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() 
{
    return m_data[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const
{
    return m_data[0];
}

template <typename T>
T &Vector<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const
{
    return m_data[m_size - 1];
}

template <typename T>
T &Vector<T>::at(size_type index)
{
    return m_data[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type index) const
{
    return m_data[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
{
    for(typename Vector<T>::size_type i = 0; i < vec.m_size; ++i) 
    {
        os << vec[i] << " ";
    }

    return os;
}

template <typename U>
bool operator==(const Vector<U> &lhs, const Vector<U> &rhs)
{
    if(lhs.size() != rhs.size()) {
        return false;
    }

    for(typename Vector<U>::size_type i = 0; i < lhs.size(); ++i) {
        if(lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
    
}

template <typename U>
bool operator!=(const Vector<U> &lhs, const Vector<U> &rhs)
{
    return !(lhs == rhs);
}

template <typename U>
void swap(Vector<U> &lhs, Vector<U> &rhs)
{
    lhs.swap(rhs);
}
