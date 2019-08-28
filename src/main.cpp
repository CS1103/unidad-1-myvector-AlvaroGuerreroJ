#include <iostream>
#include <string>
#include <vector>

#include "MyVector.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

template<class T>
void print_vector(const MyVector<T>& vec);

int main()
{
    // FIXME: This won't work, can't think of a way to solve it.
    // MyVector<int> nums0(10, 121);
    // cout << "nums0:" << endl;
    // print_vector(nums0);

    MyVector<int> nums1;
    nums1.push_back(10);
    nums1.push_back(20);
    nums1.push_back(30);
    cout << "nums1:" << endl;
    print_vector(nums1);

    MyVector<int> nums2 = {1, 4, 9, 16, 25, 36};
    cout << "nums2:" << endl;
    print_vector(nums2);

    MyVector<int> nums3 = nums1 + nums2;
    cout << "nums3:" << endl;
    print_vector(nums3);

    MyVector<int> nums4(nums1);
    cout << "nums4:" << endl;
    print_vector(nums4);

    MyVector<int> nums5(nums1 + nums2);
    cout << "nums5:" << endl;
    print_vector(nums5);

    nums5 = nums1;
    cout << "nums5:" << endl;
    print_vector(nums5);

    vector<string> v = {"hello", "world"};
    MyVector<string> words0(v.begin(), v.end());
    cout << "words0:" << endl;
    print_vector(words0);
}

template<class T>
void print_vector(const MyVector<T>& vec)
{
    for (typename MyVector<T>::size_type i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
}
