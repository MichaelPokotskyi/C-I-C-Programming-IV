//// Michael Pokotskyi U09662201
//// pokotskyi.m@gmail.com
//// C I C++ Programming IV CSE-40478
//// Raymond Mitchell IV
//// HW8.cpp
//// Win10, Visual C++ 2022, ISO C17
//
//// #8-1
//// Foo t() calling the constructor, not creating the object.
//// To make code compile we need to construct object, here is the changed code:
// 
//#include<iostream>
//struct Foo
//{
//    int i;
//};
//
//int main()
//{
//    //Foo t();
//    Foo t; // constructing object
//    t.i = 7;
//}
//
//// #8-2
//// Output = 7
//// Oject created in main will assigned value, then constructor with parameter will called 
//// and output i value.
//// Here is the changed code:
//
//#include <iostream>
//struct Foo
//{
//    Foo(const Foo&)
//    {
//        std::cout << "bar";
//    }
//    Foo(int i)
//    {
//        std::cout << i;
//    }
//};
//int main()
//{
//    //Foo t = 7;
//    Foo t(7);
//}
//
////#8-3
//// I found 4 changes need to be implemented to make this code const-correct:
//// - make second parameter of the friend function as const, #1
//// - make all functions were called by the object as const, #2
//// - make all functions were called within those functions as const, #3
//// - force_ should be mutable field, #4
//
//#include <cfloat>
//#include <iostream>
//using namespace std;
//
//class Object
//{
//    friend ostream& operator<<(ostream&, const Object&); // #1
//public:
//    Object(double mass, double acceleration)
//        : mass_(mass),
//        acceleration_(acceleration)
//    {
//        clearForce();
//    }
//    double getMass() const // #2
//    {
//        return mass_;
//    }
//    void setMass(double mass)
//    {
//        mass_ = mass;
//        clearForce();
//    }
//    double getAcceleration() const // #2
//    {
//        return acceleration_;
//    }
//    void setAcceleration(double acceleration)
//    {
//        acceleration_ = acceleration;
//        clearForce();
//    }
//    double getForce() const // #2
//    {
//        if (!isForceComputed())
//            computeForce();
//        return force_;
//    }
//private:
//    void computeForce() const // #2
//    {
//        force_ = mass_ * acceleration_;
//    }
//    void clearForce()
//    {
//        force_ = DBL_MIN;
//    }
//    bool isForceComputed() const // #2
//    {
//        return force_ != DBL_MIN;
//    }
//    double mass_; // Grams
//    double acceleration_; // Meters per second squared
//    mutable double force_; // Newtons // #4
//};
//ostream& operator<<(ostream& out, const Object& obj) // #1
//{
//    return out << obj.getMass() << "g, "
//        << obj.getAcceleration() << "m / s^2, "
//        << obj.getForce() << "N";
//}
//int main()
//{
//    Object obj(12, 150);
//    cout << obj << "\n";
//
//    const Object cobj(7, 275);
//    cout << cobj << "\n";
//}