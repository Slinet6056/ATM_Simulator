#include "System.h"

System::System() {
    Record::loadRecord(accounts);
    for (auto &account: accounts)
        accountIndex[account.id] = &account;
}

int System::signIn() {
    return 0;
}

int System::signOut() {
    return 0;
}

int System::signUp() {

    return 0;
}
