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
public:
    //���ļ���ȡ����
    static void loadRecord(vector<Account> &);

    void saveRecord(const vector<Account> &);
};


#endif
