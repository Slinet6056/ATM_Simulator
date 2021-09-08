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

    LOGFONT f{};                                                     //用于设置字体样式
    RECT r{};                                                        //用于设置矩形区域范围
    MOUSEMSG m{};                                                    //用于获取鼠标输入事件

public:
    EasyX();

    //绘制登录界面
    void showSignInMenu();

    //获取登录界面用户选择
    int getSignInMenuSelection();

    //绘制主菜单
    void showMainMenu(const string &name, bool isAdmin);

    //获取主菜单用户选择
    int getMainMenuSelection();

    //绘制账户管理模块
    void showAccountMenu(bool isAdmin);

    //获取账户管理模块用户选择
    int getAccountMenuSelection(bool isAdmin);

    //绘制存取款与转账模块
    void showTransactionMenu();

    //获取存取款与转账模块用户选择
    int getTransactionMenuSelection();

    //绘制信息查询模块
    void showInformationMenu();

    //获取信息查询模块用户选择
    int getInformationMenuSelection();

    //绘制数字输入面板
    void showNumberInputPanel();

    //输入数字 第一个参数为输入模式 1-卡号输入 2-密码输入 3-金额输入 第二个参数为提示文字
    string inputNumber(int type, LPCSTR prompt);

    //显示错误信息
    void error(LPCSTR errorMsg1, LPCSTR errorMsg2 = _T(""));

    //显示提示信息
    void tip(LPCSTR tipMsg1, LPCSTR tipMsg2 = _T(""));

    //显示确认提示框
    int confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2 = _T(""));

    //使用对话框获取用户输入
    static string inputBox(LPCTSTR prompt);

private:
    //获取用户点击的数字
    char getNumberSelection();

    //绘制预设格式的按钮
    void printButton(int style, int left, int top, int right, int bottom, LPCSTR str);

    //控制数字输入面板中已输入数字显示
    void showNumber(int textHeight, LPCSTR str);
};


#endif
