/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <vector>
#include "transaction.h"
//using namespace std;

class Account {
public:
    Account();
    Account(int id, string firstName, string lastName);
    Account(const Account& rhs);
    Account& operator=(const Account& rhs);
    ~Account();
    bool Deposit(int amount, int fundId);
    bool Withdraw(int amount, int fundId, Transaction& trans);
    void DisplayHistory(); //display all transactions
    void DisplayHistory(int fundId);  //display all transactions with fundId passed
    friend ostream& operator<<(ostream& stream, const Account& rhs);//need output operators
    int GetTotalBalance() const;
    int GetId() const;
    string GetFirstName() const;
    string GetLastName() const;
    void SetId(int idx);
    void DisplayFunds();
    Fund GetFund(int fundId) const; //return a fund with passed id
    void AddTransaction(Transaction transaction);
private:
    string firstName_;
    string lastName_;
    int id_;
    int totalBalance_;
    vector<Transaction> transactions;
    vector<Fund> funds;
};
#endif