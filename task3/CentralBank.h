#ifndef CENTRAL_BANK_H
#define CENTRAL_BANK_H

#include <vector>
#include <memory>

class Bank;
class Account;

class CentralBank {
private:
    std::vector<std::shared_ptr<Bank>> banks;
    
public:
    void registerBank(std::shared_ptr<Bank> bank);
    void processInterbankTransfer(std::shared_ptr<Account> from, 
                                std::shared_ptr<Account> to, 
                                double amount);
};

#endif // CENTRAL_BANK_H
