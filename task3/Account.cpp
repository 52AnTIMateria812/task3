#include "Account.h"

Account::Account(const std::string& accId, std::shared_ptr<Client> accOwner, 
               std::shared_ptr<Bank> accBank, AccountType accType)
    : id(accId), balance(0.0), owner(accOwner), bank(accBank), type(accType) {}

void Account::deposit(double amount) {
    if (amount <= 0) throw std::invalid_argument("Amount must be positive");
    balance += amount;
}

void Account::transfer(std::shared_ptr<Account> toAccount, double amount) {
    withdraw(amount);
    toAccount->deposit(amount);
}

double Account::getBalance() const { return balance; }
std::string Account::getId() const { return id; }
AccountType Account::getType() const { return type; }
std::shared_ptr<Client> Account::getOwner() const { return owner; }
std::shared_ptr<Bank> Account::getBank() const { return bank; }

void Account::setBalance(double newBalance) { balance = newBalance; }
