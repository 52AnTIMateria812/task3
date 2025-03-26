#include <iostream>
#include <memory>
#include <ctime>
#include "Client.h"
#include "Bank.h"
#include "CentralBank.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"

int main() {
    try {
        // 1. Инициализация банковской системы
        auto centralBank = CentralBank::getInstance();
        
        // 2. Создание банков
        auto bank1 = std::make_shared<Bank>("Alpha Bank");
        auto bank2 = std::make_shared<Bank>("Beta Bank");
        
        centralBank->registerBank(bank1);
        centralBank->registerBank(bank2);
        
        // 3. Регистрация клиентов
        auto client1 = bank1->registerClient("John", "Doe");
        client1->setPassportData("1234 567890");
        client1->setAddress("Moscow, Red Square 1");
        
        auto client2 = bank2->registerClient("Jane", "Smith");
        
        // 4. Создание счетов разных типов
        auto debitAccount = bank1->createDebitAccount(client1, 1000.0);
        
        time_t expiration = time(nullptr) + 30*24*60*60; // +30 дней
        auto depositAccount = bank1->createDepositAccount(client1, 5000.0, expiration);
        
        auto creditAccount = bank2->createCreditAccount(client2, 0.0);
        
        // 5. Выполнение операций
        std::cout << "Initial balances:\n";
        std::cout << "Debit: " << debitAccount->getBalance() << "\n";
        std::cout << "Deposit: " << depositAccount->getBalance() << "\n";
        std::cout << "Credit: " << creditAccount->getBalance() << "\n\n";
        
        debitAccount->transfer(depositAccount, 300.0);
        
        std::cout << "After transfer 300 from debit to deposit:\n";
        std::cout << "Debit: " << debitAccount->getBalance() << "\n";
        std::cout << "Deposit: " << depositAccount->getBalance() << "\n\n";
        
        try {
            depositAccount->withdraw(100.0);
        } catch (const std::exception& e) {
            std::cout << "Deposit withdraw error: " << e.what() << "\n\n";
        }
        
        creditAccount->withdraw(500.0);
        std::cout << "Credit after withdraw 500: " << creditAccount->getBalance() << "\n";
        
        // 6. Начисление процентов/комиссий
        bank1->processDailyPayments();
        bank2->processDailyPayments();
        
        std::cout << "\nAfter daily payments:\n";
        std::cout << "Debit: " << debitAccount->getBalance() << "\n";
        std::cout << "Deposit: " << depositAccount->getBalance() << "\n";
        std::cout << "Credit: " << creditAccount->getBalance() << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
