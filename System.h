#ifndef ATM_SIMULATOR_SYSTEM_H
#define ATM_SIMULATOR_SYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "Account.h"
#include "Record.h"

using std::string;
using std::vector;
using std::unordered_map;

class System {
    vector<Account> accounts;                                        //��¼�����û�����
    unordered_map<string, Account *> accountIndex;                   //�Կ���Ϊ�������û�����
    string currAccount;                                              //��ǰ��¼�û� Ϊ�����ʾδ��¼

    System();

    int signIn();

    int signOut();

    int signUp();
};


#endif
