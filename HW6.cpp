//#include<iostream>
//#include<list>
//using namespace std;
//
//// returns true if the given range makes a palindrome, else returns false
//// compare the first and last value if same, compare the second and second last values and so on
//// if not same, return false
//template <typename BidirectionalIterator>
//bool palindrome(BidirectionalIterator first, BidirectionalIterator last) {
//    last--; // The range is [first, last) i.e. last is not included so decrement last
//
//    while (first != last) { // if it is an odd palindrome it will exit at the middle element i.e. first will be equal to last
//        if (*first != *last) { //  if the values are not same it is not an palindrome so return false
//            return false;
//        }
//
//        first++;
//        // In case of an even palidrome say [2, 2] we should check if first == last then we should exit
//        // because then there is no element left to check 
//        if (first == last) break;
//        last--;
//    }
//    // if the while didn't return false, it is a palindrome.
//    return true;
//}
//
//// eliminates the consecutive duplicate elements and copies output using the result iterator
//// first: points to the copied element
//// second: moves through the list
//template <typename ForwardIterator, typename OutputIterator>
//void compress(ForwardIterator first, ForwardIterator last, OutputIterator result) {
//    if (first == last) return; // if empty no element can be copied so return
//
//    ForwardIterator second = first; // make an iterator second point to the first element
//    *result = *first; // copy value to the result list
//    result++; // increment result operator to copy the next value
//    second++; // increment second iterator
//
//    while (second != last) { // Exit when second reaches end of the list
//        if (*second != *first) { // Example: In [1 1 2 2] when second points to 2 (index 2) and first points to 1 (index 0)
//            *result = *second; // copy 2 to the result list
//            first = second; // point iterator first to index 2
//            result++;
//        }
//        second++;
//    }
//}
//
//int main() {
//
//    // empty list
//    list<int> ls;
//    cout << palindrome(ls.begin(), ls.end()) << "\n";
//
//    // palindrome containing odd number of elements
//    int data[] = { 1,2,1 };
//    list<int> ls1(data, data + 3);
//    cout << palindrome(ls1.begin(), ls1.end()) << "\n";
//
//    // palindrome containing even number of elements
//    int data1[] = { 1,2,2,1 };
//    list<int> ls2(data1, data1 + 4);
//    cout << palindrome(ls2.begin(), ls2.end()) << "\n";
//
//    // non-palindrome with odd number of elements
//    int data2[] = { 1,2,3 };
//    list<int> ls3(data2, data2 + 3);
//    cout << palindrome(ls3.begin(), ls3.end()) << "\n";
//
//    // non-palindrome with even number of elements
//    int data3[] = { 1,2,3,4 };
//    list<int> ls4(data3, data3 + 4);
//    cout << palindrome(ls4.begin(), ls4.end()) << "\n";
//
//    // empty list compress
//    list<int> ls5, ls6;
//    compress(ls5.begin(), ls5.end(), back_inserter(ls6));
//
//    for (auto ele : ls6) {
//        cout << ele << " ";
//    } cout << "\n";
//
//    // compress list containing no consecutive duplicates
//    int data4[] = { 1,2,3,1,2,3 };
//    list<int> ls7(data4, data4 + 6), ls8;
//    compress(ls7.begin(), ls7.end(), back_inserter(ls8));
//
//    for (auto ele : ls8) {
//        cout << ele << " ";
//    } cout << "\n";
//
//    // compress list containing consecutive duplicates
//    int data5[] = { 1,1,2,2,1,1 };
//    list<int> ls9(data5, data5 + 6), ls10;
//    compress(ls9.begin(), ls9.end(), back_inserter(ls10));
//
//    for (auto ele : ls10) {
//        cout << ele << " ";
//    } cout << "\n";
//}
//
///*
//1. Bidirectional iterators are iterators that can move in both directions. 
//If itr is a bidirectional iterator, we can access its value using *itr, move it forward using itr++ and backward using --itr;
//2. back_inserter(list_name) gives us an iterator that inserts new elements to the end of container 'list_name'.
//*back_inserter(list_name) = 10; // this will insert 10 at the end of the list 'list_name'.
//Compress function:
//In the compress function, I have used two pointers first and second. first points to the copied element, and second iterates through the list.
//If the iterator second points to an element having a different value than the iterator first then:
//1. Copy this value to the result list using the result iterator.
//2. Move the first pointer to the position pointed by the iterator second.
//3. Increment the second iterator.
//If the iterator second points to an element having the same value as the first iterator:
//1. Increment the second iterator.
//Palindrome function:
//Compare the first and last values, if same, compare the second and second last values, and so on until you exhaust the list and 
//if the values are not same at some point, return false.*/