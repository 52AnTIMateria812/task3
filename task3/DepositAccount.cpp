#include "DepositAccount.h"
#include <ctime>
#include <stdexcept>

DepositAccount::DepositAccount(const std::string& accId, 
                             std::shared_ptr<Client> accOwner,
                             std::shared_ptr<Bank> accBank,
                             double rate, 
                             time_t expDate)
    : Account(accId, accOwner, accBank), 
      interestRate(rate), 
      expirationDate(expDate) {}

void DepositAccount::withdraw(double amount) {
    if (!isExpired()) {
        throw std::runtime_error("Cannot withdraw from deposit account before expiration");
    }
    Account::withdraw(amount);
}

void DepositAccount::applyInterest() {
    balance += balance * (interestRate / 100 / 365);
}

bool DepositAccount::isExpired() const {
    return std::time(nullptr) >= expirationDate;
}
