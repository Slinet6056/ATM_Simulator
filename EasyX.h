#ifndef ATM_SIMULATOR_EASYX_H
#define ATM_SIMULATOR_EASYX_H

#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#define myBLACK RGB(75, 74, 73)
#define myWHITE RGB(255, 253, 249)
#define BKCOLOR RGB(247, 238, 214)

#define MODE_ID 1
#define MODE_PASSWORD 2
#define MODE_AMOUNT 3

class EasyX {

    LOGFONT f{};                                                     //��������������ʽ
    RECT r{};                                                        //�������þ�������Χ
    MOUSEMSG m{};                                                    //���ڻ�ȡ��������¼�

public:
    EasyX();

    //���Ƶ�¼����
    void showSignInMenu();

    //��ȡ��¼�����û�ѡ��
    int getSignInMenuSelection();

    //�������˵�
    void showMainMenu(const string &name, bool isAdmin);

    //��ȡ���˵��û�ѡ��
    int getMainMenuSelection();

    //�����˻�����ģ��
    void showAccountMenu(bool isAdmin);

    //��ȡ�˻�����ģ���û�ѡ��
    int getAccountMenuSelection(bool isAdmin);

    //���ƴ�ȡ����ת��ģ��
    void showTransactionMenu();

    //��ȡ��ȡ����ת��ģ���û�ѡ��
    int getTransactionMenuSelection();

    //������Ϣ��ѯģ��
    void showInformationMenu();

    //��ȡ��Ϣ��ѯģ���û�ѡ��
    int getInformationMenuSelection();

    //���������������
    void showNumberInputPanel();

    //�������� ��һ������Ϊ����ģʽ 1-�������� 2-�������� 3-������� �ڶ�������Ϊ��ʾ����
    string inputNumber(int type, LPCSTR prompt);

    //��ʾ������Ϣ
    void error(LPCSTR errorMsg1, LPCSTR errorMsg2 = _T(""));

    //��ʾ��ʾ��Ϣ
    void tip(LPCSTR tipMsg1, LPCSTR tipMsg2 = _T(""));

    //��ʾȷ����ʾ��
    int confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2 = _T(""));

    //ʹ�öԻ����ȡ�û�����
    static string inputBox(LPCTSTR prompt);

private:
    //��ȡ�û����������
    char getNumberSelection();

    //����Ԥ���ʽ�İ�ť
    void printButton(int style, int left, int top, int right, int bottom, LPCSTR str);

    //�����������������������������ʾ
    void showNumber(int textHeight, LPCSTR str);
};


#endif
