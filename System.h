#ifndef ATM_SIMULATOR_SYSTEM_H
#define ATM_SIMULATOR_SYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <sys/timeb.h>
#include <ctime>
#include "Account.h"
#include "Record.h"
#include "EasyX.h"

#define CANCEL 1
#define ERR_NOTSIGNIN -1
#define ERR_ALREADYSIGNIN -1
#define ERR_INVALIDID -2
#define ERR_WRONGPASSWORD -3
#define ERR_WRONGPASSWORD_TWOCHANCESLEFT -32
#define ERR_WRONGPASSWORD_ONECHANCELEFT -31
#define ERR_WRONGPASSWORD_NOCHANCELEFT -30
#define ERR_CARDLOCKED -4
#define ERR_SAMEPASSWORD -5
#define ERR_DIFFERENTPASSWORD -6
#define ERR_AMOUNTLIMITEXCEED -7
#define ERR_INSUFFICIENTBALANCE -8
#define ERR_ZEROAMOUNT -9

using std::string;
using std::vector;
using std::unordered_map;
using std::stringstream;
using std::ios;
using std::setiosflags;
using std::setprecision;
using std::to_string;
using std::swap;
using std::setw;
using std::setfill;

class System {
    vector<Account> accounts;                                        //记录所有用户数据
    unordered_map<string, Account *> accountIndex;                   //以卡号为键创建用户索引
    Account *currAccount{nullptr};                                   //当前登录用户 为空则表示未登录
    string currAccountId;                                            //当前用户卡号 为空则表示未登录
    EasyX easyX;                                                     //图形界面类
    bool isAdmin{false};                                             //是否为管理员账号
    const string adminId{"1234567890"};                          //管理员账号ID
    const string adminPassword{"123456"};                       //管理员账号密码

public:
    System();

    [[noreturn]] void start();

private:
    int signIn();

    int signOut();

    int signUp();

    int changePassword();

    int deleteAccount();

    int deposit();

    int withdrawal();

    int transfer();

    int showBalance();

    int showTransactionHistory();

    void signInMenu();

    void mainMenu();

    int accountMenu();

    void transactionMenu();

    void informationMenu();

    static string getTimestamp();

    static string getCurrentTime();
};


#endif
