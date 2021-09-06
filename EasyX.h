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

    //�������˵�
    void showMainMenu();

    //�����˺Ź���ģ��
    void showAccountMenu();

    //���ƴ�ȡ����ת��ģ��
    void showTransactionMenu();

    //������Ϣ��ѯģ��
    void showInformationMenu();

    //��ȡ��¼�����û�ѡ��
    int getSignInMenuSelection();

    //��ȡ���˵��û�ѡ��
    int getMainMenuSelection();

    //��ȡ�˺Ź���ģ���û�ѡ��
    int getAccountMenuSelection();

    //��ȡ��ȡ����ת��ģ���û�ѡ��
    int getTransactionMenuSelection();

    //��ȡ��Ϣ��ѯģ���û�ѡ��
    int getInformationMenuSelection();

    //���������������
    void showNumberInputPanel();

    //�������� ����Ϊ����ģʽ 1-�������� 2-�������� 3-�������
    string inputNumber(int);

    //��ȡ�û����������
    string getNumberSelection();

private:
    inline void printButtonStyle1_white(int, int, int, int, LPCTSTR);

    inline void printButtonStyle1_black(int, int, int, int, LPCTSTR);

    inline void printButtonStyle2_white(int, int, int, int, LPCTSTR);

    inline void printButtonStyle2_black(int, int, int, int, LPCTSTR);
};


#endif
