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
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("A T M", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //登录按钮
    printButton(1, 120, 310, 280, 370, "登  录");

    //退出按钮
    printButton(1, 120, 400, 280, 460, "退  出");
}

int EasyX::getSignInMenuSelection() {
    vector<bool> buttonDown(2, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 120, 310, 280, 370, "登  录");
                } else if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    buttonDown[1] = true;
                    printButton(2, 120, 400, 280, 460, "退  出");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 120, 310, 280, 370, "登  录");
                    if (m.x > 120 && m.y > 310 && m.x < 280 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 120, 400, 280, 460, "退  出");
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

    //标题
    if (isAdmin) {
        gettextstyle(&f);
        f.lfHeight = 100;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, "微软雅黑");
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext("Admin", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    } else {
        gettextstyle(&f);
        f.lfHeight = 60;
        f.lfQuality = ANTIALIASED_QUALITY;
        _tcscpy_s(f.lfFaceName, "微软雅黑");
        settextstyle(&f);
        settextcolor(myBLACK);
        setbkcolor(BKCOLOR);
        r = {0, 0, 400, 300};
        drawtext(("您好，" + name).c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    //账户管理按钮
    printButton(1, 25, 310, 185, 370, "账户管理");

    //金额操作按钮
    printButton(1, 215, 310, 375, 370, "金额操作");

    //信息查询按钮
    printButton(1, 25, 400, 185, 460, "信息查询");

    //退出登录按钮
    printButton(1, 215, 400, 375, 460, "退出登录");
}

int EasyX::getMainMenuSelection() {
    vector<bool> buttonDown(4, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "账户管理");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "金额操作");
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "信息查询");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "退出登录");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "账户管理");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "金额操作");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "信息查询");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "退出登录");
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

    //标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("账户管理", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //新建账户按钮（管理员）或升级账户按钮（用户）
    if (isAdmin) {
        printButton(1, 25, 310, 185, 370, "新建账户");
    } else {
        printButton(1, 25, 310, 185, 370, "升级账户");
    }

    //注销账户按钮
    printButton(1, 215, 310, 375, 370, "注销账户");

    //修改密码按钮
    printButton(1, 25, 400, 185, 460, "修改密码");

    //返回按钮
    printButton(1, 215, 400, 375, 460, "返  回");
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
                        printButton(2, 25, 310, 185, 370, "新建账户");
                    } else {
                        printButton(2, 25, 310, 185, 370, "升级账户");
                    }
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "注销账户");
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "修改密码");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "返  回");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    if (isAdmin) {
                        printButton(1, 25, 310, 185, 370, "新建账户");
                    } else {
                        printButton(1, 25, 310, 185, 370, "升级账户");
                    }
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "注销账户");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "修改密码");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "返  回");
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

    //标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("金额操作", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //存款按钮
    printButton(1, 25, 310, 185, 370, "存  款");

    //取款按钮
    printButton(1, 215, 310, 375, 370, "取  款");

    //转账按钮
    printButton(1, 25, 400, 185, 460, "转  账");

    //返回按钮
    printButton(1, 215, 400, 375, 460, "返  回");
}

int EasyX::getTransactionMenuSelection() {
    vector<bool> buttonDown(4, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "存  款");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "取  款");
                } else if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 25, 400, 185, 460, "转  账");
                } else if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                    buttonDown[3] = true;
                    printButton(2, 215, 400, 375, 460, "返  回");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "存  款");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "取  款");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 25, 400, 185, 460, "转  账");
                    if (m.x > 25 && m.y > 400 && m.x < 185 && m.y < 460) {
                        return 3;
                    }
                } else if (buttonDown[3]) {
                    buttonDown[3] = false;
                    printButton(1, 215, 400, 375, 460, "返  回");
                    if (m.x > 215 && m.y > 400 && m.x < 375 && m.y < 460) {
                        return 4;
                    }
                }
                break;
        }
    }
}

void EasyX::showInformationMenu() {
    setbkcolor(BKCOLOR);
    cleardevice();

    //标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("信息查询", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //余额查询按钮
    printButton(1, 25, 310, 185, 370, "余额查询");

    //交易记录按钮
    printButton(1, 215, 310, 375, 370, "交易记录");

    //返回按钮
    printButton(1, 120, 400, 280, 460, "返  回");
}

int EasyX::getInformationMenuSelection() {
    vector<bool> buttonDown(3, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                    buttonDown[0] = true;
                    printButton(2, 25, 310, 185, 370, "余额查询");
                } else if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                    buttonDown[1] = true;
                    printButton(2, 215, 310, 375, 370, "交易记录");
                } else if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                    buttonDown[2] = true;
                    printButton(2, 120, 400, 280, 460, "返  回");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 310, 185, 370, "余额查询");
                    if (m.x > 25 && m.y > 310 && m.x < 185 && m.y < 370) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 310, 375, 370, "交易记录");
                    if (m.x > 215 && m.y > 310 && m.x < 375 && m.y < 370) {
                        return 2;
                    }
                } else if (buttonDown[2]) {
                    buttonDown[2] = false;
                    printButton(1, 120, 400, 280, 460, "返  回");
                    if (m.x > 120 && m.y > 400 && m.x < 280 && m.y < 460) {
                        return 3;
                    }
                }
                break;
        }
    }
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

    //绘制0~9数字按钮以及确定退格键
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
    printButton(3, 30, 490, 190, 550, "退格");
    printButton(3, 210, 490, 370, 550, "确定");
}

string EasyX::inputNumber(int type, LPCSTR prompt) {
    string ans;
    char selectedNum;
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
                    string display = "·";
                    for (int i = 0; i < ans.size() - 1; ++i)
                        display += "  ·";
                    showNumber(80, display.c_str());
                } else if (selectedNum == 'b' && !ans.empty()) {
                    ans.pop_back();
                    if (ans.empty()) {
                        showNumber(50, prompt);
                    } else {
                        string display = "·";
                        for (int i = 0; i < ans.size() - 1; ++i)
                            display += "  ·";
                        showNumber(80, display.c_str());
                    }
                }
            }
            return ans;
    }
    return {};
}

void EasyX::error(LPCSTR errorMsg1, LPCSTR errorMsg2) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("错误", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //错误信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(errorMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //错误信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(errorMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //确定按钮
    printButton(1, 120, 460, 280, 520, "确  定");

    bool buttonDown = false;
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                    buttonDown = true;
                    printButton(2, 120, 460, 280, 520, "确  定");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown) {
                    buttonDown = false;
                    printButton(1, 120, 460, 280, 520, "确  定");
                    if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                        return;
                    }
                }
                break;
        }
    }
}

void EasyX::tip(LPCSTR tipMsg1, LPCSTR tipMsg2) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("提示", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //提示信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(tipMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //提示信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(tipMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //确定按钮
    printButton(1, 120, 460, 280, 520, "确  定");

    bool buttonDown = false;
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                    buttonDown = true;
                    printButton(2, 120, 460, 280, 520, "确  定");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown) {
                    buttonDown = false;
                    printButton(1, 120, 460, 280, 520, "确  定");
                    if (m.x > 120 && m.y > 460 && m.x < 280 && m.y < 520) {
                        return;
                    }
                }
                break;
        }
    }
}

int EasyX::confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2) {
    setbkcolor(BKCOLOR);
    cleardevice();

    //标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("确认", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //提示信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(confirmMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //提示信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(confirmMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //取消按钮
    printButton(1, 25, 460, 185, 520, "取  消");

    //确定按钮
    printButton(1, 215, 460, 375, 520, "确  定");

    vector<bool> buttonDown(2, false);
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (m.x > 25 && m.y > 460 && m.x < 185 && m.y < 520) {
                    buttonDown[0] = true;
                    printButton(2, 25, 460, 185, 520, "取  消");
                } else if (m.x > 215 && m.y > 460 && m.x < 375 && m.y < 520) {
                    buttonDown[1] = true;
                    printButton(2, 215, 460, 375, 520, "确  定");
                }
                break;
            case WM_LBUTTONUP:
                if (buttonDown[0]) {
                    buttonDown[0] = false;
                    printButton(1, 25, 460, 185, 520, "取  消");
                    if (m.x > 25 && m.y > 460 && m.x < 185 && m.y < 520) {
                        return 1;
                    }
                } else if (buttonDown[1]) {
                    buttonDown[1] = false;
                    printButton(1, 215, 460, 375, 520, "确  定");
                    if (m.x > 215 && m.y > 460 && m.x < 375 && m.y < 520) {
                        return 2;
                    }
                }
                break;
        }
    }
}

string EasyX::inputBox(LPCTSTR prompt) {
    char input[20];
    InputBox(input, 20, prompt);
    return input;
}

char EasyX::getNumberSelection() {
    vector<bool> buttonDown(14, false);
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
                    printButton(4, 30, 490, 190, 550, "退格");
                } else if (m.x > 210 && m.y > 490 && m.x < 370 && m.y < 550) {
                    buttonDown[13] = true;
                    printButton(4, 210, 490, 370, 550, "确定");
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
                    printButton(3, 30, 490, 190, 550, "退格");
                    if (m.x > 30 && m.y > 490 && m.x < 190 && m.y < 550) {
                        return 'b';
                    }
                } else if (buttonDown[13]) {
                    buttonDown[13] = false;
                    printButton(3, 210, 490, 370, 550, "确定");
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
            _tcscpy_s(f.lfFaceName, "微软雅黑");
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
            _tcscpy_s(f.lfFaceName, "微软雅黑");
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
            _tcscpy_s(f.lfFaceName, "微软雅黑");
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
            _tcscpy_s(f.lfFaceName, "微软雅黑");
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
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {20, 50, 380, 140};
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
