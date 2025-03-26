#include "CentralBank.h"
#include "Bank.h"
#include "Account.h"

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
