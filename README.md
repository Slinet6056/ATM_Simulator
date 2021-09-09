# ATM仿真软件
[![wakatime](https://wakatime.com/badge/github/Slinet6056/ATM_Simulator.svg)](https://wakatime.com/badge/github/Slinet6056/ATM_Simulator)

程序由 C++ 语言编写，图形界面使用了 EasyX 图形库

账号与密码采用 MD5 加密算法加密后储存，提供加密算法的 `MD5.h` 与 `MD5.cpp` 来自 [github.com/JieweiWei/md5](https://github.com/JieweiWei/md5)

## 登录界面

有一个专门的管理员账户，账号为 `1234567890`，密码为 `123456`，可以新建账户，以及直接对账户进行操作

初次运行没有普通账户，需要管理员自己新建