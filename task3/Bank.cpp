#include "Bank.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"

Bank::Bank(const std::string& bankName) 
    : name(bankName), 
      debitInterestRate(3.0),
      creditCommissionRate(1.0), 
      creditLimit(10000.0) {
    depositInterestRates = {
        {1000.0, 3.0},
        {5000.0, 3.5},
        {10000.0, 4.0}
    };
}

std::shared_ptr<Client> Bank::registerClient(const std::string& firstName, 
                                          const std::string& lastName) {
    auto client = std::make_shared<Client>(firstName, lastName);
    clients.push_back(client);
    return client;
}

std::shared_ptr<Account> Bank::createDebitAccount(std::shared_ptr<Client> client,
                                               double initialAmount) {
    auto account = std::make_shared<DebitAccount>(
        generateAccountId(), client, shared_from_this(), debitInterestRate);
    if (initialAmount > 0) account->deposit(initialAmount);
    accounts.push_back(account);
    client->addAccount(account);
    return account;
}

std::shared_ptr<Account> Bank::createDepositAccount(std::shared_ptr<Client> client,
                                                 double initialAmount,
                                                 time_t expirationDate) {
    double rate = getDepositRate(initialAmount);
    auto account = std::make_shared<DepositAccount>(
        generateAccountId(), client, shared_from_this(), rate, expirationDate);
    account->deposit(initialAmount);
    accounts.push_back(account);
    client->addAccount(account);
    return account;
}

std::shared_ptr<Account> Bank::createCreditAccount(std::shared_ptr<Client> client,
                                                double initialAmount) {
    auto account = std::make_shared<CreditAccount>(
        generateAccountId(), client, shared_from_this(), creditLimit, creditCommissionRate);
    if (initialAmount > 0) account->deposit(initialAmount);
    accounts.push_back(account);
    client->addAccount(account);
    return account;
}

void Bank::processDailyPayments() {
    for (auto& account : accounts) {
        if (auto debit = std::dynamic_pointer_cast<DebitAccount>(account)) {
            debit->applyInterest();
        }
        else if (auto deposit = std::dynamic_pointer_cast<DepositAccount>(account)) {
            deposit->applyInterest();
        }
        else if (auto credit = std::dynamic_pointer_cast<CreditAccount>(account)) {
            credit->applyCommission();
        }
    }
}

std::string Bank::generateAccountId() {
    static int counter = 0;
    return name + "-ACC-" + std::to_string(++counter);
}

double Bank::getDepositRate(double amount) const {
    for (auto it = depositInterestRates.rbegin(); it != depositInterestRates.rend(); ++it) {
        if (amount >= it->first) {
            return it->second;
        }
    }
    return 0.0;
}
