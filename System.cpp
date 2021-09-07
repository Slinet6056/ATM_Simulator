#include "System.h"

System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

[[noreturn]] void System::start() {
    while (true) {
        signInMenu();
        mainMenu();
    }
}

int System::signIn() {
    if (currAccount) return -1;
    easyX.showNumberInputPanel();

    string id, password;
    id = easyX.inputNumber(MODE_ID, "�����뿨��");
    if (id != "1234567890") {
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return -2;
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        password = MD5(password).toStr();
        if (accountIndex[id]->password != password) return -3;
        currAccount = accountIndex[id];
    } else {
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        if (password != "123456") return -3;
        isAdmin = true;
    }

    return 0;
}

int System::signOut() {
    if (!currAccount && !isAdmin) return -1;
    currAccount = nullptr;
    isAdmin = false;
    return 0;
}

int System::signUp() {
    string id, name, password;
    id = EasyX::inputBox("���ţ�");
    name = EasyX::inputBox("������");
    password = EasyX::inputBox("���룺");
    id = MD5(id).toStr();
    password = MD5(password).toStr();
    if (accountIndex.count(id)) return -1;
    Account account(id, name, password);
    accounts.push_back(account);
    accountIndex[id] = &accounts.back();
    Record::saveRecord(accounts);
    return 0;
}

int System::changePassword() {
    if (!currAccount && !isAdmin) return -1;
    int res = 0;
    if (isAdmin) {
        string id, newPassword;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return -2;
        newPassword = EasyX::inputBox("�����룺");
        newPassword = MD5(newPassword).toStr();
        res = accountIndex[id]->changePassword(newPassword);
    } else {
        easyX.showNumberInputPanel();
        string newPassword, confirmPassword;
        newPassword = easyX.inputNumber(MODE_PASSWORD, "������������");
        confirmPassword = easyX.inputNumber(MODE_PASSWORD, "ȷ��������");
        if (newPassword != confirmPassword) return -2;
        newPassword = MD5(newPassword).toStr();
        res = currAccount->changePassword(newPassword);
    }
    if (res) return -3;
    Record::saveRecord(accounts);
    return 0;
}

int System::deleteAccount() {
    if (!currAccount && !isAdmin) return -1;
    int res = 0;
    if (isAdmin) {
        string id;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return -2;
        res = easyX.confirm("ע���˻�");
        if (res == 1) return -3;
        swap(*accountIndex[id], *(accounts.end() - 1));
        accounts.pop_back();
        accountIndex.erase(id);
    } else {
        easyX.showNumberInputPanel();
        string password;
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        password = MD5(password).toStr();
        if (password != currAccount->password) return -2;
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;
        res = easyX.confirm("ע���˻�", ("���" + ss.str() + "Ԫ").c_str());
        if (res == 1) return -3;
        accountIndex.erase(currAccount->id);
        swap(*currAccount, *(accounts.end() - 1));
        accounts.pop_back();
        currAccount = nullptr;
    }
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
                    easyX.error("�Ѵ��ڵ�¼״̬");
                    break;
                case -2:
                    easyX.error("���Ų�����");
                    break;
                case -3:
                    easyX.error("�������");
                    break;
            }
        }
    }
}

void System::mainMenu() {
    int mainMenuSelection = 0;
    while (mainMenuSelection != 4) {
        if (isAdmin) {
            easyX.showMainMenu("Admin", true);
        } else {
            easyX.showMainMenu(currAccount->name, false);
        }
        mainMenuSelection = easyX.getMainMenuSelection();
        switch (mainMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
            case 1: {
                int res = accountMenu();
                if (res == -1) mainMenuSelection = 4;
                break;
            }
            case 2:
                transactionMenu();
                break;
            case 3:
                informationMenu();
                break;
            case 4: {
                int res = signOut();
                if (res) {
                    easyX.error("δ��¼�˻�");
                }
                break;
            }
        }
    }
}

int System::accountMenu() {
    int accountMenuSelection = 0;
    while (accountMenuSelection < 4) {
        easyX.showAccountMenu(isAdmin);
        accountMenuSelection = easyX.getAccountMenuSelection(isAdmin);
        if (isAdmin) {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    int res = signUp();
                    if (res) {
                        easyX.error("�˺��Ѵ���");
                    }
                    break;
                }
                case 2: {
                    int res = deleteAccount();
                    if (res == -1) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == -2) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 3: {
                    int res = changePassword();
                    if (res == -1) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == -2) {
                        easyX.error("���Ų�����");
                    } else if (res == -3) {
                        easyX.error("��������ԭ������ͬ");
                    }
                    break;
                }
                case 4:
                    break;
            }
        } else {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1:
                    easyX.tip("����ϵ����ԱQQ", "492829253");
                    break;
                case 2: {
                    int res = deleteAccount();
                    if (res == -1) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == -2) {
                        easyX.error("�������");
                    } else if (res == 0) {
                        accountMenuSelection = 5;
                    }
                    break;
                }
                case 3: {
                    int res = changePassword();
                    if (res == -1) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == -2) {
                        easyX.error("�����������벻һ��");
                    } else if (res == -3) {
                        easyX.error("��������ԭ������ͬ");
                    }
                    break;
                }
                case 4:
                    break;
            }
        }
    }
    if (accountMenuSelection == 5) return -1;
    else return 0;
}

void System::transactionMenu() {

}

void System::informationMenu() {

}
