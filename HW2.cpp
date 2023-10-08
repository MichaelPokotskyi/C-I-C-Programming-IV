//
// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// HW2.cpp
// Win10, Visual C++ 2022, ISO C17
// Implement Queue container for HW2, queue elements stored in v_ buffer

#include <iostream>
#include <cassert>
#include <exception>
using namespace std;

template <typename T>
class Queue {
public:
    Queue(); // Construct empty queue
    ~Queue(); // Destructor
    Queue(const Queue&); // Copy constructor
    Queue& operator=(const Queue&); // Copy assignment operator
    void push(const T&); // Add elem to back of queue
    void pop(); // Remove front elem from queue
    T& front(); // Return ref to front elem in queue
    const T& front() const; // Return ref to front elem in queue
    bool empty() const; // Return whether queue is empty
    size_t size() const; // Return # of elems in queue
private:
    T* v_; // Pointer to elems in queue
    size_t vsize_; // Entire queue size
    size_t vused_; // Used size
};
// Default constructor
template <typename T>
Queue<T>::Queue() : v_(0), vsize_(10), vused_(0) {
    v_ = new T[vsize_]; // size allocation
}
// Destructor
template <typename T>
Queue<T>::~Queue() {
    delete[] v_;
}
// Helper function for copying array
template <typename T>
T*
newCopy(const T* source, size_t source_size, size_t destin_size) {
    assert(destin_size >= source_size);
    T* destination = new T[destin_size];
    try {
        copy(source, source + source_size, destination);
    }
    catch (...) {
        delete[]destination;
        throw;
    }
    return destination;
}
// Copy constructor
template <typename T>
Queue<T>::Queue(const Queue<T>& other)
    :v_(newCopy(other.v_, other.vsize_, other.vsize_)),
    vsize_(other.vsize_), vused_(other.vused_) {
}
// Copy assignment operator
template <typename T>
Queue<T>&
Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        T* v_new = newCopy(other.v_, other.vsize_, other.vsize_);
        delete[] v_;
        v_ = v_new;
        vsize_ = other.vsize_;
        vused_ = other.vused_;
    }
    return *this;
}
// Push to the back
template <typename T>
void
Queue<T>::push(const T& t) {
    // grow if necessary
    if (vused_ == vsize_) {
        size_t vsize_new = vsize_ * 2 + 1;
        T* v_new = newCopy(v_, vsize_, vsize_new);
        delete[]v_;
        v_ = v_new;
        vsize_ = vsize_new;
    }
    // adding element to back
    v_[vused_] = t;
    // ++ after element copy
    ++vused_;
}
// Pop from the front
template <typename T>
void
Queue<T>::pop() {
    if (vused_ == 0) {
        throw logic_error("Has an empty Queue!");
    }
    else {
        size_t vsize_new = vused_ - 1;
        T* v_new = newCopy(v_ + 1, vsize_new, vsize_);
        delete[] v_;
        // replacing with changed array
        v_ = v_new;
        // -- after removal
        --vused_;
    }
}
// Return reference to front elem
template <typename T>
T&
Queue<T>::front() {
    if (vused_ == 0)
        throw logic_error("Has an empty Queue!");
    else
        return v_[0];
}
// Return reference to front elem /const/
template <typename T>
const T&
Queue<T>::front() const {
    if (vused_ == 0)
        throw logic_error("Has an empty Queue!");
    else
        return v_[0];
}
// Queue is empty?
template <typename T>
bool
Queue<T>::empty() const {
    return (vused_ == 0);
}
// Return queue # of elements
template <typename T>
size_t
Queue<T>::size() const {
    return (vused_);
}
//**********//
//All tests://
void testQueueConstructor() {
    try {
        Queue<int> tempQ;
        clog << "testQueueConstructor test PASSED\n";
    }
    catch (...) {
        clog << "testQueueConstructor test FAILED\n";
    }
}
void testQueueDestructor() {
    Queue<int>* testQ = new Queue<int>;
    try {
        delete testQ;
        clog << "testQueueDestructor test PASSED\n";
    }
    catch (...) {
        Queue<int> tempQ;
        clog << "testQueueDestructor test FAILED\n";
    }
}
void testQueueCopyConstructor() {
    Queue<int> sourceQ;
    const int VALID_INPUT = 50;
    const int NUMBER_ELEMENTS = 5;
    for (int i = 0; i < NUMBER_ELEMENTS; i++) {
        sourceQ.push(VALID_INPUT * i + 1);
    }
    try {
        Queue<int> copyQueue(sourceQ);
        for (int i = 0; i < NUMBER_ELEMENTS; i++) {
            if (sourceQ.front() == copyQueue.front()) {
                sourceQ.pop(); copyQueue.pop();
            }
            else {
                clog << "testQueueCopyConstructor test FAILED -> Expected output "
                    << sourceQ.front() << " but instead have "
                    << copyQueue.front() << "\n";
            }
        }
        clog << "testQueueCopyConstructor test PASSED\n";
    }
    catch (...) {
        clog << "testQueueCopyConstructor test FAILED\n";
    }
}
void testQueueCopyAssignment() {
    Queue<int> sourceQ;
    const int VALID_INPUT = 50;
    const int NUMBER_ELEMENTS = 5;
    for (int i = 0; i < NUMBER_ELEMENTS; i++) {
        sourceQ.push(VALID_INPUT * i + 1);
    }
    try{
        Queue<int> copyQueue = sourceQ;
        for (int i = 0; i < NUMBER_ELEMENTS; i++) {
            if (sourceQ.front() == copyQueue.front()) {
                sourceQ.pop(); copyQueue.pop();
            }
            else {
                clog << "testQueueCopyAssignment test FAILED -> Expected output "
                    << sourceQ.front() << " but instead have " <<
                    copyQueue.front() << "\n";
            }
        }
        clog << "testQueueCopyAssignment test PASSED\n";
    }
    catch (...) {
        clog << "testQueueCopyAssignment test FAILED\n";
    }
}
void testQueuePush() {
    Queue<int> tempQ;
    try {
        const int INPUT = 1;
        const size_t ORIG_SIZE = 10;
        const size_t NEW_SIZE = 11; // +1 elem
        for (int i = 0; i < ORIG_SIZE; ++i) {
            tempQ.push(i * INPUT);
        }
        clog << "testQueuePush test PASSED\n";
        // add one more elem to check
        tempQ.push(INPUT);
        // checking
        if (tempQ.size() == NEW_SIZE)
            clog << "testQueuePush test PASSED\n";
        else
            clog << "testQueuePush test FAILED -> Expected output "
            << NEW_SIZE << " but instead have " << tempQ.size() << "\n";
    }
    catch (...) {
        clog << "testQueuePush test FAILED\n";
    }
}
void testQueuePop() {
    Queue<int> tempQ;
    try {
        tempQ.pop();
        clog << "testQueuePop empty test FAILED\n";
    }
    catch (exception& e) {
        if (strcmp(e.what(), "Has an empty Queue!") == 0)
            clog << "testQueuePop empty test PASSED\n";
        else
            clog << "testQueuePop empty test FAILED -> Expected different output\n";
    }
    //test succes
    try {
        const int FIRST_INPUT = 1;
        const int SECOND_INPUT = 2;
        tempQ.push(FIRST_INPUT);
        tempQ.push(SECOND_INPUT);
        if (tempQ.front() == FIRST_INPUT)
            tempQ.pop();
        // test FIRST_INPUT was successfully removed
        if (tempQ.front() == SECOND_INPUT)
            clog << "testQueuePop test PASSED\n";
    }
    catch (...) {
        clog << "testQueuePop test FAILED\n";
    }
}
void testQueueFront() {
    Queue<int> tempQ;
    const int VALID_VALUE = 1;
    tempQ.push(VALID_VALUE);
    try {
        const int* TEST_VALUE = &(tempQ.front());
        if (*TEST_VALUE == VALID_VALUE)
            clog << "testQueueFront test PASSED\n";
        else
            clog << "testQueueFront test FAILED -> Expected output "
            << VALID_VALUE << " but instead have " << TEST_VALUE << "\n";
    }
    catch (...) {
        clog << "testQueueFront test FAILED\n";
    }
}
void testQueueFrontConst() {
    Queue<int> tempQ;
    const int VALID_VALUE = 1;
    tempQ.push(VALID_VALUE);
    try {
        const int* TEST_VALUE = &(tempQ.front());
        if (*TEST_VALUE == VALID_VALUE)
            clog << "testQueueFrontConst test PASSED\n";
        else
            clog << "testQueueFrontConst test FAILED -> Expected output "
            << VALID_VALUE << " but instead have " << TEST_VALUE << "\n";
    }
    catch (...) {
        clog << "testQueueFrontConst test FAILED\n";
    }
}
void testQueueEmpty() {
    Queue<int> tempQ0;
    const int VALID_VALUE = 1;
    tempQ0.push(VALID_VALUE);
    tempQ0.push(VALID_VALUE);
    const int VALID_SIZE = 2;
    try {
        Queue<int> tempQ1;
        if ((tempQ1.empty()) && (!tempQ0.empty()))
            clog << "testQueueEmpty test PASSED\n";
        else
            clog << "testQueueEmpty test FAILED\n";
    }
    catch (...) {
        clog << "testQueueEmpty test FAILED\n";
    }
}
void testQueueSize() {
    Queue<int> tempQ;
    const int VALID_VALUE = 1;
    tempQ.push(VALID_VALUE);
    tempQ.push(VALID_VALUE);
    const int VALID_SIZE = 2;
    try {
        const int TEST_VALUE = tempQ.size();
        if (TEST_VALUE == VALID_SIZE)
            clog << "testQueueSize test PASSED\n";
        else
            clog << "testQueueSize FAILED -> Expected output "
            << VALID_VALUE << " but instead have " << VALID_SIZE << "\n";
    }
    catch (...) {
        clog << "testQueueSize test FAILED\n";
    }
}

int main(void) {
    // running test cases
    testQueueConstructor();       // test Queue<T>::Queue()
    testQueueDestructor();        // test Queue<T>::~Queue()
    testQueueCopyConstructor();   // test Queue<T>::Queue(const Queue &)
    testQueueCopyAssignment();    // test Queue<T>::operator=(const Queue &)
    testQueuePush();              // test Queue<T>::push(const T &)
    testQueuePop();               // test Queue<T>::pop()
    testQueueFront();             // test Queue<T>::front()
    testQueueFrontConst();        // test Queue<T>::front() const
    testQueueEmpty();             // test Queue<T>::empty() const
    testQueueSize();              // test Queue<T>::size() const
}