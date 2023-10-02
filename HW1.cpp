//
// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// HW1.cpp
// Win10, Visual C++ 2022, ISO C17

// Units tests for: deque & algorithm
//                  string & algorithm
//                  vector & algorithm

using namespace std;

#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <vector>
// back_inserter
#include <iterator>
// accumulate
#include <numeric> 
// ostringstream
#include <sstream> 

class Numbers {
public:
    // constructor with initial value
    Numbers() : cur{0} {
    }
    int operator()() {
        return ++cur;
    }
private:
    int cur;
};

class LowerChar {
public:
    // constructor with initial value
    LowerChar() : cur{'a'} {
    }
    char operator()() {
        return cur++;
    }
private:
    char cur;
};

// func :: isEven?
bool isEven(int i) { 
    return (i % 2) == 0;
}

// Unit tests implementation
void testDeque() {
    Numbers number;
    const size_t VALUES_QTY = 10;
    const int RESULT = 55;
    deque<int> temp;
    // Use the generate_n algorithm to populate a deque with the values 1 through 10 
    generate_n(back_inserter(temp), VALUES_QTY, number);
    // Use the accumulate algorithm to compute the sum of the values in the deque
    int test = accumulate(temp.begin(), temp.end(), 0);
    // Verify that the sum is 55
    if (test == RESULT)
        clog << "Test PASSED\n";
    else
        clog << "Test FAILED -> Expected accumulation " << RESULT <<
        " but instead have " << test << "\n";
}

void testString() {
    LowerChar lowerLetter;
    const size_t VALUES_QTY = 26;
    string temp;
    const string RESULT = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Create a string containing the lowercase letters of the alphabet in ascending order
    generate_n(back_inserter(temp), VALUES_QTY, lowerLetter);
    // Use the transform algorithm to convert the string to uppercase.
    transform(temp.begin(), temp.end(), temp.begin(), toupper);
    // Verify that the string contains the uppercase letters of the alphabet in ascending order
    if (temp.compare(RESULT) == 0)
        clog << "Test PASSED\n";
    else
        clog << "Test FAILED -> Expected string " << RESULT 
        << " but instead have " << temp << "\n";
}

void testVector() {
    vector<int>::iterator div;
    const string RESULT = "24681013579";
    ostringstream temp;
    ostream_iterator<int> out_it(temp);
    // Create an array literal containing the values 10 through 1
    const int ARRAY_INITIAL[] = {10,9,8,7,6,5,4,3,2,1};
    /* Create a vector initialized to contain the values in the array by
    using the vector’s iterator range constructor */
    vector<int> tempVec(ARRAY_INITIAL, ARRAY_INITIAL + sizeof(ARRAY_INITIAL) / sizeof(int));
    /* Use the partition algorithm to place the even numbers in the lower half of the
    vector and the odd numbers in the upper half of the vector */
    div = partition(tempVec.begin(), tempVec.end(), isEven);
    // Use the sort algorithm to sort each partition
    sort(tempVec.begin(), div);
    sort(div, tempVec.end());
    // Use the copy algorithm to copy the vector’s elements to an ostring_stream
    copy(tempVec.begin(), tempVec.end(), out_it);
    // Verify that the ostring_stream contents are “24681013579”
    if (temp.str().compare(RESULT) == 0)
        clog << "Test PASSED\n";
    else
        clog << "Test FAILED -> Expected output " << RESULT 
        << " but instead have " << temp.str() << "\n";
}

int main(void) {
    // run tests
    testDeque();
    testString();
    testVector();
}