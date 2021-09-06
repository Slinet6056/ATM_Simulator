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
    //���ַ����Զ�������ʽд���ļ�
    static inline void writeString(ofstream &, const string &);

    //��ȡ�Զ�������ʽд���ļ����ַ���
    static inline void readString(ifstream &, string &);

public:
    //���ļ���ȡ����
    static void loadRecord(vector<Account> &);

    //������д���ļ�
    static void saveRecord(const vector<Account> &);
};


#endif
