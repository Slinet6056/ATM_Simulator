#include "Record.h"

//���ַ����Զ�������ʽд���ļ�������Ϊ�ļ��������Ҫд���ļ����ַ���
inline void Record::writeString(ofstream &fout, const string &s) {
    auto len = s.size();
    fout.write((const char *) &len, 4);
    fout.write(s.data(), s.size());
}

//��ȡ�Զ�������ʽд���ļ����ַ���������Ϊ�ļ��������ͽ��ն�ȡ���ݵ��ַ���������
inline void Record::readString(ifstream &fin, string &s) {
    size_t len;
    fin.read((char *) &len, 4);
    char c;
    for (int i = 0; i < len; ++i) {
        fin.read(&c, 1);
        s += c;
    }
}

//���ļ���ȡ���ݣ�����Ϊ�����������ݵ��˺�����������
void Record::loadRecord(vector<Account> &accounts) {
    ifstream fin("ATM_Simulator.dat", ifstream::in | ifstream::binary);
    if (!fin) return;

    size_t n;                                                        //��ȡ�û���
    fin.read((char *) &n, 4);

    for (int i = 0; i < n; ++i) {

        string id;                                                   //��ȡ����
        readString(fin, id);

        string name;                                                 //��ȡ����
        readString(fin, name);

        string password;                                             //��ȡ����
        readString(fin, password);

        double balance;                                              //��ȡ���
        fin.read((char *) &balance, 8);

        int wrongPasswordLeft;                                       //��ȡʣ����������������
        fin.read((char *) &wrongPasswordLeft, 4);

        int num;                                                     //��ȡ�û����׼�¼����
        fin.read((char *) &num, 4);

        vector<Account::Transaction> transactionHistory;             //���ڱ����ȡ�Ľ��׼�¼
        for (int j = 0; j < num; ++j) {

            string transactionId;                                    //��ȡ���ױ��
            readString(fin, transactionId);

            string transactionTime;                                  //��ȡ����ʱ��
            readString(fin, transactionTime);

            int transactionType;                                     //��ȡ�������ͣ����ȡ���ת�ˣ�
            fin.read((char *) &transactionType, 4);

            double transactionAmount;                                //��ȡ���׽��
            fin.read((char *) &transactionAmount, 8);

            string counterpartyAccount;                              //��ȡ���׶Է��˺ţ���Ϊ����Ϊ��ȡ����Է��˺�Ϊ"this"��
            readString(fin, counterpartyAccount);

            transactionHistory.push_back({transactionId, transactionTime, transactionType, transactionAmount, counterpartyAccount});
        }

        Account account(id, name, password, balance, wrongPasswordLeft, transactionHistory);
        accounts.push_back(account);
    }

    fin.close();
}

//������д���ļ�������Ϊ�洢�������ݵ��˺������ĳ�������
void Record::saveRecord(const vector<Account> &accounts) {
    ofstream fout("ATM_Simulator.dat", ofstream::out | ofstream::trunc | ofstream::binary);
    if (!fout) return;

    auto n = accounts.size();                                        //д���û���
    fout.write((const char *) &n, 4);

    for (const auto &account: accounts) {

        writeString(fout, account.id);                               //д�뿨��

        writeString(fout, account.name);                             //д������

        writeString(fout, account.password);                         //д������

        fout.write((const char *) &account.balance, 8);              //д�����

        fout.write((const char *) &account.wrongPasswordLeft, 4);    //д��ʣ����������������

        auto num = account.transactionHistory.size();                //д���û����׼�¼����
        fout.write((const char *) &num, 4);

        for (const auto &transaction: account.transactionHistory) {

            writeString(fout, transaction.transactionId);            //д�뽻�ױ��

            writeString(fout, transaction.transactionTime);          //д�뽻��ʱ��

            fout.write((const char *) &transaction.transactionType, 4);   //д�뽻������

            fout.write((const char *) &transaction.transactionAmount, 8); //д�뽻�׽��

            writeString(fout, transaction.counterpartyAccount);           //д�뽻�׶Է��˺�
        }
    }

    fout.close();
}

//��ӡƾ�ݣ�����ΪҪ��ӡ�ĵ������׼�¼
void Record::printVoucher(const Account::Transaction &transaction) {
    ofstream fout(transaction.transactionId + ".txt");
    fout << "���ױ�ţ�" << transaction.transactionId << endl;
    fout << "����ʱ�䣺" << transaction.transactionTime << endl;
    fout << "�������ͣ�";
    if (transaction.transactionType == 1) {
        fout << "���" << endl;
        fout << "����CNY " << transaction.transactionAmount;
    } else if (transaction.transactionType == 2) {
        fout << "ȡ��" << endl;
        fout << "ȡ���CNY " << transaction.transactionAmount;
    } else if (transaction.transactionType == 3) {
        fout << "ת���տ�" << endl;
        fout << "�տ��CNY " << transaction.transactionAmount << endl;
        fout << "�Է��˺ţ�" << transaction.counterpartyAccount;
    } else if (transaction.transactionType == 4) {
        fout << "ת�˸���" << endl;
        fout << "�����CNY " << transaction.transactionAmount << endl;
        fout << "�Է��˺ţ�" << transaction.counterpartyAccount;
    }
    fout.close();
}

//����������ʷ��¼������ΪҪ���������н��׼�¼
void Record::exportTransactionHistory(const vector<Account::Transaction> &transactionHistory) {
    ofstream fout("������ʷ��¼.txt");
    for (const auto &transaction: transactionHistory) {
        fout << "���ױ�ţ�" << transaction.transactionId << endl;
        fout << "����ʱ�䣺" << transaction.transactionTime << endl;
        fout << "�������ͣ�";
        if (transaction.transactionType == 1) {
            fout << "���" << endl;
            fout << "����CNY " << transaction.transactionAmount << endl;
        } else if (transaction.transactionType == 2) {
            fout << "ȡ��" << endl;
            fout << "ȡ���CNY " << transaction.transactionAmount << endl;
        } else if (transaction.transactionType == 3) {
            fout << "ת���տ�" << endl;
            fout << "�տ��CNY " << transaction.transactionAmount << endl;
            fout << "�Է��˺ţ�" << transaction.counterpartyAccount << endl;
        } else if (transaction.transactionType == 4) {
            fout << "ת�˸���" << endl;
            fout << "�����CNY " << transaction.transactionAmount << endl;
            fout << "�Է��˺ţ�" << transaction.counterpartyAccount << endl;
        }
        fout << endl;
    }
    fout.close();
}
