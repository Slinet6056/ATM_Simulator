#include "Account.h"

int Account::changePassword(const string &newPassword) {
    if (newPassword == password) return -1;
    password = newPassword;
    return 0;
}
