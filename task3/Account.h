#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <memory>
#include <stdexcept>

class Client;
class Bank;

class Account {
protected:
    std::string id;
    double balance;
    std::shared_ptr<Client> owner;
    std::shared_ptr<Bank> bank;

public:
    Account(const std::string& accId, std::shared_ptr<Client> accOwner, 
           std::shared_ptr<Bank> accBank);
    virtual ~Account() = default;
    
    virtual void deposit(double amount);
    virtual void withdraw(double amount) = 0;
    virtual void transfer(std::shared_ptr<Account> toAccount, double amount);
    
    double getBalance() const;
    std::string getId() const;
    std::shared_ptr<Client> getOwner() const;
    std::shared_ptr<Bank> getBank() const;
    
protected:
    void setBalance(double newBalance);
};
#endif
