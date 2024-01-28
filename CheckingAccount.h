
// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// CheckingAccount.h
// Win10, Visual C++ 2022, ISO C17
// Minimizing Compile-time Dependencies
// CheckingAccount.h

// include guard
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

// Only include the necessary header for string usage
#include <string>
// #include <iosfwd> // M

// Forward declarations for classes used in the class definition

class AccountExceptions;
class BankAccount;
class Check;

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(long accountNumber,
                    double initialBalance, 
                    const std::string& firstName, 
                    const std::string& lastName);
    double getBalance() const;
    void depositCheck(const Check& check);
    void depositCash(double amount);
    void withdrawCash(double amount);
    virtual std::ostream& print(std::ostream&) const;

protected:
    void processAccount();

private:
    struct CheckingAccountImpl;
    CheckingAccountImpl* pimpl_;
};

std::ostream& operator<<(std::ostream&, const CheckingAccount&);

#endif // CHECKINGACCOUNT_H