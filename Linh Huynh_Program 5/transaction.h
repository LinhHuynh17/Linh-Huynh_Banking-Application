/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/
#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
#include "fund.h"
using namespace std;
class Transaction {
public:
    Transaction();
    Transaction(char type, int primaryAccountId, int primaryFundId, int amount);
    Transaction(char type, int primaryAccountId, int primaryFundId, int secondaryAccountId, int secondaryFundId, int amount);
    Transaction(char type, int primaryAccountId);
    Transaction(char type, int primaryAccountId, int primaryFundId);
    Transaction(char type, int primaryAccountId, string firstName, string lastName);
    Transaction(const Transaction& src);
    Transaction& operator=(const Transaction& src);
    int GetType() const;
    int GetPrimaryAccountId() const;
    int GetPrimaryFundId() const;
    int GetSecondaryAccountId() const;
    int GetSecondaryFundId() const;
    int GetAmount() const;
    string GetFirstName() const;
    string GetLastName() const;
    bool GetError() const;
    void SetPrimaryFundId(int fundId);
    void SetAmount(int amount);
    void SetError(bool error);
    void Display();
private:
    char type_;
    int primaryAccountId_;
    int primaryFundId_;
    int secondaryAccountId_;
    int secondaryFundId_;
    int amount_;
    string firstName_;
    string lastName_;
    bool error_;
};
#endif