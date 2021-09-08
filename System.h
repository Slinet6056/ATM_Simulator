#ifndef ATM_SIMULATOR_SYSTEM_H
#define ATM_SIMULATOR_SYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Account.h"
#include "Record.h"
#include "EasyX.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::stringstream;
using std::ios;
using std::setiosflags;
using std::setprecision;
using std::to_string;
using std::swap;

class System {
    vector<Account> accounts;                                        //��¼�����û�����
    unordered_map<string, Account *> accountIndex;                   //�Կ���Ϊ�������û�����
    Account *currAccount{nullptr};                                   //��ǰ��¼�û� Ϊ�����ʾδ��¼
    EasyX easyX;                                                     //ͼ�ν�����
    bool isAdmin{false};                                             //�Ƿ�Ϊ����Ա�˺�
    const string adminId{"1234567890"};                          //����Ա�˺�ID
    const string adminPassword{"123456"};                       //����Ա�˺�����

public:
    System();

    [[noreturn]] void start();

private:
    int signIn();

    int signOut();

    int signUp();

    int changePassword();

    int deleteAccount();

    void signInMenu();

    void mainMenu();

    int accountMenu();

    void transactionMenu();

    void informationMenu();
};


#endif
