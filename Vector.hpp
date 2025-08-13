#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
public:
     
    Vector();
    Vector(size_t size);
    Vector(size_t size, const T& val);

    ~Vector();

    Vector(const Vector&);
    Vector& operator=(const Vector&);

    Vector(Vector&&);
    Vector& operator=(Vector&&);

    void assign(size_t count, const T& val);
    
    void push_back(const T& val);
    void pop_back();
    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void clear();

    void resize(size_t count);
    void resize(size_t count, const T& val);

    void swap(Vector& other);

    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void reserve(size_t new_cap);

    T& front();
    const T& front() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

    template <typename U>
    friend bool operator==(const Vector& lhs, const Vector& rhs);

    template <typename U>
    friend bool operator!=(const Vector& lhs, const Vector& rhs);

private:
    T *m_data;
    size_t m_capacity;
    size_t m_size;
};

#include "Vector.cpp"
#endif