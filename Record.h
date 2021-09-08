#ifndef ATM_SIMULATOR_RECORD_H
#define ATM_SIMULATOR_RECORD_H

#include <fstream>
#include <vector>
#include "Account.h"
#include "MD5.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::endl;

class Record {
    //���ַ����Զ�������ʽд���ļ�
    static inline void writeString(ofstream &, const string &);

    //��ȡ�Զ�������ʽд���ļ����ַ���
    static inline void readString(ifstream &, string &);

public:
    //���ļ���ȡ����
    static void loadRecord(vector<Account> &accounts);

    //������д���ļ�
    static void saveRecord(const vector<Account> &accounts);

    //��ӡƾ��
    static void printVoucher(const Account::Transaction &transaction);

    //����������ʷ��¼
    static void exportTransactionHistory(const vector<Account::Transaction> &transactionHistory);
};


#endif
