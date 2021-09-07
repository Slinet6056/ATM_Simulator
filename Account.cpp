#include "Account.h"

int Account::changePassword(const string &newPassword) {
    wrongPasswordLeft = 3;
    if (newPassword == password) return -1;
    password = newPassword;
    return 0;
}
