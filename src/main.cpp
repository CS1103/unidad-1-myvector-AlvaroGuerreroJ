#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "MyVector.hpp"

using std::cout;
using std::endl;
using std::initializer_list;
using std::out_of_range;
using std::string;
using std::vector;

template<class T>
void print_vector(const T& vec);

int main()
{
    // FIXME: This won't work, can't think of a way to solve it.
    // MyVector<int> nums0(10, 121);
    // cout << "nums0:" << endl;
    // print_vector(nums0);

    MyVector<unsigned> vun0 = {1, 4, 9, 16, 25};
    print_vector(vun0);
    vun0.push_back(99);
    print_vector(vun0);
    cout << endl << endl;

    cout << "vun0.front(): " << vun0.front() << endl;
    cout << "vun0.cfront(): " << vun0.cfront() << endl;
    cout << "vun0.back(): " << vun0.back() << endl;
    cout << "vun0.cback(): " << vun0.cback() << endl;
    cout << endl << endl;

    cout << "vun0 is " << (vun0.empty() ? "is empty" : "is not empty") << endl;
    auto vun1 = vun0;
    auto vun2 = vun0 + vun0;
    vun0.clear();
    cout << "vun0 is " << (vun0.empty() ? "is empty" : "is not empty") << endl;
    cout << endl << endl;

    cout << "vun1:" << endl;
    print_vector(vun1);
    cout << endl << endl;

    cout << "vun2:" << endl;
    print_vector(vun2);
    cout << endl << endl;

    cout << "vun1:" << endl;
    for (MyVector<unsigned>::iterator it = vun1.begin(); it != vun1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl << endl << endl;

    cout << "vun1's size: " << vun1.size() << endl;
    cout << "vun1's capacity: " << vun1.capacity() << endl;
    cout << endl;

    vun1.resize(10);
    cout << "executed vun1.resize(10)" << endl;
    cout << endl;

    cout << "vun1's size: " << vun1.size() << endl;
    cout << "vun1's capacity: " << vun1.capacity() << endl;
    cout << endl;

    vun1.reserve(100);
    cout << "executed vun1.reserve(100)" << endl;
    cout << endl;

    cout << "vun1's size: " << vun1.size() << endl;
    cout << "vun1's capacity: " << vun1.capacity() << endl;
    cout << endl;

    vun1.resize(1200);
    cout << "executed vun1.resize(1200)" << endl;
    cout << endl;

    cout << "vun1's size: " << vun1.size() << endl;
    cout << "vun1's capacity: " << vun1.capacity() << endl;
    cout << endl;

    MyVector<string> vst0(3, "hello");

    cout << "vst0:" << endl;
    print_vector(vst0);
    cout << endl << endl;

    MyVector<string> vst1{"something", "here"};

    vst0.insert(vst0.begin(), vst1.begin(), vst1.end());

    cout << "vst0:" << endl;
    print_vector(vst0);
    cout << endl << endl;

    vst0.insert(vst0.end(), vst1.begin(), vst1.end());

    cout << "vst0:" << endl;
    print_vector(vst0);
    cout << endl << endl;

    vst0.insert(vst0.begin(), "start");

    cout << "vst0:" << endl;
    print_vector(vst0);
    cout << endl << endl;

    vst0.insert(vst0.cend(), 3, "mult");

    cout << "vst0:" << endl;
    print_vector(vst0);
    cout << endl << endl;

    cout << vst0[0] << endl;
    cout << vst0.at(0) << endl;

    try
    {
        cout << vst0.at(999999) << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Got you" << endl;
        cout << e.what() << endl;
    }
    cout << endl << endl;

    vector<double> vdo0({2.5, 7.75, 0.888888});

    cout << "vdo0:" << endl;
    print_vector(vdo0);
    cout << endl << endl;

    initializer_list<double> temp = {-.1, -.1, -.1};
    vdo0.insert(vdo0.cbegin() + 1, temp);

    cout << "vdo0:" << endl;
    print_vector(vdo0);
    cout << endl << endl;
}

template<class T>
void print_vector(const T& vec)
{
    for (const auto& e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}
