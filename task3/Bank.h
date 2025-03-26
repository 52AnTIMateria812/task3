#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <string>
#include <ctime>

class Client;
class Account;

class Bank : public std::enable_shared_from_this<Bank> {
private:
    std::string name;
    std::vector<std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<Account>> accounts;
    
    // Параметры банка
    double debitInterestRate;
    std::map<double, double> depositInterestRates; // сумма -> ставка
    double creditCommissionRate;
    double creditLimit;

    std::string generateAccountId();

public:
    explicit Bank(const std::string& bankName);
    
    // Управление клиентами
    std::shared_ptr<Client> registerClient(const std::string& firstName,
                                         const std::string& lastName);
    
    // Создание счетов разных типов
    std::shared_ptr<Account> createDebitAccount(std::shared_ptr<Client> client,
                                             double initialAmount = 0.0);
                                             
    std::shared_ptr<Account> createDepositAccount(std::shared_ptr<Client> client,
                                               double initialAmount,
                                               time_t expirationDate);
                                               
    std::shared_ptr<Account> createCreditAccount(std::shared_ptr<Client> client,
                                              double initialAmount = 0.0);
    
    // Начисление процентов/комиссий
    void processDailyPayments();
};

#endif 
// BANK_H
