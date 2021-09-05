#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Account {

    //基本信息
    string id;                                                       //卡号
    string name;                                                     //姓名
    string password;                                                 //密码
    double balance;                                                  //账户余额

    //单笔交易记录
    struct Transaction {
        string id;                                                   //交易编号
        string time;                                                 //交易时间
        int type;                                                    //交易类型 1-存款 2-取款 3-转账
        double money;                                                //交易金额
        string counterpartyAccount;                                  //转账对方账户
    };

    //历史交易记录
    vector<Transaction> transactionHistory;
};


#endif