#include <iostream>
#include <string>
#include <iosfwd>
using namespace std;

namespace Project1 {
    class BigInt {
        /*friend const BigInt operator+(const BigInt&, const BigInt&);
        friend const BigInt operator-(const BigInt&, const BigInt&);
        friend bool operator==(const BigInt&, const BigInt&);
        friend bool operator!=(const BigInt&, const BigInt&);
        friend bool operator<(const BigInt&, const BigInt&);
        friend bool operator<=(const BigInt&, const BigInt&);
        friend bool operator>(const BigInt&, const BigInt&);
        friend bool operator>=(const BigInt&, const BigInt&);*/
        friend std::ostream& operator<<(std::ostream&, const BigInt&);
        // friend istream& operator>>(istream&, BigInt&);
    public: 
        BigInt();
        BigInt(const BigInt&);
        // Throws invalid_argument if string malformed (contains anything other than a legally formatted number) 
        BigInt(long long); 
        BigInt(const string&);
        //const BigInt& operator=(const BigInt&);
        //const BigInt& operator+=(const BigInt&);
        //const BigInt& operator-=(const BigInt&);
    private: 
        std::string value;
        char sign;
        // You decide what goes here... 
    };
}
