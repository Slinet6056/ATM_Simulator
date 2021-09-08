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

#define CANCEL 1
#define ERR_NOTSIGNIN -1
#define ERR_ALREADYSIGNIN -1
#define ERR_INVALIDID -2
#define ERR_WRONGPASSWORD -3
#define ERR_WRONGPASSWORD_TWOCHANCESLEFT -32
#define ERR_WRONGPASSWORD_ONECHANCELEFT -31
#define ERR_WRONGPASSWORD_NOCHANCELEFT -30
#define ERR_CARDLOCKED -4
#define ERR_SAMEPASSWORD -5
#define ERR_DIFFERENTPASSWORD -6
#define ERR_AMOUNTLIMITEXCEED -7
#define ERR_INSUFFICIENTBALANCE -8
#define ERR_ZEROAMOUNT -9

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

class System {
    vector<Account> accounts;                                        //��¼�����û�����
    unordered_map<string, Account *> accountIndex;                   //�Կ���Ϊ�������û�����
    Account *currAccount{nullptr};                                   //��ǰ��¼�û� Ϊ�����ʾδ��¼
    string currAccountId;                                            //��ǰ�û����� Ϊ�����ʾδ��¼
    EasyX easyX;                                                     //ͼ�ν�����
    bool isAdmin{false};                                             //�Ƿ�Ϊ����Ա�˺�
    const string adminId{"1234567890"};                          //����Ա�˺�ID
    const string adminPassword{"123456"};                       //����Ա�˺�����

public:
    System();

    [[noreturn]] void start();

private:
    int signIn();

    int signOut();

    int signUp();

    int changePassword();

    int deleteAccount();

    int deposit();

    int withdrawal();

    int transfer();

    int showBalance();

    int showTransactionHistory();

    void signInMenu();

    void mainMenu();

    int accountMenu();

    void transactionMenu();

    void informationMenu();

    static string getTimestamp();

    static string getCurrentTime();
};


#endif
