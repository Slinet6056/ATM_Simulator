#ifndef ATM_SIMULATOR_EASYX_H
#define ATM_SIMULATOR_EASYX_H

#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

//����Ԥ�����ɫ
#define myBLACK RGB(75, 74, 73)                                      //�Զ������ɫ����ɫ��
#define myWHITE RGB(255, 253, 249)                                   //�Զ����ǳɫ����ɫ��
#define BKCOLOR RGB(247, 238, 214)                                   //���ڱ�����ɫ

//��������������������ģʽ
#define MODE_ID 1                                                    //��������ģʽ
#define MODE_PASSWORD 2                                              //��������ģʽ
#define MODE_AMOUNT 3                                                //�������ģʽ

//��������ͼ�ν������ʾ
class EasyX {

    LOGFONT f{};                                                     //��������������ʽ
    RECT r{};                                                        //�������þ�������Χ
    MOUSEMSG m{};                                                    //���ڻ�ȡ��������¼�

public:
    //��Ĺ��캯��
    EasyX();

    //���Ƶ�¼����
    void showSignInMenu();

    //��ȡ��¼�����û�ѡ��
    int getSignInMenuSelection();

    //�������˵��������ֱ�Ϊ��ǰ�û��������Ƿ�Ϊ����Ա�˻�
    void showMainMenu(const string &name, bool isAdmin);

    //��ȡ���˵��û�ѡ��
    int getMainMenuSelection();

    //�����˻�����ģ��˵������������ж��Ƿ�Ϊ����Ա�˻�
    void showAccountMenu(bool isAdmin);

    //��ȡ�˻�����ģ��˵��û�ѡ�񣬲��������ж��Ƿ�Ϊ����Ա�˻�
    int getAccountMenuSelection(bool isAdmin);

    //���ƽ�����ģ��˵�
    void showTransactionMenu();

    //��ȡ������ģ��˵��û�ѡ��
    int getTransactionMenuSelection();

    //������Ϣ��ѯģ��˵�
    void showInformationMenu();

    //��ȡ��Ϣ��ѯģ��˵��û�ѡ��
    int getInformationMenuSelection();

    //��������������壨�����û����뿨�š����롢��
    void showNumberInputPanel();

    //�������֣������ֱ�Ϊ����ģʽ��MODE_ID / MODE_PASSWORD / MODE_AMOUNT����δ����ʱ�򴰿��е���ʾ����
    //���ܲ������ƣ���ͬģʽ�±����õİ�������õİ���û����ʾ�ϵ����֣��д��Ľ�
    string inputNumber(int type, LPCSTR prompt);

    //���ƴ��󴰿ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
    void error(LPCSTR errorMsg1, LPCSTR errorMsg2 = _T(""));

    //������ʾ���ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
    void tip(LPCSTR tipMsg1, LPCSTR tipMsg2 = _T(""));

    //����ȷ�ϴ��ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
    int confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2 = _T(""));

    //ʹ�õ���ʽ�Ի����ȡ�û����루���ڹ���Ա���뿨�š����롢��������Ϊ����Ի����е���ʾ����
    static string inputBox(LPCTSTR prompt);

private:
    //��ȡ�û���������������е���İ�ť����
    char getNumberSelection();

    //��������������������ʾ������ʾ���֣������֣��������ֱ�Ϊ�����ֺź�Ҫ��ʾ������
    void showNumber(int textHeight, LPCSTR str);

    //����Ԥ����ʽ�İ�ť�������ֱ�Ϊ��ť��ʽ��š���ť��x���ꡢ��ť����y���ꡢ��ť�Ҳ�x���ꡢ��ť�ײ�y���ꡢ��ť�е�����
    //��ť��ţ�1-˫ʵ�߱߿��ɫ��ť��2-˫ʵ�߱߿��ɫ��ť��3-��ʵ�߱߿��ɫ��ť��4-��ʵ�߱߿��ɫ��ť
    void printButton(int style, int left, int top, int right, int bottom, LPCSTR str);
};


#endif
