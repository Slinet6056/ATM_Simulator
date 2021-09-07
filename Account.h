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
        double transactionMoney;                                     //���׽��
        string counterpartyAccount;                                  //ת�˶Է��˻� ����ȡ����Ϊ�Լ��˻�
    };

    //��ʷ���׼�¼
    vector<Transaction> transactionHistory;

    Account() = default;

    Account(string &id, string &name, string &password) : id(id), name(name), password(password) {}

    Account(string &id, string &name, string &password, double &balance, int &wrongPasswordLeft, vector<Transaction> &transactionHistory) :
            id(id), name(name), password(password), balance(balance), wrongPasswordLeft(wrongPasswordLeft), transactionHistory(transactionHistory) {}

    int changePassword(const string &newPassword);
};


#endif