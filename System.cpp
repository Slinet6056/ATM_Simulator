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
    if (currAccount || isAdmin) return ERR_ALREADYSIGNIN;
    easyX.showNumberInputPanel();
    string id, id_copy, password;
    id = easyX.inputNumber(MODE_ID, "�����뿨��");
    if (id == adminId) {
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        if (password != adminPassword) return ERR_WRONGPASSWORD;
        isAdmin = true;
    } else {
        id_copy = id;
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        if (!accountIndex[id]->wrongPasswordLeft) return ERR_CARDLOCKED;
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        password = MD5(password).toStr();
        if (accountIndex[id]->password != password) {
            --accountIndex[id]->wrongPasswordLeft;
            Record::saveRecord(accounts);
            switch (accountIndex[id]->wrongPasswordLeft) {
                case 2:
                    return ERR_WRONGPASSWORD_TWOCHANCESLEFT;
                case 1:
                    return ERR_WRONGPASSWORD_ONECHANCELEFT;
                case 0:
                    return ERR_WRONGPASSWORD_NOCHANCELEFT;
            }
        }
        currAccount = accountIndex[id];
        currAccountId = id_copy;
        currAccount->wrongPasswordLeft = 3;
    }

    return 0;
}

int System::signOut() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    currAccount = nullptr;
    currAccountId.clear();
    isAdmin = false;
    return 0;
}

int System::signUp() {
    string id, name, password;
    id = EasyX::inputBox("���ţ�");
    id = MD5(id).toStr();
    if (accountIndex.count(id)) return ERR_INVALIDID;
    name = EasyX::inputBox("������");
    password = EasyX::inputBox("���룺");
    password = MD5(password).toStr();
    Account account(id, name, password);
    accounts.push_back(account);
    accountIndex[id] = &accounts.back();
    Record::saveRecord(accounts);
    return 0;
}

int System::changePassword() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    if (isAdmin) {
        string id, newPassword;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        newPassword = EasyX::inputBox("�����룺");
        newPassword = MD5(newPassword).toStr();
        accountIndex[id]->wrongPasswordLeft = 3;
        if (newPassword == accountIndex[id]->password) return ERR_SAMEPASSWORD;
        accountIndex[id]->password = newPassword;
    } else {
        easyX.showNumberInputPanel();
        string newPassword, confirmPassword;
        newPassword = easyX.inputNumber(MODE_PASSWORD, "������������");
        confirmPassword = easyX.inputNumber(MODE_PASSWORD, "ȷ��������");
        if (newPassword != confirmPassword) return ERR_DIFFERENTPASSWORD;
        newPassword = MD5(newPassword).toStr();
        if (newPassword == currAccount->password) return ERR_SAMEPASSWORD;
        currAccount->password = newPassword;
    }
    Record::saveRecord(accounts);
    return 0;
}

int System::deleteAccount() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    int res;
    if (isAdmin) {
        string id, id_copy;
        id = EasyX::inputBox("���ţ�");
        id_copy = id;
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        res = easyX.confirm("ɾ���˻�", id_copy.c_str());
        if (res == 1) return CANCEL;
        swap(*accountIndex[id], *(accounts.end() - 1));
        accounts.pop_back();
        accountIndex.erase(id);
    } else {
        easyX.showNumberInputPanel();
        string password;
        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        password = MD5(password).toStr();
        if (password != currAccount->password) return ERR_WRONGPASSWORD;
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;
        res = easyX.confirm("ע���˻�", ("���" + ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        accountIndex.erase(currAccount->id);
        swap(*currAccount, *(accounts.end() - 1));
        accounts.pop_back();
        currAccount = nullptr;
        currAccountId.clear();
    }
    Record::saveRecord(accounts);
    return 0;
}

int System::deposit() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    int res;
    if (isAdmin) {
        string id, amount_str;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        amount_str = EasyX::inputBox("����");
        double amount = stod(amount_str);
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;
        res = easyX.confirm("�����", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        accountIndex[id]->deposit(stod(ss.str()), getTimestamp(), getCurrentTime());
    } else {
        easyX.showNumberInputPanel();
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "����������");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 10000) return ERR_AMOUNTLIMITEXCEED;
        res = easyX.confirm("�����", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        currAccount->deposit(stod(amount_str), getTimestamp(), getCurrentTime());
        res = easyX.confirm(("�ɹ����" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }
    Record::saveRecord(accounts);
    return 0;
}

int System::withdrawal() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    int res;
    if (isAdmin) {
        string id, amount_str;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        amount_str = EasyX::inputBox("ȡ���");
        double amount = stod(amount_str);
        if (amount > accountIndex[id]->balance) return ERR_INSUFFICIENTBALANCE;
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;
        res = easyX.confirm("ȡ����", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        accountIndex[id]->withdrawal(stod(ss.str()), getTimestamp(), getCurrentTime());
    } else {
        easyX.showNumberInputPanel();
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "������ȡ����");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 5000) return ERR_AMOUNTLIMITEXCEED;
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;
        res = easyX.confirm("ȡ����", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        currAccount->withdrawal(stod(amount_str), getTimestamp(), getCurrentTime());
        res = easyX.confirm(("�ɹ�ȡ��" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }
    Record::saveRecord(accounts);
    return 0;
}

int System::transfer() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    int res;
    if (isAdmin) {
        string fromId, fromId_copy, toId, toId_copy, amount_str;
        fromId = EasyX::inputBox("����ţ�");
        fromId_copy = fromId;
        fromId = MD5(fromId).toStr();
        if (!accountIndex.count(fromId)) return ERR_INVALIDID;
        toId = EasyX::inputBox("�տ�ţ�");
        toId_copy = toId;
        toId = MD5(toId).toStr();
        if (!accountIndex.count(toId)) return ERR_INVALIDID;
        amount_str = EasyX::inputBox("ת�˽�");
        double amount = stod(amount_str);
        if (amount > accountIndex[fromId]->balance) return ERR_INSUFFICIENTBALANCE;
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;
        res = easyX.confirm("ת�˽��", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        accountIndex[fromId]->transferOut(stod(ss.str()), toId_copy, timestamp, currTime);
        accountIndex[toId]->transferIn(stod(ss.str()), fromId_copy, timestamp, currTime);
    } else {
        easyX.showNumberInputPanel();
        string toId, toId_copy, amount_str;
        toId = easyX.inputNumber(1, "������Է��˻�");
        toId_copy = toId;
        toId = MD5(toId).toStr();
        if (!accountIndex.count(toId)) return ERR_INVALIDID;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "������ת�˽��");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 50000) return ERR_AMOUNTLIMITEXCEED;
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;
        res = easyX.confirm("ת�˽��", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        currAccount->transferOut(stod(amount_str), toId_copy, getTimestamp(), getCurrentTime());
        accountIndex[toId]->transferIn(stod(amount_str), currAccountId, timestamp, currTime);
        res = easyX.confirm(("�ɹ�ת��" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }
    Record::saveRecord(accounts);
    return 0;
}

int System::showBalance() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    if (isAdmin) {
        string id;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << accountIndex[id]->balance;
        easyX.tip("���", (ss.str() + "Ԫ").c_str());
    } else {
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;
        easyX.tip("���", (ss.str() + "Ԫ").c_str());
    }
    return 0;
}

int System::showTransactionHistory() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;
    if (isAdmin) {
        string id;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        Record::exportTransactionHistory(accountIndex[id]->transactionHistory);
        easyX.tip("������ʷ��¼�ѵ���");
    } else {
        Record::exportTransactionHistory(currAccount->transactionHistory);
        easyX.tip("������ʷ��¼�ѵ���");
    }
    return 0;
}

void System::signInMenu() {
    int res = 1;
    while (res) {
        easyX.showSignInMenu();
        int signInMenuSelection = easyX.getSignInMenuSelection();
        if (signInMenuSelection == 1) {
            res = signIn();
            switch (res) {
                case ERR_ALREADYSIGNIN:
                    easyX.error("�Ѵ��ڵ�¼״̬");
                    break;
                case ERR_INVALIDID:
                    easyX.error("���Ų�����");
                    break;
                case ERR_WRONGPASSWORD:
                    easyX.error("�������");
                    break;
                case ERR_CARDLOCKED:
                    easyX.error("�˻�������");
                    break;
                case ERR_WRONGPASSWORD_NOCHANCELEFT:
                    easyX.error("�������", "�˻�������");
                    break;
                case ERR_WRONGPASSWORD_ONECHANCELEFT:
                    easyX.error("�������", "��ʣ1�λ���");
                    break;
                case ERR_WRONGPASSWORD_TWOCHANCESLEFT:
                    easyX.error("�������", "��ʣ2�λ���");
                    break;
                default:
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
                if (res == ERR_NOTSIGNIN) mainMenuSelection = 4;
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
                    if (res == ERR_INVALIDID) {
                        easyX.error("�˺��Ѵ���");
                    }
                    break;
                }
                case 2: {
                    int res = deleteAccount();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 3: {
                    int res = changePassword();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    } else if (res == ERR_SAMEPASSWORD) {
                        easyX.error("��������ԭ������ͬ", "����������������");
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
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_WRONGPASSWORD) {
                        easyX.error("�������");
                    } else if (res == 0) {
                        accountMenuSelection = 5;
                    }
                    break;
                }
                case 3: {
                    int res = changePassword();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_DIFFERENTPASSWORD) {
                        easyX.error("�����������벻һ��");
                    } else if (res == ERR_SAMEPASSWORD) {
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
    int transactionMenuSelection = 0;
    while (transactionMenuSelection < 4) {
        easyX.showTransactionMenu();
        transactionMenuSelection = easyX.getTransactionMenuSelection();
        if (isAdmin) {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    int res = deposit();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    int res = withdrawal();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("����");
                    }
                    break;
                }
                case 3: {
                    int res = transfer();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("����");
                    }
                    break;
                }
                case 4:
                    break;
            }
        } else {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    int res = deposit();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_AMOUNTLIMITEXCEED) {
                        easyX.error("�������δ��������", "����Ϊ10000Ԫ");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("������Ϊ0");
                    }
                    break;
                }
                case 2: {
                    int res = withdrawal();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_AMOUNTLIMITEXCEED) {
                        easyX.error("��������ȡ��������", "����Ϊ5000Ԫ");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("����");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("ȡ�����Ϊ0");
                    }
                    break;
                }
                case 3: {
                    int res = transfer();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("�Է��˻�������");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("ת�˽���Ϊ0");
                    } else if (res == ERR_AMOUNTLIMITEXCEED) {
                        easyX.error("��������ת�˽������", "����Ϊ50000");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("����");
                    }
                    break;
                }
                case 4:
                    break;
            }
        }
    }
}

void System::informationMenu() {
    int informationMenuSelection = 0;
    while (informationMenuSelection < 3) {
        easyX.showInformationMenu();
        informationMenuSelection = easyX.getInformationMenuSelection();
        if (isAdmin) {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    }
                    break;
                }
                case 3:
                    break;
            }
        } else {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    }
                    break;
                }
                case 3:
                    break;
            }
        }
    }
}

string System::getTimestamp() {
    timeb timestamp{};
    ftime(&timestamp);
    stringstream ss;
    ss << setw(3) << setfill('0') << timestamp.millitm;
    return to_string(timestamp.time) + ss.str();
}

string System::getCurrentTime() {
    tm currTime{};
    time_t timestamp = time(nullptr);
    localtime_s(&currTime, &timestamp);
    string ans;
    ans += to_string(1900 + currTime.tm_year) + "-";
    ans += to_string(1 + currTime.tm_mon) + "-";
    ans += to_string(currTime.tm_mday) + " ";
    ans += to_string(currTime.tm_hour) + ":";
    ans += to_string(currTime.tm_min) + ":";
    ans += to_string(currTime.tm_sec);
    return ans;
}
