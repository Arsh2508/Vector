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
Vector<T>::Vector(size_type size, const_reference val) : Vector{}
{
    m_data = static_cast<T*>(operator new (sizeof(T) * size));

    size_type i = 0;
    try{
        for(; i < size; ++i) {
            new (m_data + i) T(val); 
        }
    }
    catch(...) {
        for(size_type j = 0; j < i; ++j) {
            m_data[j].~T();
        }
        operator delete(m_data);
        throw;
    }
    m_size = m_capacity = size;
}

template <typename T>
Vector<T>::Vector(const Vector& other) : Vector{}
{
    m_data = static_cast<T *>(operator new(sizeof(T) * other.capacity));

    size_type i = 0;
    try{
        for(; i < other.m_size; ++i) {
            new (m_data + i) T(other.m_data[i]);
        }
    }
    catch(...) {
        for(size_type j = 0; j < i; ++j) {
            m_data[j].~T();
        }
        operator delete(m_data);
        throw;
    }
    m_size = other.m_size;
    m_capacity = other.m_capacity;
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
Vector<T>::~Vector()
{
    clear();
    operator delete(m_data);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if(this != &rhs){
        Vector<T> tmp(rhs);
        swap(tmp);    
    }

    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&rhs) noexcept
{
    if(this != &rhs){
        Vector<T> tmp(std::move(rhs));
        swap(tmp);
    }

    return *this;
}

template <typename T>
void Vector<T>::assign(size_type count, const_reference val)
{
    T* new_data = static_cast<T*>(operator new(sizeof(T) * count));
    size_type i = 0;
    try{
        for(; i < count; ++i) {
            new (new_data + i) T(val);
        }
    }
    catch(...) {
        for(size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete(new_data);
        throw;
    }
    clear();
    operator delete(m_data);

    m_data = new_data;
    m_capacity = m_size = count;
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
typename Vector<T>::reference Vector<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const
{
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type index)
{
    if(index > m_size) throw std::out_of_range("");

    return m_data[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type index) const
{
    if(index > m_size) throw std::out_of_range("");

    return m_data[index];
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
bool Vector<T>::empty() const noexcept
{
    return m_size == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap)
{
    if(new_cap <= m_capacity) {
        return;
    }

    T* new_data = static_cast<T *>(operator new(sizeof(T) * new_cap));
    
    size_type i = 0;
    try{
        for(; i < m_size; ++i) {
            new (new_data + i) T(m_data[i]);
        }
    }
    catch(...) {
        for(size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete(new_data);
        throw;
    }
    size_type tmp_size = m_size;
    clear();
    operator delete(m_data);

    m_data = new_data;
    m_capacity = new_cap;
    m_size = tmp_size;
}

template <typename T>
void Vector<T>::clear()
{
    for(size_type i = 0; i < m_size; ++i) {
        m_data[i].~T();
    }
    m_size = 0;
}

template <typename T>
void Vector<T>::insert(size_type pos, const T &val)
{
    size_type new_capacity = (m_capacity == m_size) ? ((m_capacity == 0) ? 1 : m_capacity * 2) : m_capacity;

    T* new_data = static_cast<T *>(operator new(sizeof(T) * new_capacity));

    size_type i = 0;
    try{
        for(; i < pos; ++i){
            new (new_data + i) T(m_data[i]);
        }

        new (new_data + pos) T(val);

        for(i = pos; i < m_size; ++i) {
            new (new_data + i + 1) T(std::move(m_data[i]));
        }
    }

    catch(...) {
        for(size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete(new_data);
        throw;
    }
    
    size_type tmp_size = m_size;
    clear();
    operator delete(m_data);

    m_data = new_data;
    m_capacity = new_capacity;
    m_size = tmp_size + 1;
}
template <typename T>
void Vector<T>::insert(size_type pos, T &&val)
{
    if(m_capacity == m_size) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }

    for(size_type i = m_size; i >= pos; --i) {
        new (m_data + i) T(std::move(m_data[i - 1]));
    }

    new (m_data + pos) T(std::move(val));

    ++m_size;
}

template <typename T>
void Vector<T>::insert(size_type pos, size_type count, const T &val)
{
    size_type new_capacity = m_capacity;
    if(count + m_size > m_capacity) {
        new_capacity = std::max(m_capacity * 2, count + m_size);
    }

    T* new_data = static_cast<T *>(operator new(sizeof(T) * new_capacity));

    size_type i = 0;
    try {
        for(; i < pos; ++i) {
            new (&new_data[i]) T(m_data[i]);
        }

        for (size_type j = 0; j < count; ++j, ++i) {
            new (&new_data[i]) T(val);
        }

        for (size_type j = pos; j < m_size; ++j, ++i) {
            new (&new_data[i]) T(std::move(m_data[j]));
        }
    }
    catch (...) {
        for(size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete(new_data);
        throw;
    }
    size_type tmp_size = m_size;
    clear();
    operator delete(m_data);

    m_data = new_data;
    m_capacity = new_capacity;
    m_size = tmp_size + count;

}

template <typename T>
void Vector<T>::push_back(const_reference val)
{
    if(m_size == m_capacity) {
        reserve((m_capacity == 0) ? 1 : m_capacity * 2);
    }

    new (m_data + m_size) T(val);
    ++m_size;
}

template <typename T>
void Vector<T>::push_back(T &&val)
{
    if(m_size == m_capacity) {
        reserve((m_capacity == 0) ? 1 : m_capacity * 2);
    }

    new (m_data + m_size) T(std::move(val));
    ++m_size;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(m_size > 0) {
        m_data[m_size - 1].~T();
        --m_size;
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
