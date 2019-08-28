#ifndef GUARD_MYVECTOR_HPP
#define GUARD_MYVECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <sstream>
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
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;

public:
    MyVector();
    MyVector(const MyVector<T>& other);
    MyVector(MyVector<T>&& other);
    MyVector(std::initializer_list<T> il);
    MyVector(size_type count);
    MyVector(size_type count, const T& value);
    template<class It>
    MyVector(It beg, It end);
    ~MyVector();

    value_type& operator[](size_type pos);
    const value_type& operator[](size_type pos) const;
    value_type& at(size_type pos);
    const value_type& at(size_type pos) const;

    reference front()
    {
        return *m_vec_arr;
    }

    const_reference cfront() const
    {
        return *m_vec_arr;
    }

    reference back()
    {
        iterator temp = end();
        temp--;
        return *temp;
    }

    const_reference cback() const
    {
        const_iterator temp = cend();
        temp--;
        return *temp;
    }

    iterator begin()
    {
        T* ret = m_vec_arr;
        return ret;
    }

    const_iterator begin() const
    {
        return cbegin();
    }

    const_iterator cbegin() const
    {
        const T* ret = m_vec_arr;
        return ret;
    }

    iterator end()
    {
        T* ret = m_vec_arr + m_size;
        return ret;
    }

    const_iterator end() const
    {
        return cend();
    }

    const_iterator cend() const
    {
        const T* ret = m_vec_arr + m_size;
        return ret;
    }

    void push_back(const T& value);
    void pop_back();
    void clear();

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    template<class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    void resize(size_type count, T value = T());
    void reserve(size_type new_cap);

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
    std::copy(other.begin(), other.end(), m_vec_arr);
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
MyVector<T>::MyVector(MyVector<T>::size_type count)
{
    m_vec_arr = new T[count];
    m_reserved = count;
    m_size = count;
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
    this->insert(this->end(), value);
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
void MyVector<T>::clear()
{
    m_size = 0;
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos,
                                                   const T& value)
{
    return insert(pos, size_type(1), value);
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos,
                                                   size_type count,
                                                   const T& value)
{
    // TODO: This is pretty similar to insert(const_iterator, InputIt, InputIt)
    //       should think of a way to refactor together.
    size_type new_size = m_size + count;
    iterator mpos = this->begin();
    std::advance(mpos, std::distance(this->cbegin(), pos));

    // If there is enough space in the current array, rotate the appropiate
    // values to the right and then insert in the appropiate position.
    if (new_size <= m_reserved)
    {
        // Copy the soon to be overwritten elements later in the array
        for (iterator replacing = mpos, replacee = mpos + count;
            replacing != this->end(); replacee++, replacing++)
        {
            *replacee = *replacing;
        }
        // Ovewrite the contents
        for (iterator replacee = mpos; count != 0; count--)
        {
            *replacee = value;
            replacee++;
        }

        m_size = new_size;
        
        return mpos;
    }
    // If there's not enough space, create a new array and copy the elements in
    // the current object til the indicated position, insert the copies of
    // value and insert the elements from [pos, this->end())
    else
    {
        size_type new_reserve = m_reserved;
        while (new_reserve < new_size)
        {
            new_reserve = std::max(size_type(1), new_reserve << 1);
        }

        T* new_arr = new T[new_reserve];
        T* cur_pos_new_arr = new_arr;
        for (iterator it = this->begin(); it != mpos; it++)
        {
            *cur_pos_new_arr = *it;
            cur_pos_new_arr++;
        }
        iterator ret(cur_pos_new_arr);
        for (; count != 0; count--)
        {
            *cur_pos_new_arr = value;
            cur_pos_new_arr++;
        }
        for (iterator it = mpos; it != this->end(); it++)
        {
            *cur_pos_new_arr = *it;
            cur_pos_new_arr++;
        }

        delete[] m_vec_arr;
        m_vec_arr = new_arr;
        m_reserved = new_reserve;
        m_size = new_size;

        return ret;
    }
}

template<class T>
template<class InputIt>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos,
                                                   InputIt first, InputIt last)
{
    size_type n_new_elements = std::distance(first, last);
    size_type new_size = m_size + n_new_elements;
    iterator mpos = this->begin();
    std::advance(mpos, std::distance(this->cbegin(), pos));

    // If there is enough space in the current array, rotate the appropiate
    // values to the right and then insert in the appropiate position.
    if (new_size <= m_reserved)
    {
        // Copy the soon to be overwritten elements later in the array
        for (iterator replacing = mpos, replacee = mpos + n_new_elements;
            replacing != this->end(); replacee++, replacing++)
        {
            *replacee = *replacing;
        }
        // Ovewrite the contents
        for (iterator replacee = mpos; first != last; first++)
        {
            *replacee = *first;
            replacee++;
        }

        m_size = new_size;
        
        return iterator(mpos);
    }
    // If there's not enough space, create a new array and copy the elements in
    // the current object til the indicated position, insert the elements in
    // [first, last), and insert the elements from [pos, this->end())
    else
    {
        size_type new_reserve = m_reserved;
        while (new_reserve < new_size)
        {
            new_reserve <<= 1;
        }

        T* new_arr = new T[new_reserve];
        T* cur_pos_new_arr = new_arr;
        for (iterator it = this->begin(); it != mpos; it++)
        {
            *cur_pos_new_arr = *it;
            cur_pos_new_arr++;
        }
        iterator ret(cur_pos_new_arr);
        for (InputIt it = first; it != last; it++)
        {
            *cur_pos_new_arr = *it;
            cur_pos_new_arr++;
        }
        for (iterator it = mpos; it != this->end(); it++)
        {
            *cur_pos_new_arr = *it;
            cur_pos_new_arr++;
        }

        delete[] m_vec_arr;
        m_vec_arr = new_arr;
        m_reserved = new_reserve;
        m_size = new_size;

        return ret;
    }
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos,
                                                   std::initializer_list<T> ilist)
{
    this->insert(ilist.begin(), ilist.end());
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator pos)
{
    // TODO
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator first,
                                                  const_iterator last)
{
    // TODO
}

template<class T>
bool MyVector<T>::empty() const
{
    return m_size == 0;
}
    
template<class T>
typename MyVector<T>::size_type MyVector<T>::size() const
{
    return m_size;
}

template<class T>
typename MyVector<T>::size_type MyVector<T>::capacity() const
{
    return m_reserved;
}

template<class T>
void MyVector<T>::resize(size_type count, T value)
{
    if (count <= m_size)
    {
        m_size = count;
    }
    else
    {
        reserve(count);
        while (m_size != count)
        {
            m_vec_arr[m_size] = value;
            m_size++;
        }
    }
}

template<class T>
void MyVector<T>::reserve(size_type new_cap)
{
    if (new_cap <= m_reserved)
    {
        return;
    }
    size_type new_reserved = m_reserved;
    while (new_reserved < new_cap)
    {
        new_reserved = std::max(new_reserved << 1, size_type(1));
    }
    
    T* temp = new T[new_reserved];
    std::copy(this->begin(), this->end(), temp);
    delete[] m_vec_arr;
    m_vec_arr = temp;
    m_reserved = new_reserved;
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
        // TODO: There should be a better way
        std::ostringstream os;
        os << pos << " is not a valid position in the vector";
        throw std::out_of_range(os.str());
    }
    return m_vec_arr[pos];
}

template<class T>
const typename MyVector<T>::value_type& MyVector<T>::at(size_type pos) const
{
    if (pos >= m_size)
    {
        // TODO: There should be a better way
        std::ostringstream os;
        os << pos << " is not a valid position in the vector";
        throw std::out_of_range(os.str());
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
