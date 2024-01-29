// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// BigInt.cpp
// Win10, Visual C++ 2022, ISO C17
// Class implementation

#include "BigInt.h"
#include <iostream>
#include <iosfwd>
#include <string>

namespace Project1 {
    // ----------------------------------------------
    //              HELPER FUNCTIONS
    // ----------------------------------------------
    bool is_valid_number(const std::string& num) {
        for (char digit : num)
            if (digit < '0' or digit > '9')
                return false;
        return true;
    }

    void strip_leading_zeroes(std::string& num) {
        size_t i;
        for (i = 0; i < num.size(); i++)
            if (num[i] != '0')
                break;
        if (i == num.size())
            num = "0";
        else
            num = num.substr(i);
    }

    // ----------------------------------------------
    //                 CONSTRUCTORS
    // ----------------------------------------------

    BigInt::BigInt() {
        value = "0";
        sign = '+';
    }

    BigInt::BigInt(const BigInt& num) {
        value = num.value;
        sign = num.sign;
    }

    BigInt::BigInt(long long num) {
        value = std::to_string(std::abs(num));
        if (num < 0)
            sign = '-';
        else
            sign = '+';
    }

    BigInt::BigInt(const std::string& num) {
        if (num[0] == '+' or num[0] == '-') {     // check for sign
            std::string magnitude = num.substr(1);
            if (is_valid_number(magnitude)) {
                value = magnitude;
                if (value == "0") {
                    sign = '+';
                }
                else {
                    sign = num[0];
                }
            }
            else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        else {      // if no sign is specified
            if (is_valid_number(num)) {
                value = num;
                sign = '+';    // positive by default
            }
            else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        strip_leading_zeroes(value);
    }

    std::ostream& operator << (std::ostream& cout, const BigInt& a) {
        if (a.sign == '-') {
            cout << a.sign;
        }
        cout << a.value;
        return cout;
    }


};