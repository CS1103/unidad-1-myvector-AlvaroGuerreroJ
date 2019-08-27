#ifndef GUARD_MYVECTOR_HPP
#define GUARD_MYVECTOR_HPP

#include <cstddef>

template<class T>
class MyVector
{
private:
    T* m_vec_arr;
    std::size_t m_size;
    std::size_t m_reserved;

public:
    typedef T value_type; 
    typedef std::size_t size_type; 

public:
    MyVector();
    ~MyVector();

    void push_back(const T& value);
    void pop_back();

    value_type& operator[](size_type pos);
    value_type& at(size_type pos);

    size_type size() const;
    MyVector<T> operator+(const MyVector<T>& other);
};

template<class T>
MyVector<T>::MyVector()
{
    m_vec_arr = nullptr;
    m_size = 0;
    m_reserved = 0;
}

template<class T>
MyVector<T>::~MyVector()
{
    if (m_vec_arr != nullptr)
    {
        delete[] m_vec_arr;
    }
}

template<class T>
void MyVector<T>::push_back(const T& value)
{
    // TODO
}

template<class T>
MyVector<T>::size_type MyVector<T>::size() const
{
    return m_size;
}

template<class T>
void MyVector<T>::pop_back()
{
    // TODO
}

template<class T>
MyVector<T>::value_type& MyVector<T>::operator[](size_type pos)
{
    // TODO
}

template<class T>
MyVector<T>::value_type& MyVector<T>::at(size_type pos)
{
    // TODO
}

template<class T>
MyVector<T> MyVector<T>::operator+(const MyVector<T>& other)
{
    // TODO
}

#endif
