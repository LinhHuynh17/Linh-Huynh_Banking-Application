/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#ifndef JOLLYBANKER_H_
#define JOLLYBANKER_H_
#include <iostream>
#include <queue>
#include "account.h"
#include "fund.h"
#include "transaction.h"
#include "BSTree.h"

class JollyBanker {
public:
    JollyBanker();
    ~JollyBanker(); // not use Dynamic allocate -> can remove destructor
    bool LoadTransactions(const string fileName);//read all transactions from text file, 
    //return true if load succesfully, otherwise return false
    void HandleTransactions(); //dequeue(delete a transaction from Queue) -> handle ->
    //load to history transactions of accounts related
    void Display();//display all accounts after transactions handled
private:
    queue<Transaction> transactionList;
    BSTree accountList; //banker's account list

};
#endif