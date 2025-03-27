#ifndef CREDIT_ACCOUNT_H
#define CREDIT_ACCOUNT_H

#include "Account.h"

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
    
    void withdraw(double amount) override;
    void applyCommission();
};
#endif
