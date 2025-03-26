#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include <optional>

class Account;
class Bank;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::optional<std::string> passportData;
    std::optional<std::string> address;
    std::vector<std::shared_ptr<Account>> accounts;
    
public:
    Client(const std::string& fName, const std::string& lName);
    
    void addAccount(std::shared_ptr<Account> account);
    std::string getFullName() const;
    std::optional<std::string> getPassportData() const;
    void setPassportData(const std::string& data);
};

#endif // CLIENT_H
