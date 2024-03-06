// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// dlist.h
// Win10, Visual C++ 2022, ISO C17
// Implementation of DLIST

// include guard
#ifndef DLIST_H
#define DLIST_H

#include <iterator>
#include <algorithm>
using namespace std;

namespace Project2
{
    //dlist container class
    template <typename T>
    class dlist
    {
    public:
        // Types
        class iterator;
        typedef size_t size_type;
        typedef T value_type;
        typedef const T const_reference;

        // Default constructor
        dlist();

        // Copy constructor
        dlist(const dlist&);

        // Iterator range constructor
        template <typename InputIterator> dlist(InputIterator first, InputIterator last);

        // Destructor
        ~dlist();

        // Copy assginment operator
        dlist& operator=(const dlist&);

        // empty() & size()
        bool empty() const;
        size_type size() const;

        // front() & back()
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // Modifiers
        void push_front(const T&);
        void pop_front();
        void push_back(const T&);
        void pop_back();
        iterator insert(iterator, const T&);
        iterator erase(iterator);

        // Comparison
        bool operator==(const dlist&) const;
        bool operator!=(const dlist&) const;
        bool operator<(const dlist&) const;
        bool operator<=(const dlist&) const;
        bool operator>(const dlist&) const;
        bool operator>=(const dlist&) const;

        // Iterators
        iterator begin();
        const iterator begin() const;
        iterator end();
        const iterator end() const;

    private:
        // You decide what goes here
        class node;
        node* head_;
        node* tail_;
        size_type size_;
        void Swap(dlist&);

    };

    template <typename T>
    class dlist<T>::iterator : public std::iterator<bidirectional_iterator_tag, T>
    {
        friend class dlist<T>;

    public:
        typedef const T const_reference;

        iterator();
        explicit iterator(typename dlist<T>::node*);

        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;

        iterator& operator++();
        const iterator operator++(int);
        iterator& operator--();
        const iterator operator--(int);

    private:
        // You decide what goes here
        node* nodePtr_;
    };

    //class defines the individual nodes of dlist
    template <typename T>
    class dlist<T>::node {
    public:
        node(const T& newData = T(), node* n = nullptr, node* p = nullptr)
            : data(newData), next(n), previous(p) {}
        node* next;
        node* previous;
        T data;
    };

    // DLIST
    //default constructor
    template<typename T> 
    dlist<T>::dlist() {
        head_ = new node();
        tail_ = new node();
        size_ = 0;
        head_->next = tail_;
        tail_->previous = head_;
    }

    //copy constructor
    template<typename T>
    dlist<T>::dlist(const dlist& other) {
        head_ = new node();
        tail_ = new node();
        size_ = 0;
        head_->next = tail_;
        tail_->previous = head_;

        if (!other.empty()) {
            node* tempNode = other.head_->next;
            while (tempNode->next != nullptr) {
                this->push_back(tempNode->data);
                tempNode = tempNode->next;
            }
        }
    }

    //destructor
    template<typename T>
    dlist<T>::~dlist() {
        while (!empty()) {
            this->pop_front();
        }
        delete head_;
        delete tail_;
    }

    //assignment operator
    template<typename T>
    dlist<T>& dlist<T>::operator=(const dlist& other) {
        dlist<T> tempDList(other);
        Swap(tempDList);
        return *this;
    }

    //swap two objects
    template<typename T>
    void dlist<T>::Swap(dlist& other) {
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

    //is empty
    template<typename T>
    bool dlist<T>::empty() const {
        return (size_ == 0);
    }

    //size of dlist
    template<typename T>
    typename dlist<T>::size_type dlist<T>::size() const {
        return size_;
    }

    //return dlist front
    template<typename T>
    T& dlist<T>::front() {
        return head_->next->data;
    }

    //return dlist front (const)
    template<typename T>
    const T& dlist<T>::front() const {
        return head_->next->data;
    }

    //return dlist back 
    template<typename T>
    T& dlist<T>::back() {
        return tail_->previous->data;
    }

    //return dlist back (const)
    template<typename T>
    const T& dlist<T>::back() const {
        return tail_->previous->data;
    }

    //add data to front
    template<typename T>
    void dlist<T>::push_front(const T& insertedData) {
        if (empty()) {
            node* newNode = new node(insertedData, tail_, head_);
            head_->next = newNode;
            tail_->previous = newNode;
            ++size_;
        }
        else {
            node* tempFirst = head_->next;
            node* newNode = new node(insertedData, tempFirst, head_);
            tempFirst->previous = newNode;
            head_->next = newNode;
            ++size_;
        }
    }

    //remove data from front
    template<typename T>
    void dlist<T>::pop_front() {
        if (empty()) {
            cerr << "Dlist empty.";
        }
        else {
            node* firstNode = head_->next;
            head_->next = firstNode->next;
            delete firstNode;
            --size_;
        }
    }

    //insert data in back
    template<typename T>
    void dlist<T>::push_back(const T& insertedData) {
        if (empty()) {
            node* newNode = new node(insertedData, tail_, head_);
            head_->next = newNode;
            tail_->previous = newNode;
            ++size_;
        }
        else {
            node* tempLast = tail_->previous;
            node* newNode = new node(insertedData, tail_, tempLast);
            tempLast->next = newNode;
            tail_->previous = newNode;
            ++size_;
        }
    }

    //remove data from back
    template<typename T>
    void dlist<T>::pop_back() {
        if (empty()) {
            cerr << "Dlist empty.";
        }
        else {
            node* lastNode = tail_->previous;
            tail_->previous = lastNode->previous;
            delete lastNode;
            --size_;
        }
    }

    //insert a node to given position
    template<typename T>
    typename dlist<T>::iterator dlist<T>::insert(iterator position, const T& insertedData) {
        if (empty() || position == end()) {
            push_back(insertedData);
            position = find(begin(), end(), insertedData);
            return position;
        }
        else {
            node* nodeMove = head_->next;
            while (nodeMove != tail_) {
                if (nodeMove->data == *position) {
                    node* tempNext = nodeMove->next;
                    node* newNode = new node(insertedData, tempNext, nodeMove);
                    nodeMove->next = newNode;
                    tempNext->previous = newNode;
                    ++size_;
                    position = find(begin(), end(), insertedData);
                    return position;
                }
                else {
                    nodeMove = nodeMove->next;
                }
            }
        }
    }

    //erase node in specified location
    template<typename T>
    typename dlist<T>::iterator dlist<T>::erase(iterator position) {
        if (empty()) {
            cerr << "Dlist empty.";
        }
        else {
            node* nodeMove = head_->next;
            while (nodeMove != tail_) {
                if (nodeMove->data == *position) {
                    node* tempPrev = nodeMove->previous;
                    node* tempNext = nodeMove->next;
                    tempPrev->next = tempNext;
                    tempNext->previous = tempPrev;
                    --size_;
                    ++position;
                    delete nodeMove;
                    return position;
                }
                else {
                    nodeMove = nodeMove->next;
                }
            }
        }
    }

    //return iterator to beginning of dlist
    template<typename T>
    typename dlist<T>::iterator dlist<T>::begin() {
        return iterator(head_->next);
    }

    //return iterator to beginning of dlist (const)
    template<typename T>
    const typename dlist<T>::iterator dlist<T>::begin() const {
        return iterator(head_->next);
    }

    //return iterator to one past the end of dlist
    template<typename T>
    typename dlist<T>::iterator dlist<T>::end() {
        return iterator(tail_);
    }

    //return iterator to one past the end of dlist (const)
    template<typename T>
    const typename dlist<T>::iterator dlist<T>::end() const {
        return iterator(tail_);
    }

    //constructor for iterator range
    template<typename T>
    template<typename InputIterator>
    dlist<T>::dlist(InputIterator first, InputIterator last) {
        head_ = new node();
        tail_ = new node();
        size_ = 0;
        head_->next = tail_;
        tail_->previous = head_;
        while (first != last) {
            this->push_back(*first++);
        }
    }

    //equality
    template<typename T>
    bool dlist<T>::operator==(const dlist& rhs) const {
        if (size_ != rhs.size_)
            return false;
        return equal(begin(), end(), rhs.begin());
    }

    //inequality
    template<typename T>
    bool dlist<T>::operator!=(const dlist& rhs) const {
        return !(*this == rhs);
    }

    //less-than
    template<typename T>
    bool dlist<T>::operator<(const dlist& rhs) const {
        return size_ < rhs.size_;
    }

    //less-than or equal-to
    template<typename T>
    bool dlist<T>::operator<=(const dlist& rhs) const {
        return *this < rhs || *this == rhs;
    }

    //greater-than
    template<typename T>
    bool dlist<T>::operator>(const dlist& rhs) const {
        return !(*this < rhs || *this == rhs);
    }

    //greater-than or equal-to
    template<typename T>
    bool dlist<T>::operator>=(const dlist& rhs) const {
        return !(*this < rhs);
    }

    // ITERATOR
    //default constructor
    template<typename T>
    dlist<T>::iterator::iterator() {
        nodePtr_ = nullptr;
    }

    //constructor with node
    template <typename T>
    dlist<T>::iterator::iterator(typename dlist<T>::node* passedPtr) {
        nodePtr_ = passedPtr;
    }

    //assignment
    template <typename T>
    bool dlist<T>::iterator::operator==(const iterator& rhs) const {
        return nodePtr_ == rhs.nodePtr_;
    }

    //inequality
    template <typename T>
    bool dlist<T>::iterator::operator!=(const iterator& rhs) const {
        return !(*this == rhs);
    }

    //dereference
    template <typename T>
    T& dlist<T>::iterator::operator*() {
        return (*nodePtr_).data;
    }

    //dereference (const)
    template <typename T>
    const T& dlist<T>::iterator::operator*() const {
        return (*nodePtr_).data;
    }

    //arrow
    template <typename T>
    T* dlist<T>::iterator::operator->() {
        return &((*nodePtr_).data);
    }

    //arrow (const)
    template <typename T>
    const T* dlist<T>::iterator::operator->() const {
        return &((*nodePtr_).data);
    }

    //pre-increment
    template <typename T>
    typename dlist<T>::iterator& dlist<T>::iterator::operator++() {
        nodePtr_ = nodePtr_->next;
        return *this;
    }

    //post-increment
    template <typename T>
    const typename dlist<T>::iterator dlist<T>::iterator::operator++(int) {
        iterator temp(*this);
        operator++();
        return temp;
    }

    //pre-decrement
    template <typename T>
    typename dlist<T>::iterator& dlist<T>::iterator::operator--() {
        nodePtr_ = nodePtr_->previous;
        return *this;
    }

    //post-decrement
    template <typename T>
    const typename dlist<T>::iterator dlist<T>::iterator::operator--(int) {
        iterator temp(*this);
        operator--();
        return temp;
    }
}
#endif