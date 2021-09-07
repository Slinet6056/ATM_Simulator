#include "System.h"

System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

void System::start() {
    signInMenu();
    mainMenu();
}

int System::signIn() {
    if (currAccount) return -1;
    easyX.showNumberInputPanel();

    string id, password;
    id = easyX.inputNumber(1);
    if (id != "1234567890") {
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return -2;
        password = easyX.inputNumber(2);
        password = MD5(password).toStr();
        if (accountIndex[id]->password != password) return -3;
        currAccount = accountIndex[id];
    } else {
        password = easyX.inputNumber(2);
        if (password != "123456") return -3;
        isAdmin = true;
    }

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
    int res = 1;
    while (res) {
        easyX.showSignInMenu();
        int signInMenuSelection = easyX.getSignInMenuSelection();
        if (signInMenuSelection == 1) {
            res = signIn();
            switch (res) { // NOLINT(hicpp-multiway-paths-covered)
                case 0:
                    break;
                case -1:
                    easyX.error(_T("ÒÑ´¦ÓÚµÇÂ¼×´Ì¬"));
                    signInMenu();
                    break;
                case -2:
                    easyX.error(_T("¿¨ºÅ²»´æÔÚ"));
                    signInMenu();
                    break;
                case -3:
                    easyX.error(_T("ÃÜÂë´íÎó"));
                    signInMenu();
            }
        }
    }
}

void System::mainMenu() {
    if(isAdmin){

    }else{}
}
