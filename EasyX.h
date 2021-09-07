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
    void showMainMenu(const string& name, bool isAdmin);

    //��ȡ���˵��û�ѡ��
    int getMainMenuSelection();

    //�����˺Ź���ģ��
    void showAccountMenu();

    //��ȡ�˺Ź���ģ���û�ѡ��
    int getAccountMenuSelection();

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

    //�������� ����Ϊ����ģʽ 1-�������� 2-�������� 3-������� 4-���֤������
    string inputNumber(int type);

    //��ʾ���ִ�����Ϣ
    void error(LPCSTR errorMsg);

private:
    //��ȡ�û����������
    char getNumberSelection();

    //����Ԥ���ʽ�İ�ť
    void printButton(int style, int left, int top, int right, int bottom, LPCSTR str);

    //����������������е�������ʾ
    void showNumber(int textHeight, LPCSTR str);
};


#endif
