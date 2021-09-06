#ifndef ATM_SIMULATOR_RECORD_H
#define ATM_SIMULATOR_RECORD_H

#include <fstream>
#include <vector>
#include "Account.h"
#include "MD5.h"

using std::ifstream;
using std::ofstream;
using std::vector;

class Record {
    //将字符串以二进制形式写入文件
    static inline void writeString(ofstream &, const string &);

    //读取以二进制形式写入文件的字符串
    static inline void readString(ifstream &, string &);

public:
    //从文件读取数据
    static void loadRecord(vector<Account> &);

    //将数据写入文件
    static void saveRecord(const vector<Account> &);
};


#endif
