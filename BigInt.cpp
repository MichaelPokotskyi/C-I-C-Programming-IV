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
#include <climits>
#include <cmath>
#include <tuple>

namespace Project1 {
    // ----------------------------------------------
    //              HELPER FUNCTIONS
    // ----------------------------------------------
    bool is_valid_num(const std::string& num) {
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

    void add_leading_zeroes(std::string& num, size_t num_zeroes) {
        num = std::string(num_zeroes, '0') + num;
    }

    std::tuple<std::string, std::string> get_larger_and_smaller(const std::string& num1,
                                                                const std::string& num2) {
        std::string larger, smaller;
        if (num1.size() > num2.size() or
           (num1.size() == num2.size() and 
            num1 > num2)) {
            larger = num1;
            smaller = num2;
        }
        else {
            larger = num2;
            smaller = num1;
        }

        // pad the smaller number with zeroes
        add_leading_zeroes(smaller, larger.size() - smaller.size());

        return std::make_tuple(larger, smaller);
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
            if (is_valid_num(magnitude)) {
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
            if (is_valid_num(num)) {
                value = num;
                sign = '+';    // positive by default
            }
            else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        strip_leading_zeroes(value);
    }

    // ----------------------------------------------
    //                  IO streams
    // ----------------------------------------------

    std::ostream& operator << (std::ostream& cout, const BigInt& a) {
        if (a.sign == '-') {
            cout << a.sign;
        }
        cout << a.value;
        return cout;
    }

    std::istream& operator>>(std::istream& in, BigInt& num) {
        std::string input;
        in >> input;
        num = BigInt(input);  // remove sign from value and set sign, if exists
        return in;
    }

    // ----------------------------------------------
    //                 RELATIONAL
    // ----------------------------------------------

    bool operator==(const BigInt& num, const BigInt& num1) {
        return (num.sign == num1.sign) and (num.value == num1.value);
    }

    bool operator!=(const BigInt& num, const BigInt& num1) {
        return !(num == num1);
    }

    bool operator<(const BigInt& num, const BigInt& num1) {
        if (num.sign == num1.sign) {
            if (num.sign == '+') {
                if (num.value.length() == num1.value.length())
                    return num.value < num1.value;
                else
                    return num.value.length() < num1.value.length();
            }
            else
                return num.value > num1.value;
        }
        else
            return num.sign == '-';

    }

    bool operator<=(const BigInt& num, const BigInt& num1) {
        return (num < num1) or (num == num1);
    }

    bool operator>(const BigInt& num, const BigInt& num1) {
        return !((num < num1) or (num == num1));
    }

    bool operator>=(const BigInt& num, const BigInt& num1) {
        return !(num < num1);
    }

    // ----------------------------------------------
    //              BINARY ARITHMETIC
    // ----------------------------------------------

    //const BigInt operator+(const BigInt& num, const BigInt& num1) {
    //    // if the operands are of opposite signs, perform subtraction
    //    if (num.sign == '+' and num1.sign == '-') {
    //        BigInt rhs = num1;
    //        rhs.sign = '+';
    //        return num - rhs;
    //    }
    //    else if (num.sign == '-' and num1.sign == '+') {
    //        BigInt lhs = num;
    //        lhs.sign = '+';
    //        return -(lhs - num1);
    //    }

    //    // identify the numbers as `larger` and `smaller`
    //    std::string larger, smaller;
    //    std::tie(larger, smaller) = get_larger_and_smaller(num.value, num1.value);

    //    BigInt result;      // the resultant sum
    //    result.value = "";  // the value is cleared as the digits will be appended
    //    short carry = 0, sum;
    //    // add the two values
    //    for (long i = larger.size() - 1; i >= 0; i--) {
    //        sum = larger[i] - '0' + smaller[i] - '0' + carry;
    //        result.value = std::to_string(sum % 10) + result.value;
    //        carry = sum / (short)10;
    //    }
    //    if (carry)
    //        result.value = std::to_string(carry) + result.value;

    //    // if the operands are negative, the result is negative
    //    if (num.sign == '-' and result.value != "0")
    //        result.sign = '-';

    //    return result;
    //}

    //const BigInt operator-(const BigInt& num, const BigInt& num1) {
    //    // if the operands are of opposite signs, perform addition
    //    if (this->sign == '+' and num.sign == '-') {
    //        BigInt rhs = num;
    //        rhs.sign = '+';
    //        return *this + rhs;
    //    }
    //    else if (this->sign == '-' and num.sign == '+') {
    //        BigInt lhs = *this;
    //        lhs.sign = '+';
    //        return -(lhs + num);
    //    }

    //    BigInt result;      // the resultant difference
    //    // identify the numbers as `larger` and `smaller`
    //    std::string larger, smaller;
    //    if (abs(*this) > abs(num)) {
    //        larger = this->value;
    //        smaller = num.value;

    //        if (this->sign == '-')      // -larger - -smaller = -result
    //            result.sign = '-';
    //    }
    //    else {
    //        larger = num.value;
    //        smaller = this->value;

    //        if (num.sign == '+')        // smaller - larger = -result
    //            result.sign = '-';
    //    }
    //    // pad the smaller number with zeroes
    //    add_leading_zeroes(smaller, larger.size() - smaller.size());

    //    result.value = "";  // the value is cleared as the digits will be appended
    //    short difference;
    //    long i, j;
    //    // subtract the two values
    //    for (i = larger.size() - 1; i >= 0; i--) {
    //        difference = larger[i] - smaller[i];
    //        if (difference < 0) {
    //            for (j = i - 1; j >= 0; j--) {
    //                if (larger[j] != '0') {
    //                    larger[j]--;    // borrow from the j-th digit
    //                    break;
    //                }
    //            }
    //            j++;
    //            while (j != i) {
    //                larger[j] = '9';    // add the borrow and take away 1
    //                j++;
    //            }
    //            difference += 10;   // add the borrow
    //        }
    //        result.value = std::to_string(difference) + result.value;
    //    }
    //    strip_leading_zeroes(result.value);

    //    // if the result is 0, set its sign as +
    //    if (result.value == "0")
    //        result.sign = '+';

    //    return result;
    //}
};