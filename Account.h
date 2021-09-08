#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Account {
public:
    //������Ϣ
    string id;                                                       //����
    string name;                                                     //����
    string password;                                                 //����
    double balance{0};                                               //�˻����
    int wrongPasswordLeft{3};                                        //������������������

    //���ʽ��׼�¼
    struct Transaction {
        string transactionId;                                        //���ױ��
        string transactionTime;                                      //����ʱ��
        int transactionType;                                         //�������� 1-��� 2-ȡ�� 3-ת�� 4-ת��
        double transactionAmount;                                    //���׽��
        string counterpartyAccount;                                  //ת�˶Է��˺� ����ȡ����Ϊ"this"
    };

    //��ʷ���׼�¼
    vector<Transaction> transactionHistory;

    Account() = default;

    Account(string &id, string &name, string &password) : id(id), name(name), password(password) {}

    Account(string &id, string &name, string &password, double &balance, int &wrongPasswordLeft, vector<Transaction> &transactionHistory) :
            id(id), name(name), password(password), balance(balance), wrongPasswordLeft(wrongPasswordLeft), transactionHistory(transactionHistory) {}

    void deposit(double amount, const string &timestamp, const string &currTime);

    void withdrawal(double amount, const string &timestamp, const string &currTime);

    void transferIn(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);

    void transferOut(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);
};


#endif