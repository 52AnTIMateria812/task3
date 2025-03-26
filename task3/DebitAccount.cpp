#include "DebitAccount.h"

DebitAccount::DebitAccount(const std::string& accId, 
                         std::shared_ptr<Client> accOwner,
                         std::shared_ptr<Bank> accBank, 
                         double rate)
    : Account(accId, accOwner, accBank), interestRate(rate) {}

void DebitAccount::withdraw(double amount) {
    if (amount <= 0) throw std::invalid_argument("Amount must be positive");
    if (balance < amount) throw std::runtime_error("Insufficient funds");
    balance -= amount;
}

void DebitAccount::applyInterest() {
    balance += balance * (interestRate / 100 / 365);
}
