#include "System.h"

System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

int System::signIn() {
    return 0;
}

int System::signOut() {
    return 0;
}

int System::signUp() {
    string id, name, password;
    std::cin >> id >> name >> password;
    id = MD5(id).toStr();
    password = MD5(password).toStr();
    Account account(id, name, password);
    accounts.push_back(account);
    Record::saveRecord(accounts);
    return 0;
}

int System::showRecord() {
    std::cout << accounts.size() << std::endl;
    for (const auto &account: accounts) {
        std::cout << account.id << " " << account.name << " " << account.password << std::endl;
    }
    return 0;
}
