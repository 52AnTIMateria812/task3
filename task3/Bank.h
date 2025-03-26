#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <ctime>

class Client;
class Account;

class Bank : public std::enable_shared_from_this<Bank> {
private:
    std::string name;
    std::vector<std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<Account>> accounts;
    
    double debitInterestRate;
    std::map<double, double> depositInterestRates;
    double creditCommissionRate;
    double creditLimit;

    std::string generateAccountId();
    double getDepositRate(double amount) const;

public:
    explicit Bank(const std::string& bankName);
    
    std::shared_ptr<Client> registerClient(const std::string& firstName,
                                         const std::string& lastName);
    
    std::shared_ptr<Account> createDebitAccount(std::shared_ptr<Client> client,
                                             double initialAmount = 0.0);
                                             
    std::shared_ptr<Account> createDepositAccount(std::shared_ptr<Client> client,
                                               double initialAmount,
                                               time_t expirationDate);
                                               
    std::shared_ptr<Account> createCreditAccount(std::shared_ptr<Client> client,
                                              double initialAmount = 0.0);
    
    void processDailyPayments();
};
#endif
