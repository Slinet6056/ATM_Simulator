#ifndef ATM_SIMULATOR_SYSTEM_H
#define ATM_SIMULATOR_SYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Account.h"
#include "Record.h"
#include "EasyX.h"

using std::string;
using std::vector;
using std::unordered_map;

class System {
    vector<Account> accounts;                                        //��¼�����û�����
    unordered_map<string, Account *> accountIndex;                   //�Կ���Ϊ�������û�����
    Account *currAccount{nullptr};                                   //��ǰ��¼�û� Ϊ�����ʾδ��¼
    EasyX easyX;                                                     //ͼ�ν�����
    bool isAdmin{false};                                             //�Ƿ�Ϊ����Ա�˺�

public:
    System();

    void start();

    int signIn();

    int signOut();

    int signUp();

    int showRecord();

    int changePassword();

private:
    void signInMenu();

    void mainMenu();
};


#endif
