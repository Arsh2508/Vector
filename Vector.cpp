#include <iostream>
#include <ostream>
#include "Vector.hpp"

template <typename T>
Vector<T>::Vector() 
    : m_data{nullptr}
    , m_size{0}
    , m_capacity{0}
{}

template <typename T>
Vector<T>::Vector(size_t size)
    : m_data{new T[size * 2]}
    , m_size{size}
    , m_capacity{size * 2}
{}

template <typename T>
Vector<T>::Vector(size_t size, const T &val)
    : m_data{new T[size * 2]}
    , m_size{size}
    , m_capacity{size * 2}
{
    for(size_t i = 0; i < m_size; ++i) 
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

    for(size_t i = 0; i < m_size; ++i) 
    {
        m_data[i] = rhs.m_data[i];
    }

    return *this;
}

template <typename T>
Vector<T>::Vector(Vector &&other)
    : m_data{other.m_data}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity}
{
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&rhs)
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
void Vector<T>::push_back(const T &val)
{
    if(m_size >= m_capacity)
    {
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* new_data = new T[new_capacity];

        for(size_t i = 0; i < m_size; ++i) {
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
T& Vector<T>::operator[](size_t index)
{
    return m_data[index];
}

template <typename T>
const T &Vector<T>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
{
    for(size_t i = 0; i < vec.m_size; ++i) 
    {
        os << vec[i] << " ";
    }
    os << '\n';

    return os;
}