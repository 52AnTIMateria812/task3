#ifndef DEPOSIT_ACCOUNT_H
#define DEPOSIT_ACCOUNT_H

#include "Account.h"
#include <ctime>

class DepositAccount : public Account {
private:
    double interestRate;
    time_t expirationDate;

public:
    DepositAccount(const std::string& accId, 
                 std::shared_ptr<Client> accOwner,
                 std::shared_ptr<Bank> accBank,
                 double rate, 
                 time_t expDate);
    
    void withdraw(double amount) override;
    void applyInterest();
    bool isExpired() const;
};
#endif
