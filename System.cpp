#include "System.h"

//��Ĺ��캯�������ļ��м����˻���Ϣ
System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

//����ATMģ������֮������ѭ����ֱ������˳���ťʹ��exit(0)��������
[[noreturn]] void System::start() {
    while (true) {
        signInMenu();
        mainMenu();
    }
}

//����ʵ���˻���¼����
int System::signIn() {
    if (currAccount || isAdmin) return ERR_ALREADYSIGNIN;

    easyX.showNumberInputPanel();

    //���ڽ�������Ŀ���������
    //���ڿ���Ҫ�������������ļ��д洢����Ϣ�ȶԣ���ʹ��id_copy������һ��δ�����ܵĸ������Ա�ʹ��
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

        //������������������һ�λ���
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

        //��¼�ɹ�
        currAccount = accountIndex[id];
        currAccountId = id_copy;
        currAccount->wrongPasswordLeft = 3;
    }
    return 0;
}

//����ʵ���˻��˳�����
int System::signOut() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //�˳��ɹ�
    currAccount = nullptr;
    currAccountId.clear();
    isAdmin = false;
    return 0;
}

//����ʵ�ֹ���Ա�����˻�����
int System::signUp() {
    //���ڽ��չ���Ա��������˻����š�����������
    string id, name, password;

    id = EasyX::inputBox("���ţ�");
    id = MD5(id).toStr();
    if (accountIndex.count(id)) return ERR_INVALIDID;

    name = EasyX::inputBox("������");

    password = EasyX::inputBox("���룺");
    password = MD5(password).toStr();

    //�ɹ�����һ�����˺�
    Account account(id, name, password);
    accounts.push_back(account);
    accountIndex[id] = &accounts.back();

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ���޸����빦��
int System::changePassword() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //���ڽ��չ���Ա������˺ź�������
        string id, newPassword;

        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //��ʣ��������������������Ϊ3
        //ע���������ִ�������¾������Ƿ���ͬ���ж�
        //Ҳ����˵��ʹ����������;�������ͬ������û���޸ĳɹ�������Ҳ�ᱻ����
        //���ô������������ʵ������һ����ڱȽϺã�������Ϊ�������޸�ͼ�ν��棬���Ծͷ���������
        accountIndex[id]->wrongPasswordLeft = 3;

        newPassword = EasyX::inputBox("�����룺");
        newPassword = MD5(newPassword).toStr();
        if (newPassword == accountIndex[id]->password) return ERR_SAMEPASSWORD;

        //�����޸ĳɹ�
        accountIndex[id]->password = newPassword;

    } else {
        easyX.showNumberInputPanel();

        //���ڽ����û����������������
        string newPassword, confirmPassword;

        newPassword = easyX.inputNumber(MODE_PASSWORD, "������������");
        confirmPassword = easyX.inputNumber(MODE_PASSWORD, "ȷ��������");

        if (newPassword != confirmPassword) return ERR_DIFFERENTPASSWORD;

        newPassword = MD5(newPassword).toStr();
        if (newPassword == currAccount->password) return ERR_SAMEPASSWORD;

        //�����޸ĳɹ�
        currAccount->password = newPassword;
    }

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ���˻�ע������
int System::deleteAccount() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //���ڽ���ɾ���˻�ȷ�ϴ��ڵķ���ֵ�����û��������Ա���Ƿ�ȷ��ɾ���˻�
    int res;
    if (isAdmin) {
        //���ڽ��չ���Ա�����Ҫɾ�����˺�
        //���ڿ���Ҫ�������������ļ��д洢����Ϣ�ȶԣ���ʹ��id_copy������һ��δ�����ܵĸ������Ա�ʹ��
        string id, id_copy;

        id = EasyX::inputBox("���ţ�");
        id_copy = id;
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //ȷ���Ƿ�ɾ���˻�
        res = easyX.confirm("ɾ���˻�", id_copy.c_str());
        if (res == 1) return CANCEL;

        //�ɹ�ɾ���˻�
        swap(*accountIndex[id], *(accounts.end() - 1));
        accounts.pop_back();
        accountIndex.erase(id);

    } else {
        easyX.showNumberInputPanel();

        //���ڽ����û����������
        string password;

        password = easyX.inputNumber(MODE_PASSWORD, "����������");
        password = MD5(password).toStr();
        if (password != currAccount->password) return ERR_WRONGPASSWORD;

        //��double���͵����תΪstring���Ͳ�ֻ��ʾ�����λС��
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;

        //ȷ���Ƿ�ע���˻�������ʾʣ�����
        res = easyX.confirm("ע���˻�", ("���" + ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //�ɹ�ע���˻�
        accountIndex.erase(currAccount->id);
        swap(*currAccount, *(accounts.end() - 1));
        accounts.pop_back();

        //�˳���¼
        currAccount = nullptr;
        currAccountId.clear();
    }

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ�ִ���
int System::deposit() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //���ڽ��մ��ȷ�ϴ��ڵķ���ֵ�����û��������Ա���Ƿ�ȷ�ϴ��
    int res;
    if (isAdmin) {
        //���ڽ��չ���Ա����Ŀ��������string���ͣ�
        string id, amount_str;

        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        amount_str = EasyX::inputBox("����");

        //��������ֻ��ʾ��λС��
        double amount = stod(amount_str);
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //ȷ���Ƿ���
        res = easyX.confirm("�����", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //���ɹ�
        accountIndex[id]->deposit(stod(ss.str()), getTimestamp(), getCurrentTime());

    } else {
        easyX.showNumberInputPanel();

        //�����û�����Ĵ���string���ͣ�
        //��ʽ�������ʱ����ѿ��ƣ��ʲ���Ҫ�ٵ���
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "����������");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 10000) return ERR_AMOUNTLIMITEXCEED;

        //ȷ���Ƿ���
        res = easyX.confirm("�����", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //���ɹ�
        currAccount->deposit(stod(amount_str), getTimestamp(), getCurrentTime());

        //��ʾ�Ƿ��ӡƾ֤
        res = easyX.confirm(("�ɹ����" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ��ȡ���
int System::withdrawal() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //���ڽ���ȡ��ȷ�ϴ��ڵķ���ֵ�����û��������Ա���Ƿ�ȷ��ȡ��
    int res;
    if (isAdmin) {
        //���ڽ��չ���Ա����Ŀ�����ȡ���string���ͣ�
        string id, amount_str;

        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        amount_str = EasyX::inputBox("ȡ���");

        //��string���͵�ȡ����ת��Ϊdouble����
        double amount = stod(amount_str);

        //����Ƿ�����
        if (amount > accountIndex[id]->balance) return ERR_INSUFFICIENTBALANCE;

        //ȡ�������ֻ��ʾ��λС��
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //ȷ���Ƿ�ȡ��
        res = easyX.confirm("ȡ����", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //ȡ��ɹ�
        accountIndex[id]->withdrawal(stod(ss.str()), getTimestamp(), getCurrentTime());
    } else {

        easyX.showNumberInputPanel();

        //�����û������ȡ���string���ͣ�
        //��ʽ�������ʱ����ѿ��ƣ��ʲ���Ҫ�ٵ���
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "������ȡ����");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 5000) return ERR_AMOUNTLIMITEXCEED;

        //����Ƿ�����
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;

        //ȷ���Ƿ�ȡ��
        res = easyX.confirm("ȡ����", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //ȡ��ɹ�
        currAccount->withdrawal(stod(amount_str), getTimestamp(), getCurrentTime());

        //��ʾ�Ƿ��ӡƾ֤
        res = easyX.confirm(("�ɹ�ȡ��" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ��ת�˹���
int System::transfer() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //���ڽ���ת��ȷ�ϴ��ڵķ���ֵ�����û��������Ա���Ƿ�ȷ��ת��
    int res;
    if (isAdmin) {
        //���ڽ��չ���Ա�����ת���˺š�ת���˺ź�ת�˽��
        //���ڿ���Ҫ�������������ļ��д洢����Ϣ�ȶԣ���ʹ��_copy������һ��δ�����ܵĸ������Ա�ʹ��
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

        //��string���͵�ת�˽��ת��Ϊdouble����
        double amount = stod(amount_str);

        //����Ƿ�����
        if (amount > accountIndex[fromId]->balance) return ERR_INSUFFICIENTBALANCE;

        //ת�˽�����ֻ��ʾ��λС��
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //ȷ���Ƿ�ת��
        res = easyX.confirm("ת�˽��", (ss.str() + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //ת�˳ɹ�
        //�����ȡ��ʱ����͸�ʽ��ʱ����ܻ᲻ͬ���������ⲻ��ʱ���ֻ��������ã����߲���̫�����
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        accountIndex[fromId]->transferOut(stod(ss.str()), toId_copy, timestamp, currTime);
        accountIndex[toId]->transferIn(stod(ss.str()), fromId_copy, timestamp, currTime);

    } else {
        easyX.showNumberInputPanel();

        //���ڽ����û�������տ��˺ź�ת�˽�string���ͣ�
        //���ڿ���Ҫ�������������ļ��д洢����Ϣ�ȶԣ���ʹ��toId_copy������һ��δ�����ܵĸ������Ա�ʹ��
        string toId, toId_copy, amount_str;

        toId = easyX.inputNumber(1, "������Է��˻�");
        toId_copy = toId;
        toId = MD5(toId).toStr();
        if (!accountIndex.count(toId)) return ERR_INVALIDID;

        amount_str = easyX.inputNumber(MODE_AMOUNT, "������ת�˽��");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 50000) return ERR_AMOUNTLIMITEXCEED;

        //����Ƿ�����
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;

        //ȷ���Ƿ�ת��
        res = easyX.confirm("ת�˽��", (amount_str + "Ԫ").c_str());
        if (res == 1) return CANCEL;

        //ת�˳ɹ�
        //�����ȡ��ʱ����͸�ʽ��ʱ����ܻ᲻ͬ���������ⲻ��ʱ���ֻ��������ã����߲���̫�����
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        currAccount->transferOut(stod(amount_str), toId_copy, getTimestamp(), getCurrentTime());
        accountIndex[toId]->transferIn(stod(amount_str), currAccountId, timestamp, currTime);

        //ȷ���Ƿ��ӡƾ֤
        res = easyX.confirm(("�ɹ�ת��" + amount_str + "Ԫ").c_str(), "�Ƿ��ӡƾ֤");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("��ӡ�ɹ�");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//����ʵ������ѯ����
int System::showBalance() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //���ڽ��չ���Ա����Ŀ���
        string id;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //������ֻ��ʾ��λС��
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << accountIndex[id]->balance;
        easyX.tip("���", (ss.str() + "Ԫ").c_str());

    } else {
        //������ֻ��ʾ��λС��
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;
        easyX.tip("���", (ss.str() + "Ԫ").c_str());
    }
    return 0;
}

//����ʵ�ֽ��׼�¼��ѯ����
//����ԭ�ƻ���һ��ȫ�µĽ��棬�����ù������¹����鿴���׼�¼
//��������д���ˣ��Ϳ�����������ܣ����ֱ�����ļ�������
int System::showTransactionHistory() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //���ڽ��չ���Ա����Ŀ���
        string id;
        id = EasyX::inputBox("���ţ�");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //�������׼�¼�ɹ�
        Record::exportTransactionHistory(accountIndex[id]->transactionHistory);
        easyX.tip("������ʷ��¼�ѵ���");

    } else {
        //ֱ�ӵ�����ǰ�˻��Ľ��׼�¼
        Record::exportTransactionHistory(currAccount->transactionHistory);
        easyX.tip("������ʷ��¼�ѵ���");
    }
    return 0;
}

//����EasyX��ķ�����ʾ��¼���棬�����ť���Խ��е�¼���˳�����������ֿ��ܷ����Ĵ���
void System::signInMenu() {
    //���ڽ��ս��е�¼��������󷵻صĽ��
    int res;
    do {
        easyX.showSignInMenu();

        //��ȡ�������ť�ı��
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
    } while (res);
}

//����EasyX��ķ�����ʾ���˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
void System::mainMenu() {
    //��ȡ�������ť�ı�ţ�4����ǳ���
    int mainMenuSelection = 0;
    while (mainMenuSelection != 4) {
        //����Ա�ı�����ʾΪ"Admin"�����û����Ǵ����������ֵĻ�ӭ��
        if (isAdmin) {
            easyX.showMainMenu("Admin", true);
        } else {
            easyX.showMainMenu(currAccount->name, false);
        }

        mainMenuSelection = easyX.getMainMenuSelection();
        switch (mainMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
            case 1: {
                //��ȡ�˻�����ģ�鷵�صĽ��
                int res = accountMenu();
                //������Ҫ���������û�ע���˻���res==-1�����ص�¼����
                //��mainMenuSelection=4���൱���ֶ����˵ǳ���ť
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
                //��ȡ�ǳ��˺Ų������
                int res = signOut();
                //ʵ�����������͵Ĵ���ֻ������һ�Σ������Ҵ���д��һ����bug��ʱ��ƽʱʹ��Ӧ��Ū�������ִ���İ�
                if (res) {
                    easyX.error("δ��¼�˻�");
                }
                break;
            }
        }
    }
}

//����EasyX��ķ�����ʾ�˻�����˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
int System::accountMenu() {
    //��ȡ����������ı�ţ�4�����ؼ���5��Ӧ����ע���˻���Ҫ�ص���¼������������
    int accountMenuSelection = 0;
    while (accountMenuSelection < 4) {
        easyX.showAccountMenu(isAdmin);

        accountMenuSelection = easyX.getAccountMenuSelection(isAdmin);
        if (isAdmin) {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //��ȡ�½��˻��������
                    int res = signUp();
                    if (res == ERR_INVALIDID) {
                        easyX.error("�˺��Ѵ���");
                    }
                    break;
                }
                case 2: {
                    //��ȡɾ���˻��������
                    int res = deleteAccount();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 3: {
                    //��ȡ�޸�����������
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
                    //������ؼ��������浽while�жϵ�ʱ�������ѭ��������
                    break;
            }
        } else {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1:
                    //��ʵ�û�����������˻���ť�Ǵ����ģ��벻������������
                    easyX.tip("����ϵ����ԱQQ", "492829253");
                    break;
                case 2: {
                    //��ȡע���˻��������
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
                    //��ȡ�޸�����������
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
                    //������ؼ������ϵ�while�жϵ�ʱ�������ѭ��������
                    break;
            }
        }
    }
    //ע���˻��ص���¼������������
    if (accountMenuSelection == 5) return -1;
    else return 0;
}

//����EasyX��ķ�����ʾ�������˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
void System::transactionMenu() {
    //��ȡ�������ť�ı�ţ�4�����ؼ�
    int transactionMenuSelection = 0;
    while (transactionMenuSelection != 4) {
        easyX.showTransactionMenu();

        transactionMenuSelection = easyX.getTransactionMenuSelection();
        if (isAdmin) {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //��ȡ���������
                    int res = deposit();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    //��ȡȡ��������
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
                    //��ȡת�˲������
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
                    //������ؼ��������浽while�жϵ�ʱ�������ѭ��������
                    break;
            }
        } else {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //��ȡ���������
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
                    //��ȡȡ��������
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
                    //��ȡת�˲������
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
                    //������ؼ������ϵ�while�жϵ�ʱ�������ѭ��������
                    break;
            }
        }
    }
}

//����EasyX��ķ�����ʾ��Ϣ��ѯ�˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
void System::informationMenu() {
    //��ȡ�������ť�ı�ţ�4�����ؼ�
    int informationMenuSelection = 0;
    while (informationMenuSelection != 3) {
        easyX.showInformationMenu();

        informationMenuSelection = easyX.getInformationMenuSelection();
        if (isAdmin) {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //��ȡ��ʾ���������
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    //��ȡ���׼�¼��ѯ�������
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    }
                    break;
                }
                case 3:
                    //������ؼ��������浽while�жϵ�ʱ�������ѭ������
                    break;
            }
        } else {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //��ȡ��ʾ���������
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("���Ų�����");
                    }
                    break;
                }
                case 2: {
                    //��ȡ��ʾ������ʷ��¼�������
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("δ��¼�˻�");
                    }
                    break;
                }
                case 3:
                    //������ؼ�����
                    break;
            }
        }
    }
}

//��ȡʱ���
string System::getTimestamp() {
    //���ǻ�ȡʱ�����
    timeb timestamp{};
    ftime(&timestamp);

    //���������ܲ�����λ��Ҫ����0
    stringstream ss;
    ss << setw(3) << setfill('0') << timestamp.millitm;

    return to_string(timestamp.time) + ss.str();
}

//��ȡ��ʽ���ĵ�ǰʱ�䣨�磺"2021-09-09 22:02:35"��
string System::getCurrentTime() {
    //�������������ڻ�ȡ��ǰʱ��Ӵ
    tm currTime{};
    time_t timestamp = time(nullptr);

    localtime_s(&currTime, &timestamp);

    //���ڴ������ո�ʽ���Ľ��
    string ans;
    //���ڸ�ʽ����ǰʱ��
    stringstream ss;

    //��
    ans += to_string(1900 + currTime.tm_year) + "-";

    //��
    ss << setw(2) << setfill('0') << 1 + currTime.tm_mon;
    ans += ss.str() + "-";

    //��
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_mday;
    ans += ss.str() + " ";

    //ʱ
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_hour;
    ans += ss.str() + ":";

    //��
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_min;
    ans += ss.str() + ":";

    //��
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_sec;
    ans += ss.str();
    return ans;
}
