#ifndef DEBIT_ACCOUNT_H
#define DEBIT_ACCOUNT_H

#include "Account.h"

class DebitAccount : public Account {
private:
    double interestRate;
    
public:
    DebitAccount(const std::string& accId, std::shared_ptr<Client> accOwner, 
                std::shared_ptr<Bank> accBank, double rate);
    
    void withdraw(double amount) override;
    void applyInterest();
};

#endif // DEBIT_ACCOUNT_H
