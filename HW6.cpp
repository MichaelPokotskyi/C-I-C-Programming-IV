//// Michael Pokotskyi U09662201
//// pokotskyi.m@gmail.com
//// C I C++ Programming IV CSE-40478
//// Raymond Mitchell IV
//// HW6.cpp
//// Win10, Visual C++ 2022, ISO C17
//// Implementation palindrome and compress
//
//#include<iostream>
//#include<list>
//#include "UnitTest++/src/UnitTest++.h"
//using namespace std;
//
//template <typename BidirectionalIterator>
//bool palindrome(BidirectionalIterator first, BidirectionalIterator last) {
//    // if empty
//    if (first == last) { 
//        return false; 
//    }
//    last--;
//    while (first != last) { 
//        if (*first != *last) { 
//            return false;
//        }
//        first++;
//        if (first == last) break;
//        last--;
//    }
//    return true;
//}
//
//template <typename ForwardIterator, typename OutputIterator>
//void compress(ForwardIterator first, ForwardIterator last, OutputIterator result) {
//    // if empty
//    if (first == last) {
//        return;
//    }
//    ForwardIterator second = first; 
//    *result = *first; 
//    result++; 
//    second++;
//    while (second != last) { 
//        if (*second != *first) {
//            *result = *second; 
//            first = second;
//            result++;
//        }
//        second++;
//    }
//}
//
//TEST(TestEmptyList)
//{
//    ostringstream out;
//    list<int> ls;
//    out << palindrome(ls.begin(), ls.end());
//    cout << "Test empty list\n";
//    CHECK_EQUAL("0", out.str());
//    out.str();
//}
//
//TEST(TestOddElementsList_TRUE)
//{
//    ostringstream out;
//    list<int> ls{1,2,1};
//    out << palindrome(ls.begin(), ls.end());
//    cout << "Test list with odd number of elements TRUE\n";
//    CHECK_EQUAL("1", out.str());
//}
//
//TEST(TestOddElementsList_FALSE)
//{
//    ostringstream out;
//    list<int> ls{1,2,3};
//    out << palindrome(ls.begin(), ls.end());
//    cout << "Test list with odd number of elements FALSE\n";
//    CHECK_EQUAL("0", out.str());
//}
//
//TEST(TestEvenElementsList_TRUE)
//{
//    ostringstream out;
//    list<int> ls{1,2,2,1};
//    out << palindrome(ls.begin(), ls.end());
//    cout << "Test list with even number of elements TRUE\n";
//    CHECK_EQUAL("1", out.str());
//}
//
//TEST(TestEvenElementsList_FALSE)
//{
//    ostringstream out;
//    list<int> ls{1,2,3,4};
//    out << palindrome(ls.begin(), ls.end());
//    cout << "Test list with even number of elements FALSE\n";
//    CHECK_EQUAL("0", out.str());
//}
//
//TEST(TestEmptyListCompress) {
//    ostringstream out;
//    list<int> ls, back;
//    compress(ls.begin(), ls.end(), back_inserter(back));
//    cout << "Compress empty list\n";
//    for (auto i : back) {
//        out << i;
//    }
//    CHECK_EQUAL("", out.str());
//}
//
//TEST(TestListContainsConsecutive) {
//    ostringstream out;
//    list<int> ls{1, 1, 2, 2, 2, 3, 3, 3, 3}, back;
//    compress(ls.begin(), ls.end(), back_inserter(back));
//    cout << "Compress list contains consecutive elemets\n";
//    for (auto i : back) {
//        out << i;
//    }
//    CHECK_EQUAL("123", out.str());
//}
//
//TEST(TestListContainsNoConsecutive) {
//    ostringstream out;
//    list<int> ls{1, 2, 3, 1, 2, 3}, back;
//    compress(ls.begin(), ls.end(), back_inserter(back));
//    cout << "Compress list contains no consecutive elemets\n";
//    for (auto i : back) {
//        out << i;
//    }
//    CHECK_EQUAL("123123", out.str());
//}
//
//int main() {
//    // run
//    return UnitTest::RunAllTests();
//}
