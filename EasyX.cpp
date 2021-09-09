#include "EasyX.h"

//类的构造函数
EasyX::EasyX() {
    initgraph(400, 600);
}

//绘制登录界面
void EasyX::showSignInMenu() {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制主界面标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("A T M", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制登录按钮
    printButton(1, 120, 310, 280, 370, "登  录");

    //绘制退出按钮
    printButton(1, 120, 400, 280, 460, "退  出");
}

//获取登录界面用户选择
int EasyX::getSignInMenuSelection() {
    vector<bool> buttonDown(2, false);                               //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制主菜单，参数分别为当前用户姓名、是否为管理员账户
void EasyX::showMainMenu(const string &name, bool isAdmin) {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
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

    //绘制账户管理按钮
    printButton(1, 25, 310, 185, 370, "账户管理");

    //绘制金额操作按钮
    printButton(1, 215, 310, 375, 370, "金额操作");

    //绘制信息查询按钮
    printButton(1, 25, 400, 185, 460, "信息查询");

    //绘制退出登录按钮
    printButton(1, 215, 400, 375, 460, "退出登录");
}

//获取主菜单用户选择
int EasyX::getMainMenuSelection() {
    vector<bool> buttonDown(4, false);                               //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制账户管理模块菜单，参数用于判断是否为管理员账户
void EasyX::showAccountMenu(bool isAdmin) {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("账户管理", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制新建账户（管理员）或升级账户（用户）按钮
    if (isAdmin) {
        printButton(1, 25, 310, 185, 370, "新建账户");
    } else {
        printButton(1, 25, 310, 185, 370, "升级账户");
    }

    //绘制删除账户（管理员）或注销账户（用户）按钮
    if (isAdmin) {
        printButton(1, 215, 310, 375, 370, "删除账户");
    } else {
        printButton(1, 215, 310, 375, 370, "注销账户");
    }

    //绘制修改密码按钮
    printButton(1, 25, 400, 185, 460, "修改密码");

    //绘制返回按钮
    printButton(1, 215, 400, 375, 460, "返  回");
}

//获取账户管理模块菜单用户选择，参数用于判断是非为管理员账户
int EasyX::getAccountMenuSelection(bool isAdmin) {
    vector<bool> buttonDown(4, false);                               //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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
                    if (isAdmin) {
                        printButton(2, 215, 310, 375, 370, "删除账户");
                    } else {
                        printButton(2, 215, 310, 375, 370, "注销账户");
                    }
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
                    if (isAdmin) {
                        printButton(1, 215, 310, 375, 370, "删除账户");
                    } else {
                        printButton(1, 215, 310, 375, 370, "注销账户");
                    }
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

//绘制金额操作模块菜单
void EasyX::showTransactionMenu() {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("金额操作", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制存款按钮
    printButton(1, 25, 310, 185, 370, "存  款");

    //绘制取款按钮
    printButton(1, 215, 310, 375, 370, "取  款");

    //绘制转账按钮
    printButton(1, 25, 400, 185, 460, "转  账");

    //绘制返回按钮
    printButton(1, 215, 400, 375, 460, "返  回");
}

//获取金额操作模块菜单用户选择
int EasyX::getTransactionMenuSelection() {
    vector<bool> buttonDown(4, false);                               //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制信息查询模块菜单
void EasyX::showInformationMenu() {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 60;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 300};
    drawtext("信息查询", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制余额查询按钮
    printButton(1, 25, 310, 185, 370, "余额查询");

    //绘制交易记录按钮
    printButton(1, 215, 310, 375, 370, "交易记录");

    //绘制返回按钮
    printButton(1, 120, 400, 280, 460, "返  回");
}

//获取信息查询模块菜单用户选择
int EasyX::getInformationMenuSelection() {
    vector<bool> buttonDown(3, false);                               //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制数字输入面板（用于用户输入卡号、密码、金额）
void EasyX::showNumberInputPanel() {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制输入显示框
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //绘制0~9数字按钮、小数点按钮、确定退格键以及“X”按钮（目前并未使用，未来可用于输入身份证号码或作为返回键使用）
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

//输入数字，参数分别为输入模式（MODE_ID / MODE_PASSWORD / MODE_AMOUNT）、未输入时候窗口中的提示文字
//功能并不完善，不同模式下被禁用的按键与可用的按键没有显示上的区分，有待改进
string EasyX::inputNumber(int type, LPCSTR prompt) {
    string ans;                                                      //用于储存用户输入的内容，变量名似乎不是很贴切
    char selectedNum;                                                //用于接收getNumberSelection函数返回的用户所按按键编号

    //根据输入模式对用户的输入进行限制，同时调用showNumber函数管理面板显示屏上的内容，最终返回输入结果
    //卡号输入模式：只允许输入数字，长度不允许超过19位
    //密码输入模式：只允许输入数字，长度必须为6位才可点击确定，同时面板显示屏上以圆点代替数字，不显示真实密码
    //金额输入模式：允许输入数字和小数点，长度不允许超过8位，在某些情况下禁用部分按键以确保输入正确的数字格式
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

//绘制错误窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
void EasyX::error(LPCSTR errorMsg1, LPCSTR errorMsg2) {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("错误", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制错误信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(errorMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制错误信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(errorMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制确定按钮
    printButton(1, 120, 460, 280, 520, "确  定");

    bool buttonDown = false;                                         //记录确定按钮是否被按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制提示窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
void EasyX::tip(LPCSTR tipMsg1, LPCSTR tipMsg2) {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("提示", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制提示信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(tipMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制提示信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(tipMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制确定按钮
    printButton(1, 120, 460, 280, 520, "确  定");

    bool buttonDown = false;                                         //记录确定按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//绘制确认窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
int EasyX::confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2) {
    //清空窗口显示
    setbkcolor(BKCOLOR);
    cleardevice();

    //绘制标题
    gettextstyle(&f);
    f.lfHeight = 100;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 0, 400, 200};
    drawtext("确认", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制提示信息文本1
    gettextstyle(&f);
    f.lfHeight = 50;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 200, 400, 300};
    drawtext(confirmMsg1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制提示信息文本2
    gettextstyle(&f);
    f.lfHeight = 45;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, "微软雅黑");
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    r = {0, 300, 400, 350};
    drawtext(confirmMsg2, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制取消按钮
    printButton(1, 25, 460, 185, 520, "取  消");

    //绘制确定按钮
    printButton(1, 215, 460, 375, 520, "确  定");

    vector<bool> buttonDown(2, false);                               //记录取消与确定按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回编号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//使用弹出式对话框获取用户输入（用于管理员输入卡号、密码、金额），参数为输入对话框中的提示文字
string EasyX::inputBox(LPCTSTR prompt) {
    char input[20];                                                      //接收输入的内容
    InputBox(input, 20, prompt);
    return input;
}

//获取用户在数字输入面板中点击的按钮代号
char EasyX::getNumberSelection() {
    vector<bool> buttonDown(14, false);                              //记录各个按钮是否按下

    //获取鼠标操作，按钮被按下后变黑，鼠标松开后按钮变白并返回代号，当且仅当在同一个按钮上按下后松开才视为有效操作
    //若在按钮上按下鼠标后移动到程序窗口外松开，将引发显示错误，可通过在固定时间后重置按钮颜色解决，该问题有待修复
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

//用于在数字输入面板的显示屏中显示数字（或文字），参数分别为文字字号和要显示的内容
void EasyX::showNumber(int textHeight, LPCSTR str) {
    //绘制显示屏外框
    setfillcolor(myWHITE);
    solidroundrect(20, 50, 380, 140, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(21, 51, 379, 139, 25, 25);

    //绘制显示屏中的文字
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

//绘制预设样式的按钮，参数分别为按钮样式编号、按钮左部x坐标、按钮顶部y坐标、按钮右部x坐标、按钮底部y坐标、按钮中的文字
//按钮编号：1-双实线边框白色按钮；2-双实线边框黑色按钮；3-单实线边框白色按钮；4-单实线边框黑色按钮
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
