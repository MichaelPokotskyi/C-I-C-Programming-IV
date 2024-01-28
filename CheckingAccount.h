// Michael Pokotskyi U09662201
// pokotskyi.m@gmail.com
// C I C++ Programming IV CSE-40478
// Raymond Mitchell IV
// CheckingAccount.h
// Win10, Visual C++ 2022, ISO C17
// Minimizing Compile-time Dependencies
// CheckingAccount.h

// Include guard
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

// Only necessary headers for string and ostream use
#include <string>
#include <iosfwd>

// FWD declarations for classes
class AccountExceptions;
class BankAccount;
class Check;

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(long accountNumber,
                    double initialBalance, 
                    const std::string& firstName,
                    const std::string& lastName);
    ~CheckingAccount();
    double getBalance() const;
    void depositCheck(const Check&);
    void depositCash(double);
    void withdrawCash(double);
    virtual std::ostream& print(std::ostream&) const;

protected:
    void processAccount();

private:
    struct CheckingAccountImpl;
    CheckingAccountImpl* pimpl_;
};

std::ostream& operator<<(std::ostream&, const CheckingAccount&);

#endif // CHECKINGACCOUNT_H