#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

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
        double transactionMoney;                                     //交易金额
        string counterpartyAccount;                                  //转账对方账户 若存取款则为自己账户
    };

    //历史交易记录
    vector<Transaction> transactionHistory;

    Account() = default;

    Account(string &id, string &name, string &password) : id(id), name(name), password(password) {}

    Account(string &id, string &name, string &password, double &balance, int &wrongPasswordLeft, vector<Transaction> &transactionHistory) :
            id(id), name(name), password(password), balance(balance), wrongPasswordLeft(wrongPasswordLeft), transactionHistory(transactionHistory) {}

    int changePassword(const string &newPassword);
};


#endif