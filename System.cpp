#include "System.h"

System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

void System::start() {
    signInMenu();
}

int System::signIn() {
    if (currAccount) return -1;
    easyX.showNumberInputPanel();
    for(;;){
        easyX.inputNumber(1);
    }
    string id, password;
    std::cin >> id >> password;
    id = MD5(id).toStr();
    password = MD5(password).toStr();
    if (!accountIndex.count(id)) return -2;
    if (accountIndex[id]->password != password) return -3;
    currAccount = accountIndex[id];
    std::cout << "Hello, " << accountIndex[id]->name << std::endl;
    return 0;
}

int System::signOut() {
    if (!currAccount) return -1;
    currAccount = nullptr;
    std::cout << "Gun" << std::endl;
    return 0;
}

int System::signUp() {
    string id, name, password;
    std::cin >> id >> name >> password;
    id = MD5(id).toStr();
    password = MD5(password).toStr();
    if (accountIndex.count(id)) return -1;
    Account account(id, name, password);
    accounts.push_back(account);
    accountIndex[id] = &accounts.back();
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

int System::changePassword() {
    if (!currAccount) return -1;
    string newPassword;
    std::cin >> newPassword;
    newPassword = MD5(newPassword).toStr();
    currAccount->changePassword(newPassword);
    signOut();
    Record::saveRecord(accounts);
    return 0;
}

void System::signInMenu() {
    easyX.showSignInMenu();
    int signInMenuSelection = easyX.getSignInMenuSelection();
    if (signInMenuSelection == 1) {
        int res = signIn();
    }
}
