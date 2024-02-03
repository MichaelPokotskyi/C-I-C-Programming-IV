//// Michael Pokotskyi U09662201
//// pokotskyi.m@gmail.com
//// C I C++ Programming IV CSE-40478
//// Raymond Mitchell IV
//// BigInt.h
//// Win10, Visual C++ 2022, ISO C17
//// Class interface and data members
//
//#include <iostream>
//#include <string>
////#include <iosfwd>
//using namespace std;
//
//namespace Project1 {
//    class BigInt {
//        friend const BigInt operator+(const BigInt&, const BigInt&);
//        friend const BigInt operator-(const BigInt&, const BigInt&);
//        friend bool operator==(const BigInt&, const BigInt&);
//        friend bool operator!=(const BigInt&, const BigInt&);
//        friend bool operator<(const BigInt&, const BigInt&);
//        friend bool operator<=(const BigInt&, const BigInt&);
//        friend bool operator>(const BigInt&, const BigInt&);
//        friend bool operator>=(const BigInt&, const BigInt&);
//        friend ostream& operator<<(ostream&, const BigInt&);
//        friend istream& operator>>(istream&, BigInt&);
//    public: 
//        BigInt();
//        BigInt(const BigInt&);
//        // Throws invalid_argument if string malformed (contains anything other than a legally formatted number)
//        BigInt(long long); 
//        BigInt(const string&);
//        const BigInt& operator=(const BigInt&);
//        const BigInt& operator+=(const BigInt&);
//        const BigInt& operator-=(const BigInt&);
//        BigInt operator-() const; // ??????
//    private: 
//        // You decide what goes here... 
//        string value;
//        char sign;
//    };
//}
