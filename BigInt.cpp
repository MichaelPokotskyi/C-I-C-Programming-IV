// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// BigInt.cpp
// Win10, Visual C++ 2022, ISO C17
// Class implementation

#include "BigInt.h"
#include <algorithm>
using namespace std;

namespace Project1 {
    // ----------------------------------------------
    //              HELPER FUNCTIONS
    // ----------------------------------------------

    bool is_valid_num(const string& num) {
        for (char digit : num) {
                if (digit < '0' or digit > '9')
                    return false;
        }
        return true;
    }

    void strip_lead_zero(string& num) {
        size_t i;
        for (i = 0; i < num.size(); i++)
        {
            if (num[i] != '0') {
                break;
            }
        }
        if (i == num.size()) {
            num = "0";
        }
        else {
            num = num.substr(i);
        }
    }

    void add_lead_zero(string& num, size_t num_zeroes) {
        num = string(num_zeroes, '0') + num;
    }

    BigInt abs_(const BigInt& num) {
        if (num < 0) {
            return -num;
        }
        else {
            return num;
        }
    }

    BigInt BigInt::operator-() const {
        BigInt temp;
        temp.value = value;
        if (value != "0") {
            if (sign == '+') {
                temp.sign = '-';
            }
            else {
                temp.sign = '+';
            }
        }
        return temp;
    }

    // ----------------------------------------------
    //                 CONSTRUCTORS
    // ----------------------------------------------

    BigInt::BigInt() : value ("0"), sign ('+') {
    }

    BigInt::BigInt(const BigInt& num) : value (num.value), sign (num.sign) {
    }

    BigInt::BigInt(long long num) : value (to_string(abs(num))) {
        if (num < 0) {
            sign = '-';
        }
        else {
            sign = '+';
        }
    }

    BigInt::BigInt(const string& num) {
        // testing cases
        if (num == "" || num == "-" || num == "00") {
            throw invalid_argument("Expected integer, but have instead " + num + "\n");
        }
        if (num[0] == '+' || num[0] == '-') {     // check for sign
            string number = num.substr(1);
            if (is_valid_num(number)) {
                value = number;
                if (num[0] == '-' && number == "0") {
                    sign = '+';
                }
                else {
                    sign = num[0];
                }
            }
            else {
                throw invalid_argument("Expected integer, but have instead " + num + "\n");
            }
        }
        else {
            // if no sign
            if (is_valid_num(num)) {
                value = num;
                sign = '+';    // positive by default
            }
            else {
                throw invalid_argument("Expected integer, but have instead " + num + "\n");
            }
        }
        strip_lead_zero(value);
    }

    // ----------------------------------------------
    //                  IO streams
    // ----------------------------------------------

    ostream& operator << (ostream& cout, const BigInt& a) {
        if (a.sign == '-') {
            cout << a.sign;
        }
        cout << a.value;
        return cout;
    }

    istream& operator>>(istream& in, BigInt& num) {
        string input;
        in >> input;
        num = BigInt(input);
        return in;
    }

    // ----------------------------------------------
    //                 RELATIONAL
    // ----------------------------------------------

    bool operator==(const BigInt& num, const BigInt& num1) {
        if (num.sign == num1.sign && num.value == num1.value) {
            return true;
        }
        return false;
    }

    bool operator!=(const BigInt& num, const BigInt& num1) {
        if (num == num1) {
            return false;
        }
        return true;
    }

    bool operator<(const BigInt& num, const BigInt& num1) {
        if (num.sign == num1.sign) {
            if (num.sign == '+') {
                if (num.value.length() == num1.value.length()) {
                    return num.value < num1.value;
                }
                else {
                    return num.value.length() < num1.value.length();
                }
            }
            else {
                return num.value > num1.value;
            }
        }
        else {
            return num.sign == '-';
        }
    }

    bool operator<=(const BigInt& num, const BigInt& num1) {
        if (num < num1 || num == num1) {
            return true;
        }
        return false;
    }

    bool operator>(const BigInt& num, const BigInt& num1) {
        if (!(num < num1 || num == num1)) {
            return true;
        }
        return false;
    }

    bool operator>=(const BigInt& num, const BigInt& num1) {
        if (!(num < num1)) {
            return true;
        }
        return false;
    }

    // ----------------------------------------------
    //              BINARY ARITHMETIC
    // ----------------------------------------------

    const BigInt operator+(const BigInt& num, const BigInt& num1) {
        if (num.sign == '+' && num1.sign == '-') {
            BigInt rhs = num1;
            rhs.sign = '+';
            return num - rhs;
        }
        else if (num.sign == '-' && num1.sign == '+') {
            BigInt lhs = num;
            lhs.sign = '+';
            return -(lhs - num1); // -(lhs - num);
        }
        // get larger and smaller
        string larger = num.value, smaller = num1.value;
        if (abs_(num) < abs_(num1)) {
            smaller.swap(larger);
        }
        // add zeros to smaller number
        add_lead_zero(smaller, larger.size() - smaller.size());
        BigInt result;
        result.value = "";
        short carry = 0, sum;
        for (long i = (long)larger.size() - 1; i >= 0; i--) {
            sum = larger[i] - '0' + smaller[i] - '0' + carry;
            result.value = to_string(sum % 10) + result.value;
            carry = sum / (short)10;
        }
        if (carry) {
            result.value = to_string(carry) + result.value;
        }
        // if the operands are negative, result is also negative
        if (num.sign == '-' && result.value != "0") {
            result.sign = '-';
        }
        return result;
    }

    const BigInt operator-(const BigInt& num, const BigInt& num1) {
        // if the operands are of opposite signs, perform addition
        if (num.sign == '+' && num1.sign == '-') {
            BigInt rhs = num1;
            rhs.sign = '+';
            return num + rhs;
        }
        else if (num.sign == '-' && num1.sign == '+') {
            BigInt lhs = num;
            lhs.sign = '+';
            return -(lhs + num1);
        }
        BigInt result;
        // get larger and smaller
        string larger = num.value, smaller = num1.value;
        if (abs_(num) > abs_(num1) && num.sign == '-') {
                result.sign = '-';
        }
        if (abs_(num) < abs_(num1)) {
            smaller.swap(larger);
            if (num1.sign == '+') {
                result.sign = '-';
            }
        }
        // add zeros to smaller number
        add_lead_zero(smaller, larger.size() - smaller.size());
        result.value = "";
        short dif;
        long i, j;
        // subtraction
        for (i = (long)larger.size() - 1; i >= 0; i--) {
            dif = larger[i] - smaller[i];
            if (dif < 0) {
                for (j = i - 1; j >= 0; j--) {
                    if (larger[j] != '0') {
                        larger[j]--;
                        break;
                    }
                }
                j++;
                while (j != i) {
                    larger[j] = '9';
                    j++;
                }
                dif += 10;
            }
            result.value = to_string(dif) + result.value;
        }
        strip_lead_zero(result.value);
        // if the result is zer0 set +
        if (result.value == "0") {
            result.sign = '+';
        }
        return result;
    }

    // ----------------------------------------------
    //                  ASSIGNMENT
    // ----------------------------------------------

    const BigInt& BigInt::operator=(const BigInt& num) {
        value = num.value;
        sign = num.sign;
        return *this;
    }

    const BigInt& BigInt::operator-=(const BigInt& num) {
        *this = *this - num;
        return *this;
    }

    const BigInt& BigInt::operator+=(const BigInt& num) {
        *this = *this + num;
        return *this;
    }
};