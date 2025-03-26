#ifndef DEPOSIT_ACCOUNT_H
#define DEPOSIT_ACCOUNT_H

#include "Account.h"
#include <ctime>

// Депозитный счет с ограниченным доступом до даты окончания
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

    // Запрещаем снятие до окончания срока депозита
    void withdraw(double amount) override;
    
    // Начисление процентов
    void applyInterest();
    
    // Проверка истек ли срок депозита
    bool isExpired() const;
};

#endif // DEPOSIT_ACCOUNT_H
