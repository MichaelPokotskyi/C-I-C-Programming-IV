//// Michael Pokotskyi U09662201
//// pokotskyi.m@gmail.com
//// C I C++ Programming IV CSE-40478
//// Raymond Mitchell IV
//// HW7.cpp
//// Win10, Visual C++ 2022, ISO C17
//// Implementation of IntegerRange::iterator
//
//#include <iostream>
//#include <cassert>
//#include <algorithm>
//#include <iterator>
//#include <vector>
//#include "UnitTest++.h"
//using namespace std;
//
//// Represents all integer values in the range [low, high).
//// low must be <= high.
//template <typename T>
//class IntegerRange {
//public:
//    class iterator {
//    public:
//        using value_type = T;
//        using difference_type = T;
//        using pointer = T*;
//        using reference = T&;
//        using iterator_category = input_iterator_tag;
//
//        iterator(T current) : current_(current) {
//        }
//
//        iterator& operator+(const iterator& other) {
//            return current_ + other.current_;
//        }
//
//        iterator& operator-(const iterator& other) {
//            return current_ - other.current_;
//        }
//
//        bool operator==(const iterator& other) const {
//            return current_ == other.current_;
//        }
//
//        bool operator!=(const iterator& other) const {
//            return !(*this == other);
//        }
//
//        T operator*() const {
//            return current_;
//        }
//
//        iterator& operator++() {
//            ++current_;
//            return *this;
//        }
//
//        iterator& operator--() {
//            --current_;
//            return *this;
//        }
//
//    private:
//        T current_;
//    };
//
//    IntegerRange(T low, T high) : low_(low), high_(high) {
//        assert(low_ <= high_);
//    }
//
//    const iterator begin() const {
//        return iterator(low_);
//    }
//
//    const iterator end() const {
//        return iterator(high_);
//    }
//
//private:
//    const T low_, high_;
//};
//
//TEST(TestIntCopy) {
//   cout << "Test int + copy: ";
//   ostringstream out;
//   IntegerRange<int> r1(-2, 3);
//   copy(r1.begin(), r1.end(), ostream_iterator<int>(out, " "));
//   CHECK_EQUAL("-2 -1 0 1 2 ", out.str());
//   cout << out.str() << "\n";
//}
//
//TEST(TestUnsignedIntCopy) {
//    cout << "Test unsigned int + copy: ";
//    ostringstream out;
//    IntegerRange<unsigned> r1(0, 6);
//    copy(r1.begin(), r1.end(), ostream_iterator<unsigned>(out, " "));
//    CHECK_EQUAL("0 1 2 3 4 5 ", out.str());
//    cout << out.str() << "\n";
//}
//
//TEST(TestLongReverseCopy) {
//    cout << "Test long + reverse_copy: ";
//    ostringstream out;
//    IntegerRange<long> r1(5, 9);
//    vector<long> v(4);
//    reverse_copy(r1.begin(), r1.end(), v.begin());
//    for (long a : v) {
//        out << a << " ";
//    }
//    CHECK_EQUAL("8 7 6 5 ", out.str());
//    cout << out.str() << "\n";
//}
//
//TEST(TestUnsignedLongCopyIf) {
//    cout << "Test unsigned long + copy_if: ";
//    ostringstream out;
//    IntegerRange<unsigned long> r1(1, 10);
//    copy_if(r1.begin(), r1.end(), ostream_iterator<unsigned long>(out, " "),
//                                    [](int x) { return x % 3 == 0; });
//    CHECK_EQUAL("3 6 9 ", out.str());
//    cout << out.str() << "\n";
//}
//
//TEST(TestShortEqual) {
//    cout << "Test short + equal: ";
//    ostringstream out;
//    IntegerRange<short> r1(1, 5);
//    vector<short> v = {1, 2, 3, 4};
//    out << equal(r1.begin(), r1.end(), v.begin());
//    CHECK_EQUAL("1", out.str());
//    cout << out.str() << "\n\n";
//}
//
//int main() {
//    return UnitTest::RunAllTests();
//}