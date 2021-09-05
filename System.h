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
    vector<Account> accounts;                                        //记录所有用户数据
    unordered_map<string, Account *> accountIndex;                   //以卡号为键创建用户索引
    string currAccount;                                              //当前登录用户 为空则表示未登录

    System();

    int signIn();

    int signOut();

    int signUp();
};


#endif
