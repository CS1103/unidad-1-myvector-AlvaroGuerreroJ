#ifndef GUARD_MYVECTOR_HPP
#define GUARD_MYVECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

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
    MyVector(const MyVector<T>& other);
    MyVector(MyVector<T>&& other);
    MyVector(std::initializer_list<T> il);
    template<class It>
    MyVector(It beg, It end);
    MyVector(size_type count, const T& value = T());
    ~MyVector();

    void push_back(const T& value);
    void pop_back();

    value_type& operator[](size_type pos);
    const value_type& operator[](size_type pos) const;
    value_type& at(size_type pos);
    const value_type& at(size_type pos) const;

    size_type size() const;
    MyVector<T> operator+(const MyVector<T>& other);
    MyVector<T>& operator=(const MyVector<T>& other);
};

template<class T>
MyVector<T>::MyVector()
{
    m_vec_arr = nullptr;
    m_size = 0;
    m_reserved = 0;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
    m_size = other.size();
    m_reserved = other.size();
    m_vec_arr = new T[other.size()];
    std::copy(other.m_vec_arr, other.m_vec_arr + other.size(), m_vec_arr);
}

template<class T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
    m_size = other.size();
    m_reserved = other.size();
    m_vec_arr = other.m_vec_arr;
    other.m_size = 0;
    other.m_reserved = 0;
    other.m_vec_arr = nullptr;
}

template<class T>
MyVector<T>::MyVector(MyVector<T>::size_type count, const T& value)
{
    m_vec_arr = new T[count];
    m_reserved = count;
    m_size = count;

    for (size_type i = 0; i < count; i++)
    {
        m_vec_arr[i] = value;
    }
}

template<class T>
MyVector<T>::MyVector(std::initializer_list<T> il)
{
    m_reserved = il.size();
    m_size = il.size();
    m_vec_arr = new T[il.size()];
    std::copy(il.begin(), il.end(), m_vec_arr);
}

template<class T>
template<class It>
MyVector<T>::MyVector(It beg, It end)
{
    size_type sz = std::distance(beg, end);
    m_reserved = sz;
    m_size = sz;
    m_vec_arr = new T[sz];
    std::copy(beg, end, m_vec_arr);
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
    if (m_size == m_reserved)
    {
        // TODO: This should probably be another method
        m_reserved = std::max(m_reserved, size_type(1));
        m_reserved <<= 1;
        T* temp = m_vec_arr;
        m_vec_arr = new T[m_reserved];
        std::copy(temp, temp + m_size, m_vec_arr);
        delete[] temp;
    }
    m_vec_arr[m_size] = value;
    m_size++;
}

template<class T>
typename MyVector<T>::size_type MyVector<T>::size() const
{
    return m_size;
}

template<class T>
void MyVector<T>::pop_back()
{
    if (m_size > 0)
    {
        m_size -= 1;
    }
}

template<class T>
typename MyVector<T>::value_type& MyVector<T>::operator[](size_type pos)
{
    // operator[] doesn't perform bound checking
    return m_vec_arr[pos];
}

template<class T>
const typename MyVector<T>::value_type& MyVector<T>::operator[](size_type pos) const
{
    // operator[] doesn't perform bound checking
    return m_vec_arr[pos];
}

template<class T>
typename MyVector<T>::value_type& MyVector<T>::at(size_type pos)
{
    if (pos >= m_size)
    {
        // TODO: Add explanatory string
        throw std::out_of_range();
    }
    return m_vec_arr[pos];
}

template<class T>
const typename MyVector<T>::value_type& MyVector<T>::at(size_type pos) const
{
    if (pos >= m_size)
    {
        // TODO: Add explanatory string
        throw std::out_of_range();
    }
    return m_vec_arr[pos];
}

template<class T>
MyVector<T> MyVector<T>::operator+(const MyVector<T>& other)
{
    size_type new_size = this->size() + other.size();
    MyVector ret(new_size);

    // TODO: I think this could be prettier
    for (size_type i = 0; i < this->size(); i++)
    {
        ret[i] = (*this)[i];
    }
    for (size_type i = this->size(); i < this->size() + other.size(); i++)
    {
        ret[i] = other[i - this->size()];
    }

    return ret;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
    m_reserved = other.size();
    m_size = other.size();
    m_vec_arr = new T[other.size()];

    std::copy(other.m_vec_arr, other.m_vec_arr + other.size(), m_vec_arr);

    return *this;
}

#endif
