
// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// CheckingAccount.cpp
// Win10, Visual C++ 2022, ISO C17
// Minimizing Compile-time Dependencies
// CheckingAccount.cpp

#include "CheckingAccount.h"
#include <vector>
#include <list>

struct CheckingAccount::CheckingAccountImpl {
    long accountNumber_;
    double balance;
    std::string firstName;
    std::string lastName;
    std::vector<double> deposits_;
    std::vector<double> withdrawals_;
    std::list<Check> checks_;
};