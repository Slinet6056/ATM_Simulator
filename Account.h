#ifndef ATM_SIMULATOR_ACCOUNT_H
#define ATM_SIMULATOR_ACCOUNT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

//�������ڴ��浥���û��Ļ�����Ϣ�ͽ��׼�¼���ṩ�����������Ӳ�ͬ���͵Ľ��׼�¼
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

    vector<Transaction> transactionHistory;                          //��ʷ���׼�¼

    //���Ĭ�Ϲ��캯��
    Account() = default;

    //�ṩ���š�������������๹�캯����һ��Ϊ�������˺�ʱʹ��
    Account(string &id, string &name, string &password) : id(id), name(name), password(password) {}

    //�ṩȫ����Ϣ���๹�캯����һ��Ϊ�ӱ����ļ���ȡ�˻���Ϣʱʹ��
    Account(string &id, string &name, string &password, double &balance, int &wrongPasswordLeft, vector<Transaction> &transactionHistory) :
            id(id), name(name), password(password), balance(balance), wrongPasswordLeft(wrongPasswordLeft), transactionHistory(transactionHistory) {}

    //����һ�����׼�¼�������ֱ�Ϊ�������ױ�ţ���ʱ������棩������ʱ��
    void deposit(double amount, const string &timestamp, const string &currTime);

    //����һ��ȡ��׼�¼�������ֱ�Ϊȡ������ױ�ţ���ʱ������棩������ʱ��
    void withdrawal(double amount, const string &timestamp, const string &currTime);

    //����һ��ת���տ�׼�¼��ת���˻����ã��������ֱ�Ϊת�˽��Է��˺š����ױ�ţ���ʱ������棩������ʱ��
    void transferIn(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);

    //����һ��ת�˸���׼�¼��ת���˻����ã��������ֱ�Ϊת�˽��Է��˺š����ױ�ţ���ʱ������棩������ʱ��
    void transferOut(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime);
};


#endif