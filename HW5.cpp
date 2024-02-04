//// Michael Pokotskyi U09662201
//// pokotskyi.m@gmail.com
//// C I C++ Programming IV CSE-40478
//// Raymond Mitchell IV
//// BigInt.cpp
//// Win10, Visual C++ 2022, ISO C17
//// Implementation of class auto_ptr
//
//#include <iostream>
//#include <assert.h>
//#include "UnitTest++/src/UnitTest++.h"
//
//template <typename X>
//    class auto_ptr
//    {
//    private:
//        X* mptr;
//
//    public:
//    // ----------------------------------------------
//    //                 CONSTRUCTORS
//    // ----------------------------------------------
//    explicit auto_ptr(X* ptr = 0) throw()
//        : mptr(ptr) {}
//
//    auto_ptr(auto_ptr& ptr) throw()
//        : mptr(ptr.release()) {}
//
//    template <typename Y>
//    auto_ptr(auto_ptr<Y>& ptr) throw()
//        : mptr(ptr.release()) {}
//
//    // ----------------------------------------------
//    //                  DESTRUCTOR
//    // ----------------------------------------------
//
//    // always warning
//    ~auto_ptr() throw()
//    {
//        delete mptr;
//    }
//
//    // ----------------------------------------------
//    //                    ACCESS
//    // ----------------------------------------------
//
//    X* get() const throw()
//    {
//        return mptr;
//    }
//
//    X& operator*() const throw()
//    {
//        assert(mptr != 0);
//        return *mptr;
//    }
//
//    X* operator->() const throw()
//    {
//        assert(mptr != NULL);
//        return mptr;
//    }
//
//    // ----------------------------------------------
//    //                 ASSIGNMENT
//    // ----------------------------------------------
//
//    auto_ptr& operator=(auto_ptr& ptr) throw()
//    {
//        reset(ptr.release());
//        return *this;
//    }
//
//    template <typename Y>
//    auto_ptr& operator=(auto_ptr<Y>& ptr) throw()
//    {
//        reset(ptr.release());
//        return *this;
//    }
//
//    // ----------------------------------------------
//    //               RELEASE & RESET
//    // ----------------------------------------------
//    
//    X* release() throw()
//    {
//        X* temp = mptr;
//        mptr = NULL;
//        return temp;
//    }
//
//    void reset(X* ptr = 0) throw()
//    {
//        if (ptr != mptr)
//        {
//            delete mptr;
//            mptr = ptr;
//        }
//    }
//};
//
//    // ----------------------------------------------
//    //                  UNIT TESTS
//    // ----------------------------------------------
//
//    TEST(PassingToAutoPtr) {
//        int* a = new int(10);
//        std::cout << "TEST PassingToAutoPtr\n";
//        std::cout << "Deref initial pointer BEFORE passing to auto_ptr: " << *a << "\n";
//        CHECK_EQUAL(10, *a);
//        {
//            auto_ptr<int> b(a);
//            std::cout << "Deref new auto_ptr: " << *b << "\n";
//            CHECK_EQUAL(10, *b);
//        }
//        std::cout << "Deref initial pointer AFTER passing to auto_ptr (garbage value should be displayed): " << *a << "\n\n";
//    }
//
//    TEST(MakingOneFromAnotherSameType) {
//        std::cout << "TEST MakingOneFromAnotherSameType\n";
//        int* a = new int(20);
//        std::cout << "Deref initial pointer BEFORE passing to auto_ptr: " << *a << "\n";
//        CHECK_EQUAL(20, *a);
//        {
//            auto_ptr<int> b(a);
//            auto_ptr<int> c(b);
//            std::cout << "Deref new auto_ptr: " << *c << "\n\n";
//            CHECK_EQUAL(20, *c);
//        }
//
//    }
//
//    TEST(PointToZeroAfterAnotherCreation) {
//        std::cout << "TEST PointToZeroAfterAnotherCreation\n";
//        int* a = new int(30);
//        {
//            auto_ptr<int> b(a);
//            auto_ptr<int> c(b);
//            std::cout << "Address of first new auto_ptr: " << b.get() << "\n";
//            std::cout << "Address of second new auto_ptr: " << c.get() << "\n";
//            std::cout << "Deref second new auto_ptr: " << *c << "\n\n";
//            CHECK_EQUAL(30, *c);
//        }
//    }
//
//    TEST(MakingOneFromAnotherDifferType) {
//        std::cout << "TEST MakingOneFromAnotherDifferType\n";
//        int* a = new int(40); 
//        {
//            auto_ptr<int> b(a);
//            std::cout << "Deref initial INT pointer: " << *b << "\n";
//            CHECK_EQUAL(40, *b);
//            auto_ptr<const int> c(b);
//            std::cout << "Deref second CONST INT pointer: " << *c << "\n\n";
//            CHECK_EQUAL(40, *c);
//        }
//    }
//
//    // ----------------------------------------------
//    // Entrypoint
//    // ----------------------------------------------
//    int main()
//    {
//       return UnitTest::RunAllTests();
//    }