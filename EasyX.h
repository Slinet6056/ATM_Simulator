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

    LOGFONT f{};                                                     //用于设置字体样式
    RECT r{};                                                        //用于设置矩形区域范围
    MOUSEMSG m{};                                                    //用于获取鼠标输入事件

public:
    EasyX();

    //绘制登录界面
    void showSignInMenu();

    //绘制主菜单
    void showMainMenu();

    //绘制账号管理模块
    void showAccountMenu();

    //绘制存取款与转账模块
    void showTransactionMenu();

    //绘制信息查询模块
    void showInformationMenu();

    //获取登录界面用户选择
    int getSignInMenuSelection();

    //获取主菜单用户选择
    int getMainMenuSelection();

    //获取账号管理模块用户选择
    int getAccountMenuSelection();

    //获取存取款与转账模块用户选择
    int getTransactionMenuSelection();

    //获取信息查询模块用户选择
    int getInformationMenuSelection();

    //绘制数字输入面板
    void showNumberInputPanel();

    //输入数字 参数为输入模式 1-卡号输入 2-密码输入 3-金额输入
    string inputNumber(int);

    //获取用户点击的数字
    string getNumberSelection();

private:
    inline void printButtonStyle1_white(int, int, int, int, LPCTSTR);

    inline void printButtonStyle1_black(int, int, int, int, LPCTSTR);

    inline void printButtonStyle2_white(int, int, int, int, LPCTSTR);

    inline void printButtonStyle2_black(int, int, int, int, LPCTSTR);
};


#endif
