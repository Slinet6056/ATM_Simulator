﻿#ifndef ATM_SIMULATOR_RECORD_H
#define ATM_SIMULATOR_RECORD_H

#include <fstream>
#include <vector>
#include "Account.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::endl;

//该类负责处理文件输入输出的相关操作
class Record {

    //C++中string类型的字符串如果直接使用常规数据类型的方式进行二进制文件读入可能会引发一些错误
    //我采用的方式是先将字符串长度存入文件，再将string类型字符串转化成C风格字符串存入
    //读的时候先读取字符串长度len，再读取len个char类型字符，最终拼接成string类型字符串
    //这种方法在特殊情况下可能依然会产生错误，但在本程序中并不会发生（但愿吧）

    //将字符串以二进制形式写入文件，参数为文件输出流和要写入文件的字符串
    static inline void writeString(ofstream &, const string &);

    //读取以二进制形式写入文件的字符串，参数为文件输入流和接收读取数据的字符串的引用
    static inline void readString(ifstream &, string &);

public:
    //从文件读取数据，参数为接收所有数据的账号容器的引用
    static void loadRecord(vector<Account> &accounts);

    //将数据写入文件，参数为存储所有数据的账号容器的常量引用
    static void saveRecord(const vector<Account> &accounts);

    //打印凭据，参数为要打印的单条交易记录
    static void printVoucher(const Account::Transaction &transaction);

    //导出交易历史记录，参数为要导出的所有交易记录
    static void exportTransactionHistory(const vector<Account::Transaction> &transactionHistory);
};


#endif
