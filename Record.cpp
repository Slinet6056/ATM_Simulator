#include "Record.h"

void Record::loadRecord(vector<Account> &accounts) {
    ifstream fin("ATM_Simulator.dat", ifstream::in | ifstream::binary);
    if (!fin) return;

    while (!fin.eof()) {
        string id;
        fin.read(reinterpret_cast<char *>(&id), sizeof(string));

        string name;
        fin.read(reinterpret_cast<char *>(&name), sizeof(string));

        string password;
        fin.read(reinterpret_cast<char *>(&password), sizeof(string));

        double balance;
        fin.read(reinterpret_cast<char *>(&balance), sizeof(double));

        int n;
        fin.read(reinterpret_cast<char *>(&n), sizeof(int));

        vector<Account::Transaction> transactionHistory;
        for (int i = 0; i < n; ++i) {
            string transactionId;
            fin.read(reinterpret_cast<char *>(&transactionId), sizeof(string));

            string transactionTime;
            fin.read(reinterpret_cast<char *>(&transactionTime), sizeof(string));

            int transactionType;
            fin.read(reinterpret_cast<char *>(&transactionType), sizeof(int));

            double transactionMoney;
            fin.read(reinterpret_cast<char *>(&transactionMoney), sizeof(double));

            string counterpartyAccount;
            fin.read(reinterpret_cast<char *>(&counterpartyAccount), sizeof(string));

            transactionHistory.push_back({transactionId, transactionTime, transactionType, transactionMoney, counterpartyAccount});
        }

        Account account(id, name, password, balance, transactionHistory);
        accounts.push_back(account);
    }
    fin.close();
}

void Record::saveRecord(const vector<Account> &accounts) {
    ofstream fout("ATM_Simulator.dat", ofstream::out | ofstream::trunc | ofstream::binary);
    if (!fout) return;
    for (const auto &account: accounts) {
        fout.write(reinterpret_cast<const char *>(&account.id), sizeof(string));

    }
}
