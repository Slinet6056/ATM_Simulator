#include "Record.h"

inline void Record::writeString(ofstream &fout, const string &s) {
    auto len = s.size();
    fout.write((const char *) &len, 4);
    fout.write(s.data(), s.size());
}

inline void Record::readString(ifstream &fin, string &s) {
    size_t len;
    fin.read((char *) &len, 4);
    char c;
    for (int i = 0; i < len; ++i) {
        fin.read(&c, 1);
        s += c;
    }
}

void Record::loadRecord(vector<Account> &accounts) {
    ifstream fin("ATM_Simulator.dat", ifstream::in | ifstream::binary);
    if (!fin) return;

    size_t n;
    fin.read((char *) &n, 4);

    for (int i = 0; i < n; ++i) {

        string id;
        readString(fin, id);

        string name;
        readString(fin, name);

        string password;
        readString(fin, password);

        double balance;
        fin.read((char *) &balance, 8);

        int wrongPasswordLeft;
        fin.read((char *) &wrongPasswordLeft, 4);

        int num;
        fin.read((char *) &num, 4);

        vector<Account::Transaction> transactionHistory;
        for (int j = 0; j < num; ++j) {

            string transactionId;
            readString(fin, transactionId);

            string transactionTime;
            readString(fin, transactionTime);

            int transactionType;
            fin.read((char *) &transactionType, 4);

            double transactionAmount;
            fin.read((char *) &transactionAmount, 8);

            string counterpartyAccount;
            readString(fin, counterpartyAccount);

            transactionHistory.push_back({transactionId, transactionTime, transactionType, transactionAmount, counterpartyAccount});
        }

        Account account(id, name, password, balance, wrongPasswordLeft, transactionHistory);
        accounts.push_back(account);
    }

    fin.close();
}

void Record::saveRecord(const vector<Account> &accounts) {
    ofstream fout("ATM_Simulator.dat", ofstream::out | ofstream::trunc | ofstream::binary);
    if (!fout) return;

    auto n = accounts.size();
    fout.write((const char *) &n, 4);

    for (const auto &account: accounts) {

        writeString(fout, account.id);

        writeString(fout, account.name);

        writeString(fout, account.password);

        fout.write((const char *) &account.balance, 8);

        fout.write((const char *) &account.wrongPasswordLeft, 4);

        auto num = account.transactionHistory.size();
        fout.write((const char *) &num, 4);

        for (const auto &transaction: account.transactionHistory) {

            writeString(fout, transaction.transactionId);

            writeString(fout, transaction.transactionTime);

            fout.write((const char *) &transaction.transactionType, 4);

            fout.write((const char *) &transaction.transactionAmount, 8);

            writeString(fout, transaction.counterpartyAccount);
        }
    }

    fout.close();
}

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