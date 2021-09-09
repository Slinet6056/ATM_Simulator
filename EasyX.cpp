#include "EasyX.h"

//��Ĺ��캯��
EasyX::EasyX() {
    initgraph(400, 600);
}

//���Ƶ�¼����
void EasyX::showSignInMenu() {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //�������������
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("A T M", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���Ƶ�¼��ť
    printButton(1, 120, 310, 280, 370, "��  ¼");

    //�����˳���ť
    printButton(1, 120, 400, 280, 460, "��  ��");
}

//��ȡ��¼�����û�ѡ��
int EasyX::getSignInMenuSelection() {
    vector<bool> buttonDown(2, false);                               //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 120, 310, 280, 370, "��  ¼");
                } else if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    buttonDown[1] = true;
                    printButton(2, 120, 400, 280, 460, "��  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 120, 310, 280, 370, "��  ¼");
                    if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 120, 400, 280, 460, "��  ��");
                    if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                        exit(0);
                    }
                }
                break;
        }
    }
}

//�������˵��������ֱ�Ϊ��ǰ�û��������Ƿ�Ϊ����Ա�˻�
void EasyX::showMainMenu(const string &name, bool isAdmin) {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    if (isAdmin) {
        gettextstyle(&f);
        f.lfHeight = 100;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, "΢���ź�");
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext("Admin", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    } else {
        gettextstyle(&f);
        f.lfHeight = 60;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, "΢���ź�");
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext(("���ã�" + name).c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    //�����˻�����ť
    printButton(1, 25, 310, 185, 370, "�˻�����");

    //���ƽ�������ť
    printButton(1, 215, 310, 375, 370, "������");

    //������Ϣ��ѯ��ť
    printButton(1, 25, 400, 185, 460, "��Ϣ��ѯ");

    //�����˳���¼��ť
    printButton(1, 215, 400, 375, 460, "�˳���¼");
}

//��ȡ���˵��û�ѡ��
int EasyX::getMainMenuSelection() {
    vector<bool> buttonDown(4, false);                               //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "�˻�����");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "������");
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "��Ϣ��ѯ");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "�˳���¼");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "�˻�����");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "������");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "��Ϣ��ѯ");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "�˳���¼");
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

//�����˻�����ģ��˵������������ж��Ƿ�Ϊ����Ա�˻�
void EasyX::showAccountMenu(bool isAdmin) {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("�˻�����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //�����½��˻�������Ա���������˻����û�����ť
    if (isAdmin) {
        printButton(1, 25, 310, 185, 370, "�½��˻�");
    } else {
        printButton(1, 25, 310, 185, 370, "�����˻�");
    }

    //����ɾ���˻�������Ա����ע���˻����û�����ť
    if (isAdmin) {
        printButton(1, 215, 310, 375, 370, "ɾ���˻�");
    } else {
        printButton(1, 215, 310, 375, 370, "ע���˻�");
    }

    //�����޸����밴ť
    printButton(1, 25, 400, 185, 460, "�޸�����");

    //���Ʒ��ذ�ť
    printButton(1, 215, 400, 375, 460, "��  ��");
}

//��ȡ�˻�����ģ��˵��û�ѡ�񣬲��������ж��Ƿ�Ϊ����Ա�˻�
int EasyX::getAccountMenuSelection(bool isAdmin) {
    vector<bool> buttonDown(4, false);                               //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    if (isAdmin) {
                        printButton(2, 25, 310, 185, 370, "�½��˻�");
                    } else {
                        printButton(2, 25, 310, 185, 370, "�����˻�");
                    }
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    if (isAdmin) {
                        printButton(2, 215, 310, 375, 370, "ɾ���˻�");
                    } else {
                        printButton(2, 215, 310, 375, 370, "ע���˻�");
                    }
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "�޸�����");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "��  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    if (isAdmin) {
                        printButton(1, 25, 310, 185, 370, "�½��˻�");
                    } else {
                        printButton(1, 25, 310, 185, 370, "�����˻�");
                    }
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    if (isAdmin) {
                        printButton(1, 215, 310, 375, 370, "ɾ���˻�");
                    } else {
                        printButton(1, 215, 310, 375, 370, "ע���˻�");
                    }
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "�޸�����");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "��  ��");
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

//���ƽ�����ģ��˵�
void EasyX::showTransactionMenu() {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("������", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƴ�ť
    printButton(1, 25, 310, 185, 370, "��  ��");

    //����ȡ�ť
    printButton(1, 215, 310, 375, 370, "ȡ  ��");

    //����ת�˰�ť
    printButton(1, 25, 400, 185, 460, "ת  ��");

    //���Ʒ��ذ�ť
    printButton(1, 215, 400, 375, 460, "��  ��");
}

//��ȡ������ģ��˵��û�ѡ��
int EasyX::getTransactionMenuSelection() {
    vector<bool> buttonDown(4, false);                               //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "��  ��");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "ȡ  ��");
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "ת  ��");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "��  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "��  ��");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "ȡ  ��");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "ת  ��");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "��  ��");
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

//������Ϣ��ѯģ��˵�
void EasyX::showInformationMenu() {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("��Ϣ��ѯ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //��������ѯ��ť
    printButton(1, 25, 310, 185, 370, "����ѯ");

    //���ƽ��׼�¼��ť
    printButton(1, 215, 310, 375, 370, "���׼�¼");

    //���Ʒ��ذ�ť
    printButton(1, 120, 400, 280, 460, "��  ��");
}

//��ȡ��Ϣ��ѯģ��˵��û�ѡ��
int EasyX::getInformationMenuSelection() {
    vector<bool> buttonDown(3, false);                               //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "����ѯ");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "���׼�¼");
                } else if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 120, 400, 280, 460, "��  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "����ѯ");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "���׼�¼");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 120, 400, 280, 460, "��  ��");
                    if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                        return 3;
                    }
                }
                break;
        }
    }
}

//��������������壨�����û����뿨�š����롢��
void EasyX::showNumberInputPanel() {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //����������ʾ��
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //����0~9���ְ�ť��С���㰴ť��ȷ���˸���Լ���X����ť��Ŀǰ��δʹ�ã�δ���������������֤�������Ϊ���ؼ�ʹ�ã�
    printButton(3, 30, 190, 130, 250, "1");
    printButton(3, 150, 190, 250, 250, "2");
    printButton(3, 270, 190, 370, 250, "3");
    printButton(3, 30, 265, 130, 325, "4");
    printButton(3, 150, 265, 250, 325, "5");
    printButton(3, 270, 265, 370, 325, "6");
    printButton(3, 30, 340, 130, 400, "7");
    printButton(3, 150, 340, 250, 400, "8");
    printButton(3, 270, 340, 370, 400, "9");
    printButton(3, 30, 415, 130, 475, ".");
    printButton(3, 150, 415, 250, 475, "0");
    printButton(3, 270, 415, 370, 475, "X");
    printButton(3, 30, 490, 190, 550, "�˸�");
    printButton(3, 210, 490, 370, 550, "ȷ��");
}

//�������֣������ֱ�Ϊ����ģʽ��MODE_ID / MODE_PASSWORD / MODE_AMOUNT����δ����ʱ�򴰿��е���ʾ����
//���ܲ������ƣ���ͬģʽ�±����õİ�������õİ���û����ʾ�ϵ����֣��д��Ľ�
string EasyX::inputNumber(int type, LPCSTR prompt) {
    string ans;                                                      //���ڴ����û���������ݣ��������ƺ����Ǻ�����
    char selectedNum;                                                //���ڽ���getNumberSelection�������ص��û������������

    //��������ģʽ���û�������������ƣ�ͬʱ����showNumber�������������ʾ���ϵ����ݣ����շ���������
    //��������ģʽ��ֻ�����������֣����Ȳ�������19λ
    //��������ģʽ��ֻ�����������֣����ȱ���Ϊ6λ�ſɵ��ȷ����ͬʱ�����ʾ������Բ��������֣�����ʾ��ʵ����
    //�������ģʽ�������������ֺ�С���㣬���Ȳ�������8λ����ĳЩ����½��ò��ְ�����ȷ��������ȷ�����ָ�ʽ
    switch (type) { // NOLINT(hicpp-multiway-paths-covered)
        case 1:
            showNumber(50, prompt);
            while (selectedNum = getNumberSelection(), selectedNum != 'c' || ans.empty()) {
                if (selectedNum >= '0' && selectedNum <= '9' && ans.size() < 19) {
                    ans += selectedNum;
                    showNumber(40, ans.c_str());
                } else if (selectedNum == 'b' && !ans.empty()) {
                    ans.pop_back();
                    if (ans.empty()) {
                        showNumber(50, prompt);
                    } else {
                        showNumber(40, ans.c_str());
                    }
                }
            }
            return ans;
        case 2:
            showNumber(50, prompt);
            while (selectedNum = getNumberSelection(), selectedNum != 'c' || ans.size() != 6) {
                if (selectedNum >= '0' && selectedNum <= '9' && ans.size() < 6) {
                    ans += selectedNum;
                    string display = "��";
                    for (int i = 0; i < ans.size() - 1; ++i)
                        display += "  ��";
                    showNumber(80, display.c_str());
                } else if (selectedNum == 'b' && !ans.empty()) {
                    ans.pop_back();
                    if (ans.empty()) {
                        showNumber(50, prompt);
                    } else {
                        string display = "��";
                        for (int i = 0; i < ans.size() - 1; ++i)
                            display += "  ��";
                        showNumber(80, display.c_str());
                    }
                }
            }
            return ans;
        case 3:
            showNumber(50, prompt);
            unsigned int pointPos = 0;
            while (selectedNum = getNumberSelection(), selectedNum != 'c' || ans.back() == '.' || ans.empty()) {
                if (selectedNum >= '0' && selectedNum <= '9' && ans != "0" && ans.size() < 8) {
                    if (pointPos && ans.size() > pointPos + 2) continue;
                    ans += selectedNum;
                    showNumber(50, ("CNY " + ans).c_str());
                } else if (selectedNum == '.' && !pointPos && !ans.empty()) {
                    pointPos = ans.size();
                    ans += selectedNum;
                    showNumber(50, ("CNY " + ans).c_str());
                } else if (selectedNum == 'b' && !ans.empty()) {
                    char c = ans.back();
                    if (c == '.') {
                        pointPos = false;
                    }
                    ans.pop_back();
                    if (ans.empty()) {
                        showNumber(50, prompt);
                    } else {
                        showNumber(50, ("CNY " + ans).c_str());
                    }
                }
            }
            return ans;
    }
    return {};
}

//���ƴ��󴰿ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
void EasyX::error(LPCSTR errorMsg1, LPCSTR errorMsg2) {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƴ�����Ϣ�ı�1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(errorMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƴ�����Ϣ�ı�2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(errorMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //����ȷ����ť
    printButton(1, 120, 460, 280, 520, "ȷ  ��");

    bool buttonDown = false;                                         //��¼ȷ����ť�Ƿ񱻰���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                    buttonDown = true;
                    printButton(2, 120, 460, 280, 520, "ȷ  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown) {
                    buttonDown = false;
                    printButton(1, 120, 460, 280, 520, "ȷ  ��");
                    if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                        return;
                    }
                }
                break;
        }
    }
}

//������ʾ���ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
void EasyX::tip(LPCSTR tipMsg1, LPCSTR tipMsg2) {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("��ʾ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //������ʾ��Ϣ�ı�1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(tipMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //������ʾ��Ϣ�ı�2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(tipMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //����ȷ����ť
    printButton(1, 120, 460, 280, 520, "ȷ  ��");

    bool buttonDown = false;                                         //��¼ȷ����ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                    buttonDown = true;
                    printButton(2, 120, 460, 280, 520, "ȷ  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown) {
                    buttonDown = false;
                    printButton(1, 120, 460, 280, 520, "ȷ  ��");
                    if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                        return;
                    }
                }
                break;
        }
    }
}

//����ȷ�ϴ��ڣ���������Ϊ��������ʾ���������֣��ڶ����ֺ���С�ڵ�һ�У�
int EasyX::confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2) {
    //��մ�����ʾ
    setbkcolor(BKCOLOR);
    cleardevice();

    //���Ʊ���
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("ȷ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //������ʾ��Ϣ�ı�1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(confirmMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //������ʾ��Ϣ�ı�2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(confirmMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //����ȡ����ť
    printButton(1, 25, 460, 185, 520, "ȡ  ��");

    //����ȷ����ť
    printButton(1, 215, 460, 375, 520, "ȷ  ��");

    vector<bool> buttonDown(2, false);                               //��¼ȡ����ȷ����ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ر�ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 460 && m.x < 185 && m.y < 520) {
                    buttonDown[0] = true;
                    printButton(2, 25, 460, 185, 520, "ȡ  ��");
                } else if (m.x > 215 && m.y > 460 && m.x < 375 && m.y < 520) {
                    buttonDown[1] = true;
                    printButton(2, 215, 460, 375, 520, "ȷ  ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 460, 185, 520, "ȡ  ��");
                    if (m.x > 25 && m.y > 460 && m.x < 185 && m.y < 520) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 460, 375, 520, "ȷ  ��");
                    if (m.x > 215 && m.y > 460 && m.x < 375 && m.y < 520) {
                        return 2;
                    }
                }
                break;
        }
    }
}

//ʹ�õ���ʽ�Ի����ȡ�û����루���ڹ���Ա���뿨�š����롢��������Ϊ����Ի����е���ʾ����
string EasyX::inputBox(LPCTSTR prompt) {
    char input[20];                                                      //�������������
    InputBox(input, 20, prompt);
    return input;
}

//��ȡ�û���������������е���İ�ť����
char EasyX::getNumberSelection() {
    vector<bool> buttonDown(14, false);                              //��¼������ť�Ƿ���

    //��ȡ����������ť�����º��ڣ�����ɿ���ť��ײ����ش��ţ����ҽ�����ͬһ����ť�ϰ��º��ɿ�����Ϊ��Ч����
    //���ڰ�ť�ϰ��������ƶ������򴰿����ɿ�����������ʾ���󣬿�ͨ���ڹ̶�ʱ������ð�ť��ɫ������������д��޸�
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                    buttonDown[1] = true;
                    printButton(4, 30, 190, 130, 250, "1");
                } else if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                    buttonDown[2] = true;
                    printButton(4, 150, 190, 250, 250, "2");
                } else if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                    buttonDown[3] = true;
                    printButton(4, 270, 190, 370, 250, "3");
                } else if (m.x > 30 && m.y > 265 && m.x < 130 && m.y < 325) {
                    buttonDown[4] = true;
                    printButton(4, 30, 265, 130, 325, "4");
                } else if (m.x > 150 && m.y > 265 && m.x < 250 && m.y < 325) {
                    buttonDown[5] = true;
                    printButton(4, 150, 265, 250, 325, "5");
                } else if (m.x > 270 && m.y > 265 && m.x < 370 && m.y < 325) {
                    buttonDown[6] = true;
                    printButton(4, 270, 265, 370, 325, "6");
                } else if (m.x > 30 && m.y > 340 && m.x < 130 && m.y < 400) {
                    buttonDown[7] = true;
                    printButton(4, 30, 340, 130, 400, "7");
                } else if (m.x > 150 && m.y > 340 && m.x < 250 && m.y < 400) {
                    buttonDown[8] = true;
                    printButton(4, 150, 340, 250, 400, "8");
                } else if (m.x > 270 && m.y > 340 && m.x < 370 && m.y < 400) {
                    buttonDown[9] = true;
                    printButton(4, 270, 340, 370, 400, "9");
                } else if (m.x > 30 && m.y > 415 && m.x < 130 && m.y < 475) {
                    buttonDown[11] = true;
                    printButton(4, 30, 415, 130, 475, ".");
                } else if (m.x > 150 && m.y > 415 && m.x < 250 && m.y < 475) {
                    buttonDown[0] = true;
                    printButton(4, 150, 415, 250, 475, "0");
                } else if (m.x > 270 && m.y > 415 && m.x < 370 && m.y < 475) {
                    buttonDown[10] = true;
                    printButton(4, 270, 415, 370, 475, "X");
                } else if (m.x > 30 && m.y > 490 && m.x < 190 && m.y < 550) {
                    buttonDown[12] = true;
                    printButton(4, 30, 490, 190, 550, "�˸�");
                } else if (m.x > 210 && m.y > 490 && m.x < 370 && m.y < 550) {
                    buttonDown[13] = true;
                    printButton(4, 210, 490, 370, 550, "ȷ��");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(3, 30, 190, 130, 250, "1");
                    if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                        return '1';
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(3, 150, 190, 250, 250, "2");
                    if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                        return '2';
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(3, 270, 190, 370, 250, "3");
                    if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                        return '3';
                    }
                } else if (buttonDown[4]) {
                    buttonDown[4] = false;
                    printButton(3, 30, 265, 130, 325, "4");
                    if (m.x > 30 && m.y > 265 && m.x < 130 && m.y < 325) {
                        return '4';
                    }
                } else if (buttonDown[5]) {
                    buttonDown[5] = false;
                    printButton(3, 150, 265, 250, 325, "5");
                    if (m.x > 150 && m.y > 265 && m.x < 250 && m.y < 325) {
                        return '5';
                    }
                } else if (buttonDown[6]) {
                    buttonDown[6] = false;
                    printButton(3, 270, 265, 370, 325, "6");
                    if (m.x > 270 && m.y > 265 && m.x < 370 && m.y < 325) {
                        return '6';
                    }
                } else if (buttonDown[7]) {
                    buttonDown[7] = false;
                    printButton(3, 30, 340, 130, 400, "7");
                    if (m.x > 30 && m.y > 340 && m.x < 130 && m.y < 400) {
                        return '7';
                    }
                } else if (buttonDown[8]) {
                    buttonDown[8] = false;
                    printButton(3, 150, 340, 250, 400, "8");
                    if (m.x > 150 && m.y > 340 && m.x < 250 && m.y < 400) {
                        return '8';
                    }
                } else if (buttonDown[9]) {
                    buttonDown[9] = false;
                    printButton(3, 270, 340, 370, 400, "9");
                    if (m.x > 270 && m.y > 340 && m.x < 370 && m.y < 400) {
                        return '9';
                    }
                } else if (buttonDown[11]) {
                    buttonDown[11] = false;
                    printButton(3, 30, 415, 130, 475, ".");
                    if (m.x > 30 && m.y > 415 && m.x < 130 && m.y < 475) {
                        return '.';
                    }
                } else if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(3, 150, 415, 250, 475, "0");
                    if (m.x > 150 && m.y > 415 && m.x < 250 && m.y < 475) {
                        return '0';
                    }
                } else if (buttonDown[10]) {
                    buttonDown[10] = false;
                    printButton(3, 270, 415, 370, 475, "X");
                    if (m.x > 270 && m.y > 415 && m.x < 370 && m.y < 475) {
                        return 'X';
                    }
                } else if (buttonDown[12]) {
                    buttonDown[12] = false;
                    printButton(3, 30, 490, 190, 550, "�˸�");
                    if (m.x > 30 && m.y > 490 && m.x < 190 && m.y < 550) {
                        return 'b';
                    }
                } else if (buttonDown[13]) {
                    buttonDown[13] = false;
                    printButton(3, 210, 490, 370, 550, "ȷ��");
                    if (m.x > 210 && m.y > 490 && m.x < 370 && m.y < 550) {
                        return 'c';
                    }
                }
                break;
        }
    }
}

//��������������������ʾ������ʾ���֣������֣��������ֱ�Ϊ�����ֺź�Ҫ��ʾ������
void EasyX::showNumber(int textHeight, LPCSTR str) {
    //������ʾ�����
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //������ʾ���е�����
    gettextstyle(&f);
    f.lfHeight = textHeight;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "΢���ź�");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {20, 50, 380, 140};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//����Ԥ����ʽ�İ�ť�������ֱ�Ϊ��ť��ʽ��š���ť��x���ꡢ��ť����y���ꡢ��ť�Ҳ�x���ꡢ��ť�ײ�y���ꡢ��ť�е�����
//��ť��ţ�1-˫ʵ�߱߿��ɫ��ť��2-˫ʵ�߱߿��ɫ��ť��3-��ʵ�߱߿��ɫ��ť��4-��ʵ�߱߿��ɫ��ť
void EasyX::printButton(int style, int left, int top, int right, int bottom, LPCSTR str) {
    switch (style) { // NOLINT(hicpp-multiway-paths-covered)
        case 1:
            setfillcolor(myWHITE);
            solidroundrect(left, top, right, bottom, 25, 25);
            setlinecolor(myBLACK);
            setlinestyle(PS_SOLID, 3);
            setbkcolor(myWHITE);
            roundrect(left + 1, top + 1, right - 1, bottom - 1, 24, 24);
            roundrect(left + 7, top + 7, right - 7, bottom - 7, 18, 18);
            gettextstyle(&f);
            f.lfHeight = 35;
            f.lfQuality = ANTIALIASED_QUALITY;
            _tcscpy_s(f.lfFaceName, "΢���ź�");
            settextstyle(&f);
            settextcolor(myBLACK);
            setbkcolor(myWHITE);
            r = {left, top, right, bottom};
            drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            break;
        case 2:
            setfillcolor(myBLACK);
            solidroundrect(left, top, right, bottom, 25, 25);
            setlinecolor(myWHITE);
            setlinestyle(PS_SOLID, 3);
            setbkcolor(myBLACK);
            roundrect(left + 4, top + 4, right - 4, bottom - 4, 20, 20);
            gettextstyle(&f);
            f.lfHeight = 35;
            f.lfQuality = ANTIALIASED_QUALITY;
            _tcscpy_s(f.lfFaceName, "΢���ź�");
            settextstyle(&f);
            settextcolor(myWHITE);
            setbkcolor(myBLACK);
            r = {left, top, right, bottom};
            drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            break;
        case 3:
            setfillcolor(myWHITE);
            solidroundrect(left, top, right, bottom, 25, 25);
            setlinecolor(myBLACK);
            setlinestyle(PS_SOLID, 3);
            setbkcolor(myWHITE);
            roundrect(left + 1, top + 1, right - 1, bottom - 1, 25, 25);
            gettextstyle(&f);
            f.lfHeight = 35;
            f.lfQuality = ANTIALIASED_QUALITY;
            _tcscpy_s(f.lfFaceName, "΢���ź�");
            settextstyle(&f);
            settextcolor(myBLACK);
            setbkcolor(myWHITE);
            r = {left, top, right, bottom};
            drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            break;
        case 4:
            setfillcolor(myBLACK);
            solidroundrect(left, top, right, bottom, 25, 25);
            gettextstyle(&f);
            f.lfHeight = 35;
            f.lfQuality = ANTIALIASED_QUALITY;
            _tcscpy_s(f.lfFaceName, "΢���ź�");
            settextstyle(&f);
            settextcolor(myWHITE);
            setbkcolor(myBLACK);
            r = {left, top, right, bottom};
            drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            break;
    }
}
