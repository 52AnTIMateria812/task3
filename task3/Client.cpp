#include "Client.h"

Client::Client(const std::string& fName, const std::string& lName)
    : firstName(fName), lastName(lName) {}

void Client::addAccount(std::shared_ptr<Account> account) {
    accounts.push_back(account);
}

std::string Client::getFullName() const {
    return firstName + " " + lastName;
}

std::optional<std::string> Client::getPassportData() const {
    return passportData;
}

void Client::setPassportData(const std::string& data) {
    passportData = data;
}
