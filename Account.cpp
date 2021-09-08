#include "Account.h"

void Account::deposit(double amount, const string &timestamp, const string &currTime) {
    balance += amount;
    Transaction transaction;
    transaction.transactionId = timestamp;
    transaction.transactionTime = currTime;
    transaction.transactionType = 1;
    transaction.transactionAmount = amount;
    transaction.counterpartyAccount = "this";
    transactionHistory.push_back(transaction);
}

void Account::withdrawal(double amount, const string &timestamp, const string &currTime) {
    balance -= amount;
    Transaction transaction;
    transaction.transactionId = timestamp;
    transaction.transactionTime = currTime;
    transaction.transactionType = 2;
    transaction.transactionAmount = amount;
    transaction.counterpartyAccount = "this";
    transactionHistory.push_back(transaction);
}

void Account::transferIn(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime) {
    balance += amount;
    Transaction transaction;
    transaction.transactionId = timestamp;
    transaction.transactionTime = currTime;
    transaction.transactionType = 3;
    transaction.transactionAmount = amount;
    transaction.counterpartyAccount = counterpartyAccount;
    transactionHistory.push_back(transaction);
}

void Account::transferOut(double amount, const string &counterpartyAccount, const string &timestamp, const string &currTime) {
    balance -= amount;
    Transaction transaction;
    transaction.transactionId = timestamp;
    transaction.transactionTime = currTime;
    transaction.transactionType = 4;
    transaction.transactionAmount = amount;
    transaction.counterpartyAccount = counterpartyAccount;
    transactionHistory.push_back(transaction);
}
