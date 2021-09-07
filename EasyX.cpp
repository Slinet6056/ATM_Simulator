#include "EasyX.h"

EasyX::EasyX() {
    initgraph(400, 600);
}

void EasyX::showSignInMenu() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //���������
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext(_T("A T M"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //��¼��ť
    printButton(1, 120, 310, 280, 370, _T("��  ¼"));

    //�˳���ť
    printButton(1, 120, 400, 280, 460, _T("��  ��"));
}

int EasyX::getSignInMenuSelection() {
    vector<bool> buttonDown(2, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 120, 310, 280, 370, _T("��  ¼"));
                } else if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    buttonDown[1] = true;
                    printButton(2, 120, 400, 280, 460, _T("��  ��"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 120, 310, 280, 370, _T("��  ¼"));
                    if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 120, 400, 280, 460, _T("��  ��"));
                    if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                        exit(0);
                    }
                }
                break;
        }
    }
}

void EasyX::showMainMenu(const string &name, bool isAdmin) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //����
    if (isAdmin) {
        gettextstyle(&f);
        f.lfHeight = 100;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext(_T("Admin"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    } else {
        gettextstyle(&f);
        f.lfHeight = 60;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext(("���ã�" + name).c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    //�˺Ź���ť
    printButton(1, 25, 310, 185, 370, _T("�˺Ź���"));

    //��������ť
    printButton(1, 215, 310, 375, 370, _T("������"));

    //��Ϣ��ѯ��ť
    printButton(1, 25, 400, 185, 460, _T("��Ϣ��ѯ"));

    //�˳���¼��ť
    printButton(1, 215, 400, 375, 460, _T("�˳���¼"));
}

int EasyX::getMainMenuSelection() {
    vector<bool> buttonDown(4, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, _T("�˺Ź���"));
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, _T("������"));
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, _T("��Ϣ��ѯ"));
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, _T("�˳���¼"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, _T("�˺Ź���"));
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, _T("������"));
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, _T("��Ϣ��ѯ"));
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, _T("�˳���¼"));
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

void EasyX::showAccountMenu(bool isAdmin) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //����
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext(_T("�˺Ź���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //�½��˻���ť������Ա���������˻���ť���û���
    if (isAdmin) {
        printButton(1, 25, 310, 185, 370, _T("�½��˻�"));
    } else {
        printButton(1, 25, 310, 185, 370, _T("�����˻�"));
    }

    //ע���˻���ť
    printButton(1, 215, 310, 375, 370, _T("ע���˻�"));

    //�޸����밴ť
    printButton(1, 25, 400, 185, 460, _T("�޸�����"));

    //���ذ�ť
    printButton(1, 215, 400, 375, 460, _T("��  ��"));
}

int EasyX::getAccountMenuSelection(bool isAdmin) {
    vector<bool> buttonDown(4, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    if (isAdmin) {
                        printButton(2, 25, 310, 185, 370, _T("�½��˻�"));
                    } else {
                        printButton(2, 25, 310, 185, 370, _T("�����˻�"));
                    }
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, _T("ע���˻�"));
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, _T("�޸�����"));
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, _T("��  ��"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    if (isAdmin) {
                        printButton(1, 25, 310, 185, 370, _T("�½��˻�"));
                    } else {
                        printButton(1, 25, 310, 185, 370, _T("�����˻�"));
                    }
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, _T("ע���˻�"));
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, _T("�޸�����"));
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, _T("��  ��"));
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

void EasyX::showTransactionMenu() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //����
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext(_T("������"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //�˺Ź���ť
    printButton(1, 25, 310, 185, 370, _T("��  ��"));

    //��������ť
    printButton(1, 215, 310, 375, 370, _T("ȡ  ��"));

    //��Ϣ��ѯ��ť
    printButton(1, 25, 400, 185, 460, _T("ת  ��"));

    //�˳���¼��ť
    printButton(1, 215, 400, 375, 460, _T("��  ��"));
}

int EasyX::getTransactionMenuSelection() {
    vector<bool> buttonDown(4, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, _T("��  ��"));
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, _T("ȡ  ��"));
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, _T("ת  ��"));
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, _T("��  ��"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, _T("��  ��"));
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, _T("ȡ  ��"));
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, _T("ת  ��"));
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, _T("��  ��"));
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

void EasyX::showInformationMenu(bool isAdmin) {

}

int EasyX::getInformationMenuSelection() {
    return 0;
}

void EasyX::showNumberInputPanel() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //���������
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //����0~9���ְ�ť�Լ�ȷ���˸��
    printButton(3, 30, 190, 130, 250, _T("1"));
    printButton(3, 150, 190, 250, 250, _T("2"));
    printButton(3, 270, 190, 370, 250, _T("3"));
    printButton(3, 30, 265, 130, 325, _T("4"));
    printButton(3, 150, 265, 250, 325, _T("5"));
    printButton(3, 270, 265, 370, 325, _T("6"));
    printButton(3, 30, 340, 130, 400, _T("7"));
    printButton(3, 150, 340, 250, 400, _T("8"));
    printButton(3, 270, 340, 370, 400, _T("9"));
    printButton(3, 30, 415, 130, 475, _T("."));
    printButton(3, 150, 415, 250, 475, _T("0"));
    printButton(3, 270, 415, 370, 475, _T("X"));
    printButton(3, 30, 490, 190, 550, _T("�˸�"));
    printButton(3, 210, 490, 370, 550, _T("ȷ��"));
}

string EasyX::inputNumber(const int type) {
    string ans;
    char selectedNum;
    switch (type) { // NOLINT(hicpp-multiway-paths-covered)
        case 1:
            showNumber(50, _T("�����뿨��"));
            while (selectedNum = getNumberSelection(), selectedNum != 'c' || ans.empty()) {
                if (selectedNum >= '0' && selectedNum <= '9' && ans.size() < 19) {
                    ans += selectedNum;
                    showNumber(40, ans.c_str());
                } else if (selectedNum == 'b' && !ans.empty()) {
                    ans.pop_back();
                    if (ans.empty()) {
                        showNumber(50, _T("�����뿨��"));
                    } else {
                        showNumber(40, ans.c_str());
                    }
                }
            }
            return ans;
        case 2:
            showNumber(50, _T("����������"));
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
                        showNumber(50, _T("����������"));
                    } else {
                        string display = "��";
                        for (int i = 0; i < ans.size() - 1; ++i)
                            display += "  ��";
                        showNumber(80, display.c_str());
                    }
                }
            }
            return ans;
    }
    return {};
}

void EasyX::error(LPCSTR errorMsg) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //����
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //������Ϣ
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(errorMsg, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //ȷ����ť
    printButton(1, 120, 460, 280, 520, _T("ȷ  ��"));

    bool buttonDown = false;
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                    buttonDown = true;
                    printButton(2, 120, 460, 280, 520, _T("ȷ  ��"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown) {
                    buttonDown = false;
                    printButton(1, 120, 460, 280, 520, _T("ȷ  ��"));
                    if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                        return;
                    }
                }
                break;
        }
    }
}

char EasyX::getNumberSelection() {
    vector<bool> buttonDown(14, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                    buttonDown[1] = true;
                    printButton(4, 30, 190, 130, 250, _T("1"));
                } else if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                    buttonDown[2] = true;
                    printButton(4, 150, 190, 250, 250, _T("2"));
                } else if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                    buttonDown[3] = true;
                    printButton(4, 270, 190, 370, 250, _T("3"));
                } else if (m.x > 30 && m.y > 265 && m.x < 130 && m.y < 325) {
                    buttonDown[4] = true;
                    printButton(4, 30, 265, 130, 325, _T("4"));
                } else if (m.x > 150 && m.y > 265 && m.x < 250 && m.y < 325) {
                    buttonDown[5] = true;
                    printButton(4, 150, 265, 250, 325, _T("5"));
                } else if (m.x > 270 && m.y > 265 && m.x < 370 && m.y < 325) {
                    buttonDown[6] = true;
                    printButton(4, 270, 265, 370, 325, _T("6"));
                } else if (m.x > 30 && m.y > 340 && m.x < 130 && m.y < 400) {
                    buttonDown[7] = true;
                    printButton(4, 30, 340, 130, 400, _T("7"));
                } else if (m.x > 150 && m.y > 340 && m.x < 250 && m.y < 400) {
                    buttonDown[8] = true;
                    printButton(4, 150, 340, 250, 400, _T("8"));
                } else if (m.x > 270 && m.y > 340 && m.x < 370 && m.y < 400) {
                    buttonDown[9] = true;
                    printButton(4, 270, 340, 370, 400, _T("9"));
                } else if (m.x > 30 && m.y > 415 && m.x < 130 && m.y < 475) {
                    buttonDown[11] = true;
                    printButton(4, 30, 415, 130, 475, _T("."));
                } else if (m.x > 150 && m.y > 415 && m.x < 250 && m.y < 475) {
                    buttonDown[0] = true;
                    printButton(4, 150, 415, 250, 475, _T("0"));
                } else if (m.x > 270 && m.y > 415 && m.x < 370 && m.y < 475) {
                    buttonDown[10] = true;
                    printButton(4, 270, 415, 370, 475, _T("X"));
                } else if (m.x > 30 && m.y > 490 && m.x < 190 && m.y < 550) {
                    buttonDown[12] = true;
                    printButton(4, 30, 490, 190, 550, _T("�˸�"));
                } else if (m.x > 210 && m.y > 490 && m.x < 370 && m.y < 550) {
                    buttonDown[13] = true;
                    printButton(4, 210, 490, 370, 550, _T("ȷ��"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(3, 30, 190, 130, 250, _T("1"));
                    if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                        return '1';
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(3, 150, 190, 250, 250, _T("2"));
                    if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                        return '2';
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(3, 270, 190, 370, 250, _T("3"));
                    if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                        return '3';
                    }
                } else if (buttonDown[4]) {
                    buttonDown[4] = false;
                    printButton(3, 30, 265, 130, 325, _T("4"));
                    if (m.x > 30 && m.y > 265 && m.x < 130 && m.y < 325) {
                        return '4';
                    }
                } else if (buttonDown[5]) {
                    buttonDown[5] = false;
                    printButton(3, 150, 265, 250, 325, _T("5"));
                    if (m.x > 150 && m.y > 265 && m.x < 250 && m.y < 325) {
                        return '5';
                    }
                } else if (buttonDown[6]) {
                    buttonDown[6] = false;
                    printButton(3, 270, 265, 370, 325, _T("6"));
                    if (m.x > 270 && m.y > 265 && m.x < 370 && m.y < 325) {
                        return '6';
                    }
                } else if (buttonDown[7]) {
                    buttonDown[7] = false;
                    printButton(3, 30, 340, 130, 400, _T("7"));
                    if (m.x > 30 && m.y > 340 && m.x < 130 && m.y < 400) {
                        return '7';
                    }
                } else if (buttonDown[8]) {
                    buttonDown[8] = false;
                    printButton(3, 150, 340, 250, 400, _T("8"));
                    if (m.x > 150 && m.y > 340 && m.x < 250 && m.y < 400) {
                        return '8';
                    }
                } else if (buttonDown[9]) {
                    buttonDown[9] = false;
                    printButton(3, 270, 340, 370, 400, _T("9"));
                    if (m.x > 270 && m.y > 340 && m.x < 370 && m.y < 400) {
                        return '9';
                    }
                } else if (buttonDown[11]) {
                    buttonDown[11] = false;
                    printButton(3, 30, 415, 130, 475, _T("."));
                    if (m.x > 30 && m.y > 415 && m.x < 130 && m.y < 475) {
                        return '.';
                    }
                } else if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(3, 150, 415, 250, 475, _T("0"));
                    if (m.x > 150 && m.y > 415 && m.x < 250 && m.y < 475) {
                        return '0';
                    }
                } else if (buttonDown[10]) {
                    buttonDown[10] = false;
                    printButton(3, 270, 415, 370, 475, _T("X"));
                    if (m.x > 270 && m.y > 415 && m.x < 370 && m.y < 475) {
                        return 'X';
                    }
                } else if (buttonDown[12]) {
                    buttonDown[12] = false;
                    printButton(3, 30, 490, 190, 550, _T("�˸�"));
                    if (m.x > 30 && m.y > 490 && m.x < 190 && m.y < 550) {
                        return 'b';
                    }
                } else if (buttonDown[13]) {
                    buttonDown[13] = false;
                    printButton(3, 210, 490, 370, 550, _T("ȷ��"));
                    if (m.x > 210 && m.y > 490 && m.x < 370 && m.y < 550) {
                        return 'c';
                    }
                }
                break;
        }
    }
}

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
            _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
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
            _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
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
            _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
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
            _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
            settextstyle(&f);
            settextcolor(myWHITE);
            setbkcolor(myBLACK);
            r = {left, top, right, bottom};
            drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            break;
    }
}

void EasyX::showNumber(int textHeight, LPCSTR str) {
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    gettextstyle(&f);
    f.lfHeight = textHeight;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {20, 50, 380, 140};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
