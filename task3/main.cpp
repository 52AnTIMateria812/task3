#include <iostream>
#include <memory>
#include "Client.h"
#include "Bank.h"
#include "CentralBank.h"
#include "DebitAccount.h"

int main() {
    try {
        // 1. Создаем центральный банк
        auto centralBank = std::make_shared<CentralBank>();
        
        // 2. Создаем два коммерческих банка
        auto bank1 = std::make_shared<Bank>("Alpha Bank", centralBank);
        auto bank2 = std::make_shared<Bank>("Beta Bank", centralBank);
        
        // 3. Регистрируем банки в центральном банке
        centralBank->registerBank(bank1);
        centralBank->registerBank(bank2);
        
        // 4. Создаем клиентов
        auto client1 = bank1->registerClient("John", "Doe");
        auto client2 = bank2->registerClient("Jane", "Smith");
        
        // 5. Создаем счета для клиентов
        auto account1 = bank1->createAccount(AccountType::DEBIT, client1, 1000.0);
        auto account2 = bank2->createAccount(AccountType::DEBIT, client2, 500.0);
        
        // 6. Выводим информацию о счетах
        std::cout << "Account 1 balance: " << account1->getBalance() << std::endl;
        std::cout << "Account 2 balance: " << account2->getBalance() << std::endl;
        
        // 7. Выполняем перевод между счетами
        account1->transfer(account2, 200.0);
        
        std::cout << "\nAfter transfer:\n";
        std::cout << "Account 1 balance: " << account1->getBalance() << std::endl;
        std::cout << "Account 2 balance: " << account2->getBalance() << std::endl;
        
        // 8. Пытаемся выполнить перевод с недостаточным балансом
        try {
            account1->transfer(account2, 1000.0);
        } catch (const std::exception& e) {
            std::cout << "\nError: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
