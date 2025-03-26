#include "Bank.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"

Bank::Bank(const std::string& bankName, std::shared_ptr<CentralBank> cb)
    : name(bankName), centralBank(cb), debitInterestRate(3.0),
      creditCommissionRate(1.0), creditLimit(10000.0) {}

std::shared_ptr<Client> Bank::registerClient(const std::string& firstName, 
                                          const std::string& lastName) {
    auto client = std::make_shared<Client>(firstName, lastName);
    clients.push_back(client);
    return client;
}

std::shared_ptr<Account> Bank::createAccount(AccountType type, 
                                           std::shared_ptr<Client> client,
                                           double initialAmount) {
    std::string accountId = generateAccountId();
    std::shared_ptr<Account> account;

    switch (type) {
        case AccountType::DEBIT:
            account = std::make_shared<DebitAccount>(accountId, client, 
                                                   shared_from_this(), debitInterestRate);
            break;
        // Реализации для других типов счетов аналогичны
        default:
            throw std::invalid_argument("Unknown account type");
    }

    if (initialAmount > 0) {
        account->deposit(initialAmount);
    }

    accounts.push_back(account);
    client->addAccount(account);
    return account;
}

std::string Bank::generateAccountId() {
    static int counter = 0;
    return name + "-ACC-" + std::to_string(++counter);
}
