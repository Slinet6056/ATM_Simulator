#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Account {

    //������Ϣ
    string id;                                                       //����
    string name;                                                     //����
    string password;                                                 //����
    double balance;                                                  //�˻����

    //���ʽ��׼�¼
    struct Transaction {
        string id;                                                   //���ױ��
        string time;                                                 //����ʱ��
        int type;                                                    //�������� 1-��� 2-ȡ�� 3-ת��
        double money;                                                //���׽��
        string counterpartyAccount;                                  //ת�˶Է��˻�
    };

    //��ʷ���׼�¼
    vector<Transaction> transactionHistory;
};


#endif