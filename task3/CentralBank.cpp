#include "CentralBank.h"
#include "Bank.h"
#include "Account.h"

std::shared_ptr<CentralBank> CentralBank::instance = nullptr;

std::shared_ptr<CentralBank> CentralBank::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<CentralBank>(new CentralBank());
    }
    return instance;
}

void CentralBank::registerBank(std::shared_ptr<Bank> bank) {
    banks.push_back(bank);
}

void CentralBank::processInterbankTransfer(std::shared_ptr<Account> from, 
                                        std::shared_ptr<Account> to, 
                                        double amount) {
    if (from->getBank() == to->getBank()) {
        throw std::runtime_error("Accounts are in the same bank");
    }
    from->withdraw(amount);
    to->deposit(amount);
}
