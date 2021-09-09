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
#include "MD5.h"

//各种错误状态
#define CANCEL 1                                                     //取消
#define ERR_NOTSIGNIN -1                                             //未登录账户，按照程序逻辑不应发生此错误，仅防止极端情况发生
#define ERR_ALREADYSIGNIN -1                                         //已登录账户，按照程序逻辑不应发生此错误，仅防止极端情况发生
#define ERR_INVALIDID -2                                             //输入的卡号不存在
#define ERR_WRONGPASSWORD -3                                         //密码错误
#define ERR_WRONGPASSWORD_TWOCHANCESLEFT -32                         //用户登录时输入的密码错误，还剩两次机会
#define ERR_WRONGPASSWORD_ONECHANCELEFT -31                          //用户登录时输入的密码错误，还剩一次机会
#define ERR_WRONGPASSWORD_NOCHANCELEFT -30                           //用户登录时输入的密码错误，没有剩余机会
#define ERR_CARDLOCKED -4                                            //账户以锁定
#define ERR_SAMEPASSWORD -5                                          //修改密码时新密码与原密码相同
#define ERR_DIFFERENTPASSWORD -6                                     //用户修改密码时两次输入的密码不一致
#define ERR_AMOUNTLIMITEXCEED -7                                     //用户进行存取款和转账时单笔金额超过上限
#define ERR_INSUFFICIENTBALANCE -8                                   //取款与转账时账户余额不足
#define ERR_ZEROAMOUNT -9                                            //存款取款和转账金额为零

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

//该类调用其他类的方法，实现了AMT模拟器的各种功能
class System {
    vector<Account> accounts;                                        //记录所有用户数据
    unordered_map<string, Account *> accountIndex;                   //以卡号为键创建用户索引
    Account *currAccount{nullptr};                                   //当前登录用户，为空则表示未登录
    string currAccountId;                                            //当前用户卡号，为空则表示未登录
    EasyX easyX;                                                     //创建一个图形界面类
    bool isAdmin{false};                                             //是否为管理员账号
    const string adminId{"1234567890"};                              //保存管理员账户ID
    const string adminPassword{"123456"};                            //保存管理员账户密码

public:
    //类的构造函数，从文件中加载账户信息
    System();

    //启动ATM模拟器，之后无限循环，直到点击退出按钮使用exit(0)结束程序
    [[noreturn]] void start();

private:
    //负责实现账户登录功能
    int signIn();

    //负责实现账户退出功能
    int signOut();

    //负责实现管理员增加账户功能
    int signUp();

    //负责实现修改密码功能
    int changePassword();

    //负责实现账户注销功能
    int deleteAccount();

    //负责实现存款功能
    int deposit();

    //负责实现取款功能
    int withdrawal();

    //负责实现转账功能
    int transfer();

    //负责实现余额查询功能
    int showBalance();

    //负责实现交易记录查询功能
    //这里原计划是一个全新的界面，可以用滚轮上下滚动查看交易记录
    //后来代码写累了，就砍掉了这个功能，变成直接用文件导出了
    int showTransactionHistory();

    //调用EasyX类的方法显示登录界面，点击按钮可以进行登录与退出，并处理各种可能发生的错误
    void signInMenu();

    //调用EasyX类的方法显示主菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
    void mainMenu();

    //调用EasyX类的方法显示账户管理菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
    int accountMenu();

    //调用EasyX类的方法显示金额操作菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
    void transactionMenu();

    //调用EasyX类的方法显示信息查询菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
    void informationMenu();

    //获取时间戳
    static string getTimestamp();

    //获取格式化的当前时间（如："2021-09-09 22:02:35"）
    //话说这几天每天都写代码到十一点多，要秃了要秃了
    static string getCurrentTime();
};


#endif
