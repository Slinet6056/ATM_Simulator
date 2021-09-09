#include "Record.h"

//将字符串以二进制形式写入文件，参数为文件输出流和要写入文件的字符串
inline void Record::writeString(ofstream &fout, const string &s) {
    auto len = s.size();
    fout.write((const char *) &len, 4);
    fout.write(s.data(), s.size());
}

//读取以二进制形式写入文件的字符串，参数为文件输入流和接收读取数据的字符串的引用
inline void Record::readString(ifstream &fin, string &s) {
    size_t len;
    fin.read((char *) &len, 4);
    char c;
    for (int i = 0; i < len; ++i) {
        fin.read(&c, 1);
        s += c;
    }
}

//从文件读取数据，参数为接收所有数据的账号容器的引用
void Record::loadRecord(vector<Account> &accounts) {
    ifstream fin("ATM_Simulator.dat", ifstream::in | ifstream::binary);
    if (!fin) return;

    size_t n;                                                        //读取用户数
    fin.read((char *) &n, 4);

    for (int i = 0; i < n; ++i) {

        string id;                                                   //读取卡号
        readString(fin, id);

        string name;                                                 //读取姓名
        readString(fin, name);

        string password;                                             //读取密码
        readString(fin, password);

        double balance;                                              //读取余额
        fin.read((char *) &balance, 8);

        int wrongPasswordLeft;                                       //读取剩余密码输入错误次数
        fin.read((char *) &wrongPasswordLeft, 4);

        int num;                                                     //读取用户交易记录条数
        fin.read((char *) &num, 4);

        vector<Account::Transaction> transactionHistory;             //用于保存读取的交易记录
        for (int j = 0; j < num; ++j) {

            string transactionId;                                    //读取交易编号
            readString(fin, transactionId);

            string transactionTime;                                  //读取交易时间
            readString(fin, transactionTime);

            int transactionType;                                     //读取交易类型（存款取款或转账）
            fin.read((char *) &transactionType, 4);

            double transactionAmount;                                //读取交易金额
            fin.read((char *) &transactionAmount, 8);

            string counterpartyAccount;                              //读取交易对方账号（若为类型为存取款则对方账号为"this"）
            readString(fin, counterpartyAccount);

            transactionHistory.push_back({transactionId, transactionTime, transactionType, transactionAmount, counterpartyAccount});
        }

        Account account(id, name, password, balance, wrongPasswordLeft, transactionHistory);
        accounts.push_back(account);
    }

    fin.close();
}

//将数据写入文件，参数为存储所有数据的账号容器的常量引用
void Record::saveRecord(const vector<Account> &accounts) {
    ofstream fout("ATM_Simulator.dat", ofstream::out | ofstream::trunc | ofstream::binary);
    if (!fout) return;

    auto n = accounts.size();                                        //写入用户数
    fout.write((const char *) &n, 4);

    for (const auto &account: accounts) {

        writeString(fout, account.id);                               //写入卡号

        writeString(fout, account.name);                             //写入姓名

        writeString(fout, account.password);                         //写入密码

        fout.write((const char *) &account.balance, 8);              //写入余额

        fout.write((const char *) &account.wrongPasswordLeft, 4);    //写入剩余密码输入错误次数

        auto num = account.transactionHistory.size();                //写入用户交易记录条数
        fout.write((const char *) &num, 4);

        for (const auto &transaction: account.transactionHistory) {

            writeString(fout, transaction.transactionId);            //写入交易编号

            writeString(fout, transaction.transactionTime);          //写入交易时间

            fout.write((const char *) &transaction.transactionType, 4);   //写入交易类型

            fout.write((const char *) &transaction.transactionAmount, 8); //写入交易金额

            writeString(fout, transaction.counterpartyAccount);           //写入交易对方账号
        }
    }

    fout.close();
}

//打印凭据，参数为要打印的单条交易记录
void Record::printVoucher(const Account::Transaction &transaction) {
    ofstream fout(transaction.transactionId + ".txt");
    fout << "交易编号：" << transaction.transactionId << endl;
    fout << "交易时间：" << transaction.transactionTime << endl;
    fout << "交易类型：";
    if (transaction.transactionType == 1) {
        fout << "存款" << endl;
        fout << "存款金额：CNY " << transaction.transactionAmount;
    } else if (transaction.transactionType == 2) {
        fout << "取款" << endl;
        fout << "取款金额：CNY " << transaction.transactionAmount;
    } else if (transaction.transactionType == 3) {
        fout << "转账收款" << endl;
        fout << "收款金额：CNY " << transaction.transactionAmount << endl;
        fout << "对方账号：" << transaction.counterpartyAccount;
    } else if (transaction.transactionType == 4) {
        fout << "转账付款" << endl;
        fout << "付款金额：CNY " << transaction.transactionAmount << endl;
        fout << "对方账号：" << transaction.counterpartyAccount;
    }
    fout.close();
}

//导出交易历史记录，参数为要导出的所有交易记录
void Record::exportTransactionHistory(const vector<Account::Transaction> &transactionHistory) {
    ofstream fout("交易历史记录.txt");
    for (const auto &transaction: transactionHistory) {
        fout << "交易编号：" << transaction.transactionId << endl;
        fout << "交易时间：" << transaction.transactionTime << endl;
        fout << "交易类型：";
        if (transaction.transactionType == 1) {
            fout << "存款" << endl;
            fout << "存款金额：CNY " << transaction.transactionAmount << endl;
        } else if (transaction.transactionType == 2) {
            fout << "取款" << endl;
            fout << "取款金额：CNY " << transaction.transactionAmount << endl;
        } else if (transaction.transactionType == 3) {
            fout << "转账收款" << endl;
            fout << "收款金额：CNY " << transaction.transactionAmount << endl;
            fout << "对方账号：" << transaction.counterpartyAccount << endl;
        } else if (transaction.transactionType == 4) {
            fout << "转账付款" << endl;
            fout << "付款金额：CNY " << transaction.transactionAmount << endl;
            fout << "对方账号：" << transaction.counterpartyAccount << endl;
        }
        fout << endl;
    }
    fout.close();
}
