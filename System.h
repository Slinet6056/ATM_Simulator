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
    vector<Account> accounts;                                        //记录所有用户数据
    unordered_map<string, Account *> accountIndex;                   //以卡号为键创建用户索引
    Account *currAccount{nullptr};                                   //当前登录用户 为空则表示未登录
    EasyX easyX;                                                     //图形界面类
    bool isAdmin{false};                                             //是否为管理员账号

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
