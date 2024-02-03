// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// BigInt.cpp
// Win10, Visual C++ 2022, ISO C17
// Implementation of class auto_ptr

#include <iostream>
#include <assert.h>
// using namespace std;

template <typename X>
class auto_ptr
{
private:
    X* mptr;

public:
    // Constructors

    //argument list has _a, whose default value is NULL.
    //assigns mptr the valuse _a
    explicit auto_ptr(X* _a = 0) throw()
        : mptr(_a) {}

    //constructing object from another object of auto_ptr type.
    //mptr now points to the object previously owned by _a, and _a
    //now has no responsibility of managing it.
    auto_ptr(auto_ptr& _a) throw()
        : mptr(_a.release()) {}

    //constructing object from another object of auto_ptr type havind diffrent type,
    //type Y must be convertible to type X.
    //mptr now points to the object previously owned by _a, and _a
    //now has no responsibility of managing it.
    template <typename Y>
    auto_ptr(auto_ptr<Y>& _a) throw()
        : mptr(_a.release()) {}

    // Destructor

    //deletes whatever mptr was pointing to.
    ~auto_ptr() throw()
    {
        delete mptr;
    }

    // Access
    //returns pointer this object manages.
    X* get() const throw()
    {
        return mptr;
    }

    //returns value of object managed my this object.
    //crashes if it dosen't manage anything as in that case it
    //will point to nullpointer and it can not be derefrenced.
    X& operator*() const throw()
    {
        //checking if mptr is not null.
        assert(mptr != 0);
        return *mptr;
    }

    //return pointer this object points to.
    X* operator->() const throw()
    {
        //checking if mptr is not null.
        assert(mptr != 0);
        return mptr;
    }

    // Assignment

    //assigning auto_ptr value of another auto_ptr of diffrent type.
    //This object now points to object which was managed by _a.
    //type Y must be convertible to type X.
    //_a now has no responsibility of managing it.
    //The object managed by this object has now been deleted, if any.
    auto_ptr& operator=(auto_ptr& _a) throw()
    {
        reset(_a.release());
        return *this;
    }

    //assigning auto_ptr value of another auto_ptr of same type.
    //This object now points to object which was managed by _a.
    //_a now has no responsibility of managing it.
    //The object managed by this object, if any, has now been deleted.
    template <typename Y>
    auto_ptr& operator=(auto_ptr<Y>& a) throw()
    {
        reset(a.release());
        return *this;
    }

    // Release & Reset
    //This object now no longer manages any pointer, and now
    //points to null. Copy of object owned by this is returned.
    X* release() throw()
    {
        X* temp = mptr;
        mptr = 0;
        return temp;
    }

    //deleted the object managed by this and also assigns value to
    //mptr of function argument _a, defaults to NULL.
    void reset(X* _a = 0) throw()
    {
        if (_a != mptr)
        {
            delete mptr;
            mptr = _a;
        }
    }
};

int main()
{
    std::cout << "Making auto pointer of int type\n";
    //making int pointer.
    int* a = new int(25);

    std::cout << "Before Deletion: " << *a << "\n";

    //making auto_ptr to manage above created pointer a.
    {
        auto_ptr<int> b(a);
    }
    //garbage value should be printed as a has been deleted as object managing it has been deleted.
    std::cout << "After Deletion: " << *a << "\n";

    std::cout << "Making auto pointer from another auto pointer of same type.\n";
    //assigning a new int as old one has been deleted.
    a = new int(50);
    //making auto ptr from a
    auto_ptr<int> b(a);

    std::cout << "Before Deletion: " << *b << "\n";
    std::cout << "Before Deletion(address pointed by b): " << b.get() << "\n";

    //creating a int auto_pointer in below block from a auto_ptr b.
    {
        auto_ptr<int> c(b);
    }
    //garbage value should be printed as a has been deleted as object managing it has been deleted.
    std::cout << "After Deletion: " << *a << "\n";

    //now, b should points to null as after we create a object from a auto_ptr,
    //it no longer manages it and should point to null.
    std::cout << "After Deletion(address pointed by b): " << b.get() << "\n";

    std::cout << "Making auto pointer from another auto pointer of diffrent type.\n";
    //assigning a new int as old one has been deleted.
    a = new int(50);

    //making auto ptr from a
    auto_ptr<int> b1(a);

    std::cout << "Before Deletion: " << *b1 << "\n";
    std::cout << "Before Deletion(address pointed by b): " << b1.get() << "\n";

    //creating a const int pointer in below block from a auto_ptr of type int.
    {
        auto_ptr<const int> c(b1);
    }

    //garbage value should be printed as a has been deleted as object managing it has been deleted.
    std::cout << "After Deletion: " << *a << "\n";

    //now, auto should points to null as after we create a object from a auto_ptr,
    //it no longer manages it and should point to null.
    std::cout << "After Deletion(address pointed by b): " << b1.get() << "\n";
}