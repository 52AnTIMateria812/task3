#ifndef CREDIT_ACCOUNT_H
#define CREDIT_ACCOUNT_H

#include "Account.h"

// Кредитный счет с лимитом и комиссией
class CreditAccount : public Account {
private:
    double creditLimit;
    double commissionRate;

public:
    CreditAccount(const std::string& accId,
                std::shared_ptr<Client> accOwner,
                std::shared_ptr<Bank> accBank,
                double limit,
                double rate);

    // Разрешаем уходить в минус в пределах лимита
    void withdraw(double amount) override;
    
    // Начисление комиссии на отрицательный баланс
    void applyCommission();
};

#endif // CREDIT_ACCOUNT_H
