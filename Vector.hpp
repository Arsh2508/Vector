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

    
    void push_back(const T& val);
    void pop_back();
    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

private:
    T *m_data;
    size_t m_capacity;
    size_t m_size;
};

#include "Vector.cpp"
#endif