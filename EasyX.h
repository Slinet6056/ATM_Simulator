#ifndef ATM_SIMULATOR_EASYX_H
#define ATM_SIMULATOR_EASYX_H

#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

//三种预设的颜色
#define myBLACK RGB(75, 74, 73)                                      //自定义的深色（黑色）
#define myWHITE RGB(255, 253, 249)                                   //自定义的浅色（白色）
#define BKCOLOR RGB(247, 238, 214)                                   //窗口背景颜色

//数字输入面板的三种输入模式
#define MODE_ID 1                                                    //卡号输入模式
#define MODE_PASSWORD 2                                              //密码输入模式
#define MODE_AMOUNT 3                                                //金额输入模式

//该类用于图形界面的显示
class EasyX {

    LOGFONT f{};                                                     //用于设置字体样式
    RECT r{};                                                        //用于设置矩形区域范围
    MOUSEMSG m{};                                                    //用于获取鼠标输入事件

public:
    //类的构造函数
    EasyX();

    //绘制登录界面
    void showSignInMenu();

    //获取登录界面用户选择
    int getSignInMenuSelection();

    //绘制主菜单，参数分别为当前用户姓名、是否为管理员账户
    void showMainMenu(const string &name, bool isAdmin);

    //获取主菜单用户选择
    int getMainMenuSelection();

    //绘制账户管理模块菜单，参数用于判断是否为管理员账户
    void showAccountMenu(bool isAdmin);

    //获取账户管理模块菜单用户选择，参数用于判断是非为管理员账户
    int getAccountMenuSelection(bool isAdmin);

    //绘制金额操作模块菜单
    void showTransactionMenu();

    //获取金额操作模块菜单用户选择
    int getTransactionMenuSelection();

    //绘制信息查询模块菜单
    void showInformationMenu();

    //获取信息查询模块菜单用户选择
    int getInformationMenuSelection();

    //绘制数字输入面板（用于用户输入卡号、密码、金额）
    void showNumberInputPanel();

    //输入数字，参数分别为输入模式（MODE_ID / MODE_PASSWORD / MODE_AMOUNT）、未输入时候窗口中的提示文字
    //功能并不完善，不同模式下被禁用的按键与可用的按键没有显示上的区分，有待改进
    string inputNumber(int type, LPCSTR prompt);

    //绘制错误窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
    void error(LPCSTR errorMsg1, LPCSTR errorMsg2 = _T(""));

    //绘制提示窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
    void tip(LPCSTR tipMsg1, LPCSTR tipMsg2 = _T(""));

    //绘制确认窗口，两个参数为窗口中显示的两行文字（第二行字号略小于第一行）
    int confirm(LPCSTR confirmMsg1, LPCSTR confirmMsg2 = _T(""));

    //使用弹出式对话框获取用户输入（用于管理员输入卡号、密码、金额），参数为输入对话框中的提示文字
    static string inputBox(LPCTSTR prompt);

private:
    //获取用户在数字输入面板中点击的按钮代号
    char getNumberSelection();

    //用于在数字输入面板的显示屏中显示数字（或文字），参数分别为文字字号和要显示的内容
    void showNumber(int textHeight, LPCSTR str);

    //绘制预设样式的按钮，参数分别为按钮样式编号、按钮左部x坐标、按钮顶部y坐标、按钮右部x坐标、按钮底部y坐标、按钮中的文字
    //按钮编号：1-双实线边框白色按钮；2-双实线边框黑色按钮；3-单实线边框白色按钮；4-单实线边框黑色按钮
    void printButton(int style, int left, int top, int right, int bottom, LPCSTR str);
};


#endif
