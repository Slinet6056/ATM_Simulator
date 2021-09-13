#include "System.h"

//类的构造函数，从文件中加载账户信息
System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

//启动ATM模拟器，之后无限循环，直到点击退出按钮使用exit(0)结束程序
[[noreturn]] void System::start() {
    while (true) {
        signInMenu();
        mainMenu();
    }
}

//负责实现账户登录功能
int System::signIn() {
    if (currAccount || isAdmin) return ERR_ALREADYSIGNIN;

    easyX.showNumberInputPanel();

    //用于接收输入的卡号与密码
    //由于卡号要经过加密再与文件中存储的信息比对，故使用id_copy保留了一份未经加密的副本，以便使用
    string id, id_copy, password;

    id = easyX.inputNumber(MODE_ID, "请输入卡号");
    if (id == adminId) {
        password = easyX.inputNumber(MODE_PASSWORD, "请输入密码");
        if (password != adminPassword) return ERR_WRONGPASSWORD;
        isAdmin = true;

    } else {
        id_copy = id;
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;
        if (!accountIndex[id]->wrongPasswordLeft) return ERR_CARDLOCKED;

        password = easyX.inputNumber(MODE_PASSWORD, "请输入密码");
        password = MD5(password).toStr();

        //若密码输入错误，则减少一次机会
        if (accountIndex[id]->password != password) {
            --accountIndex[id]->wrongPasswordLeft;
            Record::saveRecord(accounts);
            switch (accountIndex[id]->wrongPasswordLeft) {
                case 2:
                    return ERR_WRONGPASSWORD_TWOCHANCESLEFT;
                case 1:
                    return ERR_WRONGPASSWORD_ONECHANCELEFT;
                case 0:
                    return ERR_WRONGPASSWORD_NOCHANCELEFT;
            }
        }

        //登录成功
        currAccount = accountIndex[id];
        currAccountId = id_copy;
        currAccount->wrongPasswordLeft = 3;
    }
    return 0;
}

//负责实现账户退出功能
int System::signOut() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //退出成功
    currAccount = nullptr;
    currAccountId.clear();
    isAdmin = false;
    return 0;
}

//负责实现管理员增加账户功能
int System::signUp() {
    //用于接收管理员输入的新账户卡号、姓名和密码
    string id, name, password;

    id = EasyX::inputBox("卡号：");
    id = MD5(id).toStr();
    if (accountIndex.count(id)) return ERR_INVALIDID;

    name = EasyX::inputBox("姓名：");

    password = EasyX::inputBox("密码：");
    password = MD5(password).toStr();

    //成功增加一个新账号
    Account account(id, name, password);
    accounts.push_back(account);
    accountIndex[id] = &accounts.back();

    Record::saveRecord(accounts);
    return 0;
}

//负责实现修改密码功能
int System::changePassword() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //用于接收管理员输入的账号和新密码
        string id, newPassword;

        id = EasyX::inputBox("卡号：");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //将剩余密码输入错误次数重置为3
        //注意这条语句执行早于新旧密码是否相同的判断
        //也就是说即使发现新密码和旧密码相同，密码没有修改成功，次数也会被重置
        //重置次数这个功能其实单独做一个入口比较好，但是因为不想再修改图形界面，所以就放在这里了
        accountIndex[id]->wrongPasswordLeft = 3;

        newPassword = EasyX::inputBox("新密码：");
        newPassword = MD5(newPassword).toStr();
        if (newPassword == accountIndex[id]->password) return ERR_SAMEPASSWORD;

        //密码修改成功
        accountIndex[id]->password = newPassword;

    } else {
        easyX.showNumberInputPanel();

        //用于接收用户两次输入的新密码
        string newPassword, confirmPassword;

        newPassword = easyX.inputNumber(MODE_PASSWORD, "请输入新密码");
        confirmPassword = easyX.inputNumber(MODE_PASSWORD, "确认新密码");

        if (newPassword != confirmPassword) return ERR_DIFFERENTPASSWORD;

        newPassword = MD5(newPassword).toStr();
        if (newPassword == currAccount->password) return ERR_SAMEPASSWORD;

        //密码修改成功
        currAccount->password = newPassword;
    }

    Record::saveRecord(accounts);
    return 0;
}

//负责实现账户注销功能
int System::deleteAccount() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //用于接收删除账户确认窗口的返回值，即用户（或管理员）是否确认删除账户
    int res;
    if (isAdmin) {
        //用于接收管理员输入的要删除的账号
        //由于卡号要经过加密再与文件中存储的信息比对，故使用id_copy保留了一份未经加密的副本，以便使用
        string id, id_copy;

        id = EasyX::inputBox("卡号：");
        id_copy = id;
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //确认是否删除账户
        res = easyX.confirm("删除账户", id_copy.c_str());
        if (res == 1) return CANCEL;

        //成功删除账户
        swap(*accountIndex[id], *(accounts.end() - 1));
        accounts.pop_back();
        accountIndex.erase(id);

    } else {
        easyX.showNumberInputPanel();

        //用于接收用户输入的密码
        string password;

        password = easyX.inputNumber(MODE_PASSWORD, "请输入密码");
        password = MD5(password).toStr();
        if (password != currAccount->password) return ERR_WRONGPASSWORD;

        //将double类型的余额转为string类型并只显示最多两位小数
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;

        //确认是否注销账户，并提示剩余余额
        res = easyX.confirm("注销账户", ("余额" + ss.str() + "元").c_str());
        if (res == 1) return CANCEL;

        //成功注销账户
        accountIndex.erase(currAccount->id);
        swap(*currAccount, *(accounts.end() - 1));
        accounts.pop_back();

        //退出登录
        currAccount = nullptr;
        currAccountId.clear();
    }

    Record::saveRecord(accounts);
    return 0;
}

//负责实现存款功能
int System::deposit() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //用于接收存款确认窗口的返回值，即用户（或管理员）是否确认存款
    int res;
    if (isAdmin) {
        //用于接收管理员输入的卡号与存款金额（string类型）
        string id, amount_str;

        id = EasyX::inputBox("卡号：");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        amount_str = EasyX::inputBox("存款金额：");

        //存款金额最多只显示两位小数
        double amount = stod(amount_str);
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //确认是否存款
        res = easyX.confirm("存款金额", (ss.str() + "元").c_str());
        if (res == 1) return CANCEL;

        //存款成功
        accountIndex[id]->deposit(stod(ss.str()), getTimestamp(), getCurrentTime());

    } else {
        easyX.showNumberInputPanel();

        //接收用户输入的存款金额（string类型）
        //格式在输入的时候就已控制，故不需要再调整
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "请输入存款金额");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 10000) return ERR_SINGLEAMOUNTLIMITEXCEED;
        if (stod(amount_str) + getDailyAmount(1) > 100000) return ERR_DAILYAMOUNTLIMITEXCEED;

        //确认是否存款
        res = easyX.confirm("存款金额", (amount_str + "元").c_str());
        if (res == 1) return CANCEL;

        //存款成功
        currAccount->deposit(stod(amount_str), getTimestamp(), getCurrentTime());

        //提示是否打印凭证
        res = easyX.confirm(("成功存款" + amount_str + "元").c_str(), "是否打印凭证");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("打印成功");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//负责实现取款功能
int System::withdrawal() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //用于接收取款确认窗口的返回值，即用户（或管理员）是否确认取款
    int res;
    if (isAdmin) {
        //用于接收管理员输入的卡号与取款金额（string类型）
        string id, amount_str;

        id = EasyX::inputBox("卡号：");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        amount_str = EasyX::inputBox("取款金额：");

        //将string类型的取款金额转化为double类型
        double amount = stod(amount_str);

        //检查是否余额不足
        if (amount > accountIndex[id]->balance) return ERR_INSUFFICIENTBALANCE;

        //取款金额最多只显示两位小数
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //确认是否取款
        res = easyX.confirm("取款金额", (ss.str() + "元").c_str());
        if (res == 1) return CANCEL;

        //取款成功
        accountIndex[id]->withdrawal(stod(ss.str()), getTimestamp(), getCurrentTime());
    } else {

        easyX.showNumberInputPanel();

        //接收用户输入的取款金额（string类型）
        //格式在输入的时候就已控制，故不需要再调整
        string amount_str;
        amount_str = easyX.inputNumber(MODE_AMOUNT, "请输入取款金额");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) > 5000) return ERR_SINGLEAMOUNTLIMITEXCEED;
        if (stod(amount_str) + getDailyAmount(2) > 20000) return ERR_DAILYAMOUNTLIMITEXCEED;

        //检查是否余额不足
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;

        //确认是否取款
        res = easyX.confirm("取款金额", (amount_str + "元").c_str());
        if (res == 1) return CANCEL;

        //取款成功
        currAccount->withdrawal(stod(amount_str), getTimestamp(), getCurrentTime());

        //提示是否打印凭证
        res = easyX.confirm(("成功取款" + amount_str + "元").c_str(), "是否打印凭证");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("打印成功");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//负责实现转账功能
int System::transfer() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    //用于接收转账确认窗口的返回值，即用户（或管理员）是否确认转账
    int res;
    if (isAdmin) {
        //用于接收管理员输入的转出账号、转入账号和转账金额
        //由于卡号要经过加密再与文件中存储的信息比对，故使用_copy保留了一份未经加密的副本，以便使用
        string fromId, fromId_copy, toId, toId_copy, amount_str;

        fromId = EasyX::inputBox("付款卡号：");
        fromId_copy = fromId;
        fromId = MD5(fromId).toStr();
        if (!accountIndex.count(fromId)) return ERR_INVALIDID;

        toId = EasyX::inputBox("收款卡号：");
        toId_copy = toId;
        toId = MD5(toId).toStr();
        if (!accountIndex.count(toId)) return ERR_INVALIDID;

        amount_str = EasyX::inputBox("转账金额：");

        //将string类型的转账金额转化为double类型
        double amount = stod(amount_str);

        //检查是否余额不足
        if (amount > accountIndex[fromId]->balance) return ERR_INSUFFICIENTBALANCE;

        //转账金额最多只显示两位小数
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << amount;

        //确认是否转账
        res = easyX.confirm("转账金额", (ss.str() + "元").c_str());
        if (res == 1) return CANCEL;

        //转账成功
        //这里获取的时间戳和格式化时间可能会不同，不过问题不大，时间戳只是做编号用，两者并无太大关联
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        accountIndex[fromId]->transferOut(stod(ss.str()), toId_copy, timestamp, currTime);
        accountIndex[toId]->transferIn(stod(ss.str()), fromId_copy, timestamp, currTime);

    } else {
        easyX.showNumberInputPanel();

        //用于接收用户输入的收款账号和转账金额（string类型）
        //由于卡号要经过加密再与文件中存储的信息比对，故使用toId_copy保留了一份未经加密的副本，以便使用
        string toId, toId_copy, amount_str;

        toId = easyX.inputNumber(1, "请输入对方账户");
        toId_copy = toId;
        toId = MD5(toId).toStr();
        if (!accountIndex.count(toId)) return ERR_INVALIDID;
        if (toId_copy == currAccountId) return ERR_SELFTRANSFER;

        amount_str = easyX.inputNumber(MODE_AMOUNT, "请输入转账金额");
        if (stod(amount_str) == 0) return ERR_ZEROAMOUNT;
        if (stod(amount_str) + getDailyAmount(4) > 50000) return ERR_DAILYAMOUNTLIMITEXCEED;

        //检查是否余额不足
        if (stod(amount_str) > currAccount->balance) return ERR_INSUFFICIENTBALANCE;

        //确认是否转账
        res = easyX.confirm("转账金额", (amount_str + "元").c_str());
        if (res == 1) return CANCEL;

        //转账成功
        //这里获取的时间戳和格式化时间可能会不同，不过问题不大，时间戳只是做编号用，两者并无太大关联
        auto timestamp = getTimestamp();
        auto currTime = getCurrentTime();
        currAccount->transferOut(stod(amount_str), toId_copy, getTimestamp(), getCurrentTime());
        accountIndex[toId]->transferIn(stod(amount_str), currAccountId, timestamp, currTime);

        //确认是否打印凭证
        res = easyX.confirm(("成功转账" + amount_str + "元").c_str(), "是否打印凭证");
        if (res == 2) {
            Record::printVoucher(currAccount->transactionHistory.back());
            easyX.tip("打印成功");
        }
    }

    Record::saveRecord(accounts);
    return 0;
}

//负责实现余额查询功能
int System::showBalance() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //用于接收管理员输入的卡号
        string id;
        id = EasyX::inputBox("卡号：");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //余额最多只显示两位小数
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << accountIndex[id]->balance;
        easyX.tip("余额", (ss.str() + "元").c_str());

    } else {
        //余额最多只显示两位小数
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(2) << currAccount->balance;
        easyX.tip("余额", (ss.str() + "元").c_str());
    }
    return 0;
}

//负责实现交易记录查询功能
//这里原计划是一个全新的界面，可以用滚轮上下滚动查看交易记录
//后来代码写累了，就砍掉了这个功能，变成直接用文件导出了
int System::showTransactionHistory() {
    if (!currAccount && !isAdmin) return ERR_NOTSIGNIN;

    if (isAdmin) {
        //用于接收管理员输入的卡号
        string id;
        id = EasyX::inputBox("卡号：");
        id = MD5(id).toStr();
        if (!accountIndex.count(id)) return ERR_INVALIDID;

        //导出交易记录成功
        Record::exportTransactionHistory(accountIndex[id]->transactionHistory);
        easyX.tip("交易历史记录已导出");

    } else {
        //直接导出当前账户的交易记录
        Record::exportTransactionHistory(currAccount->transactionHistory);
        easyX.tip("交易历史记录已导出");
    }
    return 0;
}

//调用EasyX类的方法显示登录界面，点击按钮可以进行登录与退出，并处理各种可能发生的错误
void System::signInMenu() {
    //用于接收进行登录操作程序后返回的结果
    int res;
    do {
        easyX.showSignInMenu();

        //获取被点击按钮的编号
        int signInMenuSelection = easyX.getSignInMenuSelection();
        if (signInMenuSelection == 1) {
            res = signIn();
            switch (res) {
                case ERR_ALREADYSIGNIN:
                    easyX.error("已处于登录状态");
                    break;
                case ERR_INVALIDID:
                    easyX.error("卡号不存在");
                    break;
                case ERR_WRONGPASSWORD:
                    easyX.error("密码错误");
                    break;
                case ERR_CARDLOCKED:
                    easyX.error("账户已锁定");
                    break;
                case ERR_WRONGPASSWORD_NOCHANCELEFT:
                    easyX.error("密码错误", "账户已锁定");
                    break;
                case ERR_WRONGPASSWORD_ONECHANCELEFT:
                    easyX.error("密码错误", "还剩1次机会");
                    break;
                case ERR_WRONGPASSWORD_TWOCHANCESLEFT:
                    easyX.error("密码错误", "还剩2次机会");
                    break;
                default:
                    break;
            }
        }
    } while (res);
}

//调用EasyX类的方法显示主菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
void System::mainMenu() {
    //获取被点击按钮的编号，4代表登出键
    int mainMenuSelection = 0;
    while (mainMenuSelection != 4) {
        //管理员的标题显示为"Admin"，而用户则是带有他们名字的欢迎语
        if (isAdmin) {
            easyX.showMainMenu("Admin", true);
        } else {
            easyX.showMainMenu(currAccount->name, false);
        }

        mainMenuSelection = easyX.getMainMenuSelection();
        switch (mainMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
            case 1: {
                //获取账户管理模块返回的结果
                int res = accountMenu();
                //这里主要作用是在用户注销账户后（res==-1）返回登录界面
                //让mainMenuSelection=4就相当于手动点了登出按钮
                if (res == -1) mainMenuSelection = 4;
                break;
            }
            case 2:
                transactionMenu();
                break;
            case 3:
                informationMenu();
                break;
            case 4: {
                //获取登出账号操作结果
                int res = signOut();
                //实际上这种类型的错误只发生过一次，是在我代码写了一半有bug的时候，平时使用应该弄不出这种错误的吧
                if (res) {
                    easyX.error("未登录账户");
                }
                break;
            }
        }
    }
}

//调用EasyX类的方法显示账户管理菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
int System::accountMenu() {
    //获取被点击按键的编号，4代表返回键，5对应的是注销账户后要回到登录界面的特殊情况
    int accountMenuSelection = 0;
    while (accountMenuSelection < 4) {
        easyX.showAccountMenu(isAdmin);

        accountMenuSelection = easyX.getAccountMenuSelection(isAdmin);
        if (isAdmin) {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //获取管理员新建账户操作结果
                    int res = signUp();
                    if (res == ERR_INVALIDID) {
                        easyX.error("账号已存在");
                    }
                    break;
                }
                case 2: {
                    //获取管理员删除账户操作结果
                    int res = deleteAccount();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    }
                    break;
                }
                case 3: {
                    //获取管理员修改密码操作结果
                    int res = changePassword();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    } else if (res == ERR_SAMEPASSWORD) {
                        easyX.error("新密码与原密码相同", "密码错误次数已重置");
                    }
                    break;
                }
                case 4:
                    //点击返回键，等下面到while判断的时候就跳出循环返回了
                    break;
            }
        } else {
            switch (accountMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1:
                    //其实用户的这个升级账户按钮是凑数的，想不出其他功能了
                    easyX.tip("请联系管理员QQ", "492829253");
                    break;
                case 2: {
                    //获取用户注销账户操作结果
                    int res = deleteAccount();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_WRONGPASSWORD) {
                        easyX.error("密码错误");
                    } else if (res == 0) {
                        accountMenuSelection = 5;
                    }
                    break;
                }
                case 3: {
                    //获取用户修改密码操作结果
                    int res = changePassword();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_DIFFERENTPASSWORD) {
                        easyX.error("两次输入密码不一致");
                    } else if (res == ERR_SAMEPASSWORD) {
                        easyX.error("新密码与原密码相同");
                    }
                    break;
                }
                case 4:
                    //点击返回键，马上到while判断的时候就跳出循环返回了
                    break;
            }
        }
    }
    //注销账户回到登录界面的特殊情况
    if (accountMenuSelection == 5) return -1;
    else return 0;
}

//调用EasyX类的方法显示金额操作菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
void System::transactionMenu() {
    //获取被点击按钮的编号，4代表返回键
    int transactionMenuSelection = 0;
    while (transactionMenuSelection != 4) {
        easyX.showTransactionMenu();

        transactionMenuSelection = easyX.getTransactionMenuSelection();
        if (isAdmin) {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //获取管理员存款操作结果
                    int res = deposit();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    }
                    break;
                }
                case 2: {
                    //获取管理员取款操作结果
                    int res = withdrawal();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("余额不足");
                    }
                    break;
                }
                case 3: {
                    //获取管理员转账操作结果
                    int res = transfer();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("余额不足");
                    }
                    break;
                }
                case 4:
                    //点击返回键，等下面到while判断的时候就跳出循环返回啦
                    break;
            }
        } else {
            switch (transactionMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //获取用户存款操作结果
                    int res = deposit();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_SINGLEAMOUNTLIMITEXCEED) {
                        easyX.error("超出单次存款金额上限", "上限为10000元");
                    } else if (res == ERR_DAILYAMOUNTLIMITEXCEED) {
                        easyX.error("超出当日存款金额上限", "上限为100000元");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("存款金额不能为0");
                    }
                    break;
                }
                case 2: {
                    //获取用户取款操作结果
                    int res = withdrawal();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_SINGLEAMOUNTLIMITEXCEED) {
                        easyX.error("超出单次取款金额上限", "上限为5000元");
                    } else if (res == ERR_DAILYAMOUNTLIMITEXCEED) {
                        easyX.error("超出当日取款金额上限", "上限为20000元");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("余额不足");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("取款金额不能为0");
                    }
                    break;
                }
                case 3: {
                    //获取用户转账操作结果
                    int res = transfer();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("对方账户不存在");
                    } else if (res == ERR_SELFTRANSFER) {
                        easyX.error("不可向自己转账");
                    } else if (res == ERR_ZEROAMOUNT) {
                        easyX.error("转账金额不能为0");
                    } else if (res == ERR_DAILYAMOUNTLIMITEXCEED) {
                        easyX.error("超出当日转账金额上限", "上限为50000元");
                    } else if (res == ERR_INSUFFICIENTBALANCE) {
                        easyX.error("余额不足");
                    }
                    break;
                }
                case 4:
                    //点击返回键，马上到while判断的时候就跳出循环返回啦
                    break;
            }
        }
    }
}

//调用EasyX类的方法显示信息查询菜单，点击按钮可以进行相应的操作，并处理各种可能发生的错误
void System::informationMenu() {
    //获取被点击按钮的编号，4代表返回键
    int informationMenuSelection = 0;
    while (informationMenuSelection != 3) {
        easyX.showInformationMenu();

        informationMenuSelection = easyX.getInformationMenuSelection();
        if (isAdmin) {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //获取管理员显示余额操作结果
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    }
                    break;
                }
                case 2: {
                    //获取管理员交易记录查询操作结果
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    }
                    break;
                }
                case 3:
                    //点击返回键，等下面到while判断的时候就跳出循环返回
                    break;
            }
        } else {
            switch (informationMenuSelection) { // NOLINT(hicpp-multiway-paths-covered)
                case 1: {
                    //获取用户显示余额操作结果
                    int res = showBalance();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    } else if (res == ERR_INVALIDID) {
                        easyX.error("卡号不存在");
                    }
                    break;
                }
                case 2: {
                    //获取用户显示交易历史记录操作结果
                    int res = showTransactionHistory();
                    if (res == ERR_NOTSIGNIN) {
                        easyX.error("未登录账户");
                    }
                    break;
                }
                case 3:
                    //点击返回键……
                    break;
            }
        }
    }
}

double System::getDailyAmount(int type) {
    //防止未登录用户账号而调用该函数意外发生
    if (!currAccount) return -1;

    //获取当前日期
    string today = getCurrentTime().substr(0, 10);

    //函数的返回值，当日特定类型的交易总额
    double ans = 0;

    for (const auto &account: currAccount->transactionHistory) {
        if (account.transactionTime.substr(0, 10) == today && account.transactionType == type) {
            ans += account.transactionAmount;
        }
    }

    return ans;
}

//获取时间戳
string System::getTimestamp() {
    //就是获取时间戳嘛
    timeb timestamp{};
    ftime(&timestamp);

    //毫秒数可能不足三位，要补上0
    stringstream ss;
    ss << setw(3) << setfill('0') << timestamp.millitm;

    return to_string(timestamp.time) + ss.str();
}

//获取格式化的当前时间（如："2021-09-09 22:02:35"）
string System::getCurrentTime() {
    //这两个变量用于获取当前时间哟
    tm currTime{};
    time_t timestamp = time(nullptr);

    localtime_s(&currTime, &timestamp);

    //用于储存最终格式化的结果
    string ans;
    //用于格式化当前时间
    stringstream ss;

    //年
    ans += to_string(1900 + currTime.tm_year) + "-";

    //月
    ss << setw(2) << setfill('0') << 1 + currTime.tm_mon;
    ans += ss.str() + "-";

    //日
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_mday;
    ans += ss.str() + " ";

    //时
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_hour;
    ans += ss.str() + ":";

    //分
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_min;
    ans += ss.str() + ":";

    //秒
    ss.str("");
    ss << setw(2) << setfill('0') << currTime.tm_sec;
    ans += ss.str();
    return ans;
}
