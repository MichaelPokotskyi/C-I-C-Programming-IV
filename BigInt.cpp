// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// BigInt.cpp
// Win10, Visual C++ 2022, ISO C17
// Class implementation

#include "BigInt.h"
#include <tuple>
using namespace std;

namespace Project1 {
    // ----------------------------------------------
    //              HELPER FUNCTIONS
    // ----------------------------------------------

    bool is_valid_num(const string& num) {
        for (char digit : num)
            if (digit < '0' or digit > '9')
                return false;
        return true;
    }

    void strip_leading_zeroes(string& num) {
        size_t i;
        for (i = 0; i < num.size(); i++)
            if (num[i] != '0')
                break;
        if (i == num.size())
            num = "0";
        else
            num = num.substr(i);
    }

    void add_leading_zeroes(string& num, size_t num_zeroes) {
        num = string(num_zeroes, '0') + num;
    }

    const tuple<string, string> get_larger_and_smaller(const string& num1,
        const string& num2) {
        string larger, smaller;
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

        return make_tuple(larger, smaller);
    }

    BigInt abs_(const BigInt& num) {
        return num < 0 ? -num : num;
    }

    BigInt BigInt::operator-() const {
        BigInt temp;

        temp.value = value;
        if (value != "0") {
            if (sign == '+')
                temp.sign = '-';
            else
                temp.sign = '+';
        }

        return temp;
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
        value = to_string(abs(num));
        if (num < 0)
            sign = '-';
        else
            sign = '+';
    }

    BigInt::BigInt(const string& num) {
        if (num[0] == '+' or num[0] == '-') {     // check for sign
            string magnitude = num.substr(1);
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
                throw invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        else {      // if no sign is specified
            if (is_valid_num(num)) {
                value = num;
                sign = '+';    // positive by default
            }
            else {
                throw invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        strip_leading_zeroes(value);
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

    const BigInt operator+(const BigInt& num, const BigInt& num1) {
        if (num.sign == '+' and num1.sign == '-') {
            BigInt rhs = num1;
            rhs.sign = '+';
            return num - rhs;
        }
        else if (num.sign == '-' and num1.sign == '+') {
            BigInt lhs = num;
            lhs.sign = '+';
            return -(lhs - num1); // -(lhs - num);
        }
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(num.value, num1.value);

        BigInt result;      // the resultant sum
        result.value = "";  // the value is cleared as the digits will be appended
        short carry = 0, sum;
        // add the two values
        for (long i = larger.size() - 1; i >= 0; i--) {
            sum = larger[i] - '0' + smaller[i] - '0' + carry;
            result.value = std::to_string(sum % 10) + result.value;
            carry = sum / (short)10;
        }
        if (carry)
            result.value = std::to_string(carry) + result.value;

        // if the operands are negative, the result is negative
        if (num.sign == '-' and result.value != "0")
            result.sign = '-';
        return result;
    }

    const BigInt operator-(const BigInt& num, const BigInt& num1) {
        // if the operands are of opposite signs, perform addition
        if (num.sign == '+' and num1.sign == '-') {
            BigInt rhs = num1;
            rhs.sign = '+';
            return num + rhs;
        }
        else if (num.sign == '-' and num1.sign == '+') {
            BigInt lhs = num;
            lhs.sign = '+';
            return -(lhs + num1);
        }

        BigInt result;      // the resultant difference
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        if (abs_(num) > abs_(num1)) {
            larger = num.value;
            smaller = num1.value;

            if (num.sign == '-')      // -larger - -smaller = -result
                result.sign = '-';
        }
        else {
            larger = num1.value;
            smaller = num.value;

            if (num1.sign == '+')        // smaller - larger = -result
                result.sign = '-';
        }
        // pad the smaller number with zeroes
        add_leading_zeroes(smaller, larger.size() - smaller.size());

        result.value = "";  // the value is cleared as the digits will be appended
        short difference;
        long i, j;
        // subtract the two values
        for (i = larger.size() - 1; i >= 0; i--) {
            difference = larger[i] - smaller[i];
            if (difference < 0) {
                for (j = i - 1; j >= 0; j--) {
                    if (larger[j] != '0') {
                        larger[j]--;    // borrow from the j-th digit
                        break;
                    }
                }
                j++;
                while (j != i) {
                    larger[j] = '9';    // add the borrow and take away 1
                    j++;
                }
                difference += 10;   // add the borrow
            }
            result.value = std::to_string(difference) + result.value;
        }
        strip_leading_zeroes(result.value);

        // if the result is 0, set its sign as +
        if (result.value == "0")
            result.sign = '+';

        return result;
    }

    // ----------------------------------------------
    //                  ASSIGNMENT
    // ----------------------------------------------

    const BigInt& BigInt::operator=(const BigInt& num)
    {
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