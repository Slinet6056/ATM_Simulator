﻿#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

//该类用于储存单个用户的基本信息和交易记录，提供方法用于增加不同类型的交易记录
class Account {
public:
    //基本信息
    string id;                                                       //卡号
    string name;                                                     //姓名
    string password;                                                 //密码
    double balance{0};                                               //账户余额
    int wrongPasswordLeft{3};                                        //还可输入错误密码次数

    //单笔交易记录
    struct Transaction {
        string transactionId;                                        //交易编号
        string transactionTime;                                      //交易时间
        int transactionType;                                         //交易类型 1-存款 2-取款 3-转入 4-转出
        double transactionAmount;                                    //交易金额
        string counterpartyAccount;                                  //转账对方账号 若存取款则为"this"
    };

    vector<Transaction> transactionHistory;                          //历史交易记录

    //类的默认构造函数
    Account() = default;

    //提供卡号、姓名和密码的类构造函数，一般为创建新账号时使用
    Account(string &id, string &name, string &password) : id(id), name(name), password(password) {}

    //提供全部信息的类构造函数，一般为从本地文件读取账户信息时使用
    Account(string &id, string &name, string &password, double &balance, int &wrongPasswordLeft, vector<Transaction> &transactionHistory) :
            id(id), name(name), password(password), balance(balance), wrongPasswordLeft(wrongPasswordLeft), transactionHistory(transactionHistory) {}

    //增加一条存款交易记录，参数分别为存款金额、交易编号（用时间戳代替）、交易时间
    void deposit(double amount, const string &timestamp, const string &currTime);

    //增加一条取款交易记录，参数分别为取款金额、交易编号（用时间戳代替）、交易时间
    void withdrawal(double amount, const string &timestamp, const string &currTime);

    //增加一条转账收款交易记录（转入账户调用），参数分别为转账金额、对方账号、交易编号（用时间戳代替）、交易时间
    void transferIn(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);

    //增加一条转账付款交易记录（转出账户调用），参数分别为转账金额、对方账号、交易编号（用时间戳代替）、交易时间
    void transferOut(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);
};


#endif