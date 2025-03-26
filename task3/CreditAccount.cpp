#include "CreditAccount.h"
#include <stdexcept>

CreditAccount::CreditAccount(const std::string& accId,
                          std::shared_ptr<Client> accOwner,
                          std::shared_ptr<Bank> accBank,
                          double limit,
                          double rate)
    : Account(accId, accOwner, accBank),
      creditLimit(limit),
      commissionRate(rate) {}

void CreditAccount::withdraw(double amount) {
    if (amount <= 0) throw std::invalid_argument("Amount must be positive");
    if (balance - amount < -creditLimit) {
        throw std::runtime_error("Exceeds credit limit");
    }
    balance -= amount;
}

void CreditAccount::applyCommission() {
    if (balance < 0) {
        double commission = -balance * (commissionRate / 100 / 30);
        balance -= commission;
    }
}
