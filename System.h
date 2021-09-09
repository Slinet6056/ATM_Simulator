#ifndef ATM_SIMULATOR_SYSTEM_H
#define ATM_SIMULATOR_SYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <sys/timeb.h>
#include <ctime>
#include "Account.h"
#include "Record.h"
#include "EasyX.h"
#include "MD5.h"

//���ִ���״̬
#define CANCEL 1                                                     //ȡ��
#define ERR_NOTSIGNIN -1                                             //δ��¼�˻������ճ����߼���Ӧ�����˴��󣬽���ֹ�����������
#define ERR_ALREADYSIGNIN -1                                         //�ѵ�¼�˻������ճ����߼���Ӧ�����˴��󣬽���ֹ�����������
#define ERR_INVALIDID -2                                             //����Ŀ��Ų�����
#define ERR_WRONGPASSWORD -3                                         //�������
#define ERR_WRONGPASSWORD_TWOCHANCESLEFT -32                         //�û���¼ʱ�����������󣬻�ʣ���λ���
#define ERR_WRONGPASSWORD_ONECHANCELEFT -31                          //�û���¼ʱ�����������󣬻�ʣһ�λ���
#define ERR_WRONGPASSWORD_NOCHANCELEFT -30                           //�û���¼ʱ������������û��ʣ�����
#define ERR_CARDLOCKED -4                                            //�˻�������
#define ERR_SAMEPASSWORD -5                                          //�޸�����ʱ��������ԭ������ͬ
#define ERR_DIFFERENTPASSWORD -6                                     //�û��޸�����ʱ������������벻һ��
#define ERR_AMOUNTLIMITEXCEED -7                                     //�û����д�ȡ���ת��ʱ���ʽ�������
#define ERR_INSUFFICIENTBALANCE -8                                   //ȡ����ת��ʱ�˻�����
#define ERR_ZEROAMOUNT -9                                            //���ȡ���ת�˽��Ϊ��

using std::string;
using std::vector;
using std::unordered_map;
using std::stringstream;
using std::ios;
using std::setiosflags;
using std::setprecision;
using std::to_string;
using std::swap;
using std::setw;
using std::setfill;

//�������������ķ�����ʵ����AMTģ�����ĸ��ֹ���
class System {
    vector<Account> accounts;                                        //��¼�����û�����
    unordered_map<string, Account *> accountIndex;                   //�Կ���Ϊ�������û�����
    Account *currAccount{nullptr};                                   //��ǰ��¼�û���Ϊ�����ʾδ��¼
    string currAccountId;                                            //��ǰ�û����ţ�Ϊ�����ʾδ��¼
    EasyX easyX;                                                     //����һ��ͼ�ν�����
    bool isAdmin{false};                                             //�Ƿ�Ϊ����Ա�˺�
    const string adminId{"1234567890"};                              //�������Ա�˻�ID
    const string adminPassword{"123456"};                            //�������Ա�˻�����

public:
    //��Ĺ��캯�������ļ��м����˻���Ϣ
    System();

    //����ATMģ������֮������ѭ����ֱ������˳���ťʹ��exit(0)��������
    [[noreturn]] void start();

private:
    //����ʵ���˻���¼����
    int signIn();

    //����ʵ���˻��˳�����
    int signOut();

    //����ʵ�ֹ���Ա�����˻�����
    int signUp();

    //����ʵ���޸����빦��
    int changePassword();

    //����ʵ���˻�ע������
    int deleteAccount();

    //����ʵ�ִ���
    int deposit();

    //����ʵ��ȡ���
    int withdrawal();

    //����ʵ��ת�˹���
    int transfer();

    //����ʵ������ѯ����
    int showBalance();

    //����ʵ�ֽ��׼�¼��ѯ����
    //����ԭ�ƻ���һ��ȫ�µĽ��棬�����ù������¹����鿴���׼�¼
    //��������д���ˣ��Ϳ�����������ܣ����ֱ�����ļ�������
    int showTransactionHistory();

    //����EasyX��ķ�����ʾ��¼���棬�����ť���Խ��е�¼���˳�����������ֿ��ܷ����Ĵ���
    void signInMenu();

    //����EasyX��ķ�����ʾ���˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
    void mainMenu();

    //����EasyX��ķ�����ʾ�˻�����˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
    int accountMenu();

    //����EasyX��ķ�����ʾ�������˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
    void transactionMenu();

    //����EasyX��ķ�����ʾ��Ϣ��ѯ�˵��������ť���Խ�����Ӧ�Ĳ�������������ֿ��ܷ����Ĵ���
    void informationMenu();

    //��ȡʱ���
    static string getTimestamp();

    //��ȡ��ʽ���ĵ�ǰʱ�䣨�磺"2021-09-09 22:02:35"��
    //��˵�⼸��ÿ�춼д���뵽ʮһ��࣬Ҫͺ��Ҫͺ��
    static string getCurrentTime();
};


#endif
