#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <string>

class CentralBank;
class Client;
class Account;

class Bank : public std::enable_shared_from_this<Bank> {
private:
    std::string name;
    std::vector<std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<Account>> accounts;
    std::shared_ptr<CentralBank> centralBank;
    
    double debitInterestRate;
    double creditCommissionRate;
    double creditLimit;
    
    std::string generateAccountId();
    
public:
    Bank(const std::string& bankName, std::shared_ptr<CentralBank> cb);
    
    std::shared_ptr<Client> registerClient(const std::string& firstName, 
                                         const std::string& lastName);
    std::shared_ptr<Account> createAccount(AccountType type, 
                                         std::shared_ptr<Client> client,
                                         double initialAmount = 0.0);
};

#endif // BANK_H
