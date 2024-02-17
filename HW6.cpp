

#include<iostream>
#include<list>
#include "UnitTest++/src/UnitTest++.h"
using namespace std;

template <typename BidirectionalIterator>
bool palindrome(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) { 
        return false; 
    }
    last--;
    while (first != last) { 
        if (*first != *last) { 
            return false;
        }
        first++;
        if (first == last) break;
        last--;
    }
    return true;
}

template <typename ForwardIterator, typename OutputIterator>
void compress(ForwardIterator first, ForwardIterator last, OutputIterator result) {
    if (first == last) {
        return;
    }
    ForwardIterator second = first; 
    *result = *first; 
    result++; 
    second++;
    while (second != last) { 
        if (*second != *first) {
            *result = *second; 
            first = second;
            result++;
        }
        second++;
    }
}

TEST(TestEmptyList)
{
    ostringstream out;
    list<int> ls;
    out << palindrome(ls.begin(), ls.end());
    cout << "Test empty list\n";
    CHECK_EQUAL("0", out.str());
    out.str();
}

TEST(TestOddElementsList_TRUE)
{
    ostringstream out;
    //string out;
    int data[] = { 1,2,1 };
    list<int> ls(data, data + 3);
    out << palindrome(ls.begin(), ls.end());
    cout << "Test list with odd number of elements TRUE\n";
    CHECK_EQUAL("1", out.str());
}

TEST(TestOddElementsList_FALSE)
{
    ostringstream out;
    int data[] = { 1,2,3 };
    list<int> ls(data, data + 3);
    out << palindrome(ls.begin(), ls.end());
    cout << "Test list with odd number of elements FALSE\n";
    CHECK_EQUAL("0", out.str());
}

TEST(TestEvenElementsList_TRUE)
{
    ostringstream out;
    int data1[] = { 1,2,2,1 };
    list<int> ls(data1, data1 + 4);
    out << palindrome(ls.begin(), ls.end());
    cout << "Test list with even number of elements TRUE\n";
    CHECK_EQUAL("1", out.str());
}

TEST(TestEvenElementsList_FALSE)
{
    ostringstream out;
    int data1[] = { 1,2,3,4 };
    list<int> ls(data1, data1 + 4);
    out << palindrome(ls.begin(), ls.end());
    cout << "Test list with even number of elements FALSE\n";
    CHECK_EQUAL("0", out.str());
}

TEST(Test) {}

int main() {

    UnitTest::RunAllTests();

    // empty list compress
    list<int> ls5, ls6;
    compress(ls5.begin(), ls5.end(), back_inserter(ls6));

    for (auto ele : ls6) {
        cout << ele << " ";
    } cout << "\n";

    // compress list containing no consecutive duplicates
    int data4[] = { 1,2,3,1,2,3 };
    list<int> ls7(data4, data4 + 6), ls8;
    compress(ls7.begin(), ls7.end(), back_inserter(ls8));

    for (auto ele : ls8) {
        cout << ele << " ";
    } cout << "\n";

    // compress list containing consecutive duplicates
    int data5[] = { 1,1,2,2,1,1 };
    list<int> ls9(data5, data5 + 6), ls10;
    compress(ls9.begin(), ls9.end(), back_inserter(ls10));

    for (auto ele : ls10) {
        cout << ele << " ";
    } cout << "\n";
}
