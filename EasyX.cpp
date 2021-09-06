#include "EasyX.h"

EasyX::EasyX() {
    initgraph(400, 600);
}

void EasyX::showSignInMenu() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //主界面标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext(_T("A T M"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //登录按钮
    printButtonStyle1_white(120, 310, 280, 370, _T("登  录"));

    //退出按钮
    printButtonStyle1_white(120, 400, 280, 460, _T("退  出"));
}

void EasyX::showMainMenu() {

}


void EasyX::showAccountMenu() {

}

void EasyX::showTransactionMenu() {

}

void EasyX::showInformationMenu() {

}

int EasyX::getSignInMenuSelection() {
    bool SignInButtonDown = false;                                    //记录登录按钮显示状态 防止按下左键后移动鼠标产生显示问题
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                //在登录按钮上按下鼠标左键 按钮变成黑色
                if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                    SignInButtonDown = true;
                    printButtonStyle1_black(120, 310, 280, 370, _T("登  录"));
                }

                //点击退出按钮
                if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    exit(0);
                }
                break;
            case WM_LBUTTONUP:
                //登录按钮恢复白色
                if (SignInButtonDown) {
                    SignInButtonDown = false;
                    printButtonStyle1_white(120, 310, 280, 370, _T("登  录"));
                    //在登录按钮上按下后松开鼠标左键
                    if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                        return 1;
                    }
                }
                break;
        }
    }
}

int EasyX::getMainMenuSelection() {
    return 0;
}

int EasyX::getAccountMenuSelection() {
    return 0;
}

int EasyX::getTransactionMenuSelection() {
    return 0;
}

int EasyX::getInformationMenuSelection() {
    return 0;
}

void EasyX::showNumberInputPanel() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制输入框
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //绘制0~9数字按钮以及退格键
    printButtonStyle2_white(30, 190, 130, 250, _T("1"));
    printButtonStyle2_white(150, 190, 250, 250, _T("2"));
    printButtonStyle2_white(270, 190, 370, 250, _T("3"));
    printButtonStyle2_white(30, 290, 130, 350, _T("4"));
    printButtonStyle2_white(150, 290, 250, 350, _T("5"));
    printButtonStyle2_white(270, 290, 370, 350, _T("6"));
    printButtonStyle2_white(30, 390, 130, 450, _T("7"));
    printButtonStyle2_white(150, 390, 250, 450, _T("8"));
    printButtonStyle2_white(270, 390, 370, 450, _T("9"));
    printButtonStyle2_white(30, 490, 130, 550, _T("X"));
    printButtonStyle2_white(150, 490, 250, 550, _T("0"));
    printButtonStyle2_white(270, 490, 370, 550, _T("←"));
}

string EasyX::inputNumber(const int type) {
    getNumberSelection();
    return {};
}

string EasyX::getNumberSelection() {
    vector<bool> buttonDown(12, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                    buttonDown[1] = true;
                    printButtonStyle2_black(30, 190, 130, 250, _T("1"));
                } else if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                    buttonDown[2] = true;
                    printButtonStyle2_black(150, 190, 250, 250, _T("2"));
                } else if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                    buttonDown[3] = true;
                    printButtonStyle2_black(270, 190, 370, 250, _T("3"));
                } else if (m.x > 30 && m.y > 290 && m.x < 130 && m.y < 350) {
                    buttonDown[4] = true;
                    printButtonStyle2_black(30, 290, 130, 350, _T("4"));
                } else if (m.x > 150 && m.y > 290 && m.x < 250 && m.y < 350) {
                    buttonDown[5] = true;
                    printButtonStyle2_black(150, 290, 250, 350, _T("5"));
                } else if (m.x > 270 && m.y > 290 && m.x < 370 && m.y < 350) {
                    buttonDown[6] = true;
                    printButtonStyle2_black(270, 290, 370, 350, _T("6"));
                } else if (m.x > 30 && m.y > 390 && m.x < 130 && m.y < 450) {
                    buttonDown[7] = true;
                    printButtonStyle2_black(30, 390, 130, 450, _T("7"));
                } else if (m.x > 150 && m.y > 390 && m.x < 250 && m.y < 450) {
                    buttonDown[8] = true;
                    printButtonStyle2_black(150, 390, 250, 450, _T("8"));
                } else if (m.x > 270 && m.y > 390 && m.x < 370 && m.y < 450) {
                    buttonDown[9] = true;
                    printButtonStyle2_black(270, 390, 370, 450, _T("9"));
                } else if (m.x > 30 && m.y > 490 && m.x < 130 && m.y < 550) {
                    buttonDown[10] = true;
                    printButtonStyle2_black(30, 490, 130, 550, _T("X"));
                } else if (m.x > 150 && m.y > 490 && m.x < 250 && m.y < 550) {
                    buttonDown[0] = true;
                    printButtonStyle2_black(150, 490, 250, 550, _T("0"));
                } else if (m.x > 270 && m.y > 490 && m.x < 370 && m.y < 550) {
                    buttonDown[11] = true;
                    printButtonStyle2_black(270, 490, 370, 550, _T("←"));
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButtonStyle2_white(30, 190, 130, 250, _T("1"));
                    if (m.x > 30 && m.y > 190 && m.x < 130 && m.y < 250) {
                        return "1";
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButtonStyle2_white(150, 190, 250, 250, _T("2"));
                    if (m.x > 150 && m.y > 190 && m.x < 250 && m.y < 250) {
                        return "2";
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButtonStyle2_white(270, 190, 370, 250, _T("3"));
                    if (m.x > 270 && m.y > 190 && m.x < 370 && m.y < 250) {
                        return "3";
                    }
                } else if (buttonDown[4]) {
                    buttonDown[4] = false;
                    printButtonStyle2_white(30, 290, 130, 350, _T("4"));
                    if (m.x > 30 && m.y > 290 && m.x < 130 && m.y < 350) {
                        return "4";
                    }
                } else if (buttonDown[5]) {
                    buttonDown[5] = false;
                    printButtonStyle2_white(150, 290, 250, 350, _T("5"));
                    if (m.x > 150 && m.y > 290 && m.x < 250 && m.y < 350) {
                        return "5";
                    }
                } else if (buttonDown[6]) {
                    buttonDown[6] = false;
                    printButtonStyle2_white(270, 290, 370, 350, _T("6"));
                    if (m.x > 270 && m.y > 290 && m.x < 370 && m.y < 350) {
                        return "6";
                    }
                } else if (buttonDown[7]) {
                    buttonDown[7] = false;
                    printButtonStyle2_white(30, 390, 130, 450, _T("7"));
                    if (m.x > 30 && m.y > 390 && m.x < 130 && m.y < 450) {
                        return "7";
                    }
                } else if (buttonDown[8]) {
                    buttonDown[8] = false;
                    printButtonStyle2_white(150, 390, 250, 450, _T("8"));
                    if (m.x > 150 && m.y > 390 && m.x < 250 && m.y < 450) {
                        return "8";
                    }
                } else if (buttonDown[9]) {
                    buttonDown[9] = false;
                    printButtonStyle2_white(270, 390, 370, 450, _T("9"));
                    if (m.x > 270 && m.y > 390 && m.x < 370 && m.y < 450) {
                        return "9";
                    }
                } else if (buttonDown[10]) {
                    buttonDown[10] = false;
                    printButtonStyle2_white(30, 490, 130, 550, _T("X"));
                    if (m.x > 30 && m.y > 490 && m.x < 130 && m.y < 550) {
                        return "X";
                    }
                } else if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButtonStyle2_white(150, 490, 250, 550, _T("0"));
                    if (m.x > 150 && m.y > 490 && m.x < 250 && m.y < 550) {
                        return "0";
                    }
                } else if (buttonDown[11]) {
                    buttonDown[11] = false;
                    printButtonStyle2_white(270, 490, 370, 550, _T("←"));
                    if (m.x > 270 && m.y > 490 && m.x < 370 && m.y < 550) {
                        return "-1";
                    }
                }
                break;
        }
    }
}

void EasyX::printButtonStyle1_white(int left, int top, int right, int bottom, LPCTSTR str) {
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
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {left, top, right, bottom};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void EasyX::printButtonStyle1_black(int left, int top, int right, int bottom, LPCTSTR str) {
    setfillcolor(myBLACK);
    solidroundrect(left, top, right, bottom, 25, 25);
    setlinecolor(myWHITE);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myBLACK);
    roundrect(left + 4, top + 4, right - 4, bottom - 4, 20, 20);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    settextstyle(&f);
    settextcolor(myWHITE);
    setbkcolor(myBLACK);
    r = {left, top, right, bottom};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void EasyX::printButtonStyle2_white(int left, int top, int right, int bottom, LPCTSTR str) {
    setfillcolor(myWHITE);
    solidroundrect(left, top, right, bottom, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(left + 1, top + 1, right - 1, bottom - 1, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {left, top, right, bottom};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void EasyX::printButtonStyle2_black(int left, int top, int right, int bottom, LPCTSTR str) {
    setfillcolor(myBLACK);
    solidroundrect(left, top, right, bottom, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    settextstyle(&f);
    settextcolor(myWHITE);
    setbkcolor(myBLACK);
    r = {left, top, right, bottom};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
