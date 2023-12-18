/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#include "JollyBanker.h"
#include <iostream>
#include <fstream>
using namespace std;

JollyBanker::JollyBanker() {

}

JollyBanker::~JollyBanker() {

}

bool JollyBanker::LoadTransactions(const string fileName) {
    ifstream infile; //input file stream and read its contents
    infile.open(fileName); //open the file stream
    if (!infile.is_open())
    {
        return false;
    }
    char type_;
    int primaryAccountId_;
    int primaryFundId_;
    int secondaryAccountId_;
    int secondaryFundId_;
    int amount_;
    string firstName_;
    string lastName_;
    // cout << infile.eof() << endl;
    while (!infile.eof()) //if haven't read to the end of the file
    {
        infile >> type_;
        // cout << type_ << endl;
        switch (type_) {
        case 'D':
            infile >> primaryAccountId_;
            infile >> primaryFundId_;
            infile >> amount_;
            transactionList.push(Transaction(type_, primaryAccountId_, primaryFundId_, amount_));
            break;
        case 'W':
            infile >> primaryAccountId_;
            infile >> primaryFundId_;
            infile >> amount_;
            transactionList.push(Transaction(type_, primaryAccountId_, primaryFundId_, amount_));

            break;
        case 'T':
            infile >> primaryAccountId_;
            infile >> primaryFundId_;
            infile >> secondaryAccountId_;
            infile >> secondaryFundId_;
            infile >> amount_;
            transactionList.push(Transaction(type_, primaryAccountId_, primaryFundId_, secondaryAccountId_, secondaryFundId_, amount_));

            break;
        case 'A':
            infile >> primaryAccountId_;
            transactionList.push(Transaction(type_, primaryAccountId_));

            break;
        case 'F':
            infile >> primaryAccountId_;
            infile >> primaryFundId_;
            transactionList.push(Transaction(type_, primaryAccountId_, primaryFundId_));

            break;
        case 'O':
            infile >> primaryAccountId_;
            infile >> firstName_;
            infile >> lastName_;
            transactionList.push(Transaction(type_, primaryAccountId_, firstName_, lastName_));
            break;
        }
    }
    infile.close();
    return true;
}
void JollyBanker::HandleTransactions() {
    Account* account = nullptr;
    Account* account2 = nullptr;
    int amount;
    int fundId;
    bool f1, f2;
    Transaction trans2;
    while (!transactionList.empty()) {
        Transaction trans = transactionList.front(); //copy first element of queue to trans
        transactionList.pop(); //delete first element of queue
        switch (trans.GetType()) {
        case 'D':
            if (accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                //found account
                amount = trans.GetAmount();
                if (amount < 0) {
                    cerr << "ERROR: Invalid deposit amount" << endl;
                    trans.SetError(true);
                }
                else {
                    account->Deposit(amount, trans.GetPrimaryFundId());
                }
                account->AddTransaction(trans);
            }
            else {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " not found." << endl;
            }
            break;
        case 'W':
            //withdraw
            if (accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                //found account
                // variable 'account' is the account that we must handle with
                amount = trans.GetAmount(); //amount to withdraw

                if (amount < 0) {
                    cerr << "ERROR: Invalid withdraw amount" << endl;
                    trans.SetError(true);
                }
                else {
                    // W 1234 0 500
                    // amount = 500
                    trans2 = trans;
                    trans2.SetPrimaryFundId(-1);
                    if (!account->Withdraw(amount, trans.GetPrimaryFundId(), trans2)) {
                        //withdraw failed
                        trans.SetError(true);
                    }
                    else {
                        if (trans2.GetPrimaryFundId() != -1) {
                            //transfer from other fund
                            trans.SetAmount(amount - trans2.GetAmount()); //update amount of trans 1
                            account->AddTransaction(trans2);
                        }
                    }
                }
                account->AddTransaction(trans);
            }
            else {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " not found. Withdraw refused." << endl;
            }
            break;
        case 'T':
            f1 = true;
            f2 = true;
            if (!accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " not found. Transferal refused." << endl;
                f1 = false;
                trans.SetError(true);
            }
            if (!accountList.Retrieve(trans.GetSecondaryAccountId(), account2)) {
                cerr << "ERROR: Account " << trans.GetSecondaryAccountId() << " not found. Transferal refused." << endl;
                f2 = false;
                trans.SetError(true);
            }

            if (!f1 && f2) { //f1 false, f2 true
                account2->AddTransaction(trans);
            }

            if (f1 && !f2) {
                account->AddTransaction(trans);
            }

            if (f1 && f2) {
                //transfer from account1 to account2
                amount = trans.GetAmount();
                trans2 = trans;
                trans2.SetPrimaryFundId(-1);
                if (trans.GetPrimaryAccountId() == trans.GetSecondaryAccountId()) {//transfer on itself
                    if (!account->Withdraw(amount, trans.GetPrimaryFundId(), trans2)) { //if withdraw fail -> update err of trans
                        trans.SetError(true);
                    }
                    else {
                        if (!account2->Deposit(amount, trans.GetSecondaryFundId())) { // deposit fail -> update err of trans
                            trans.SetError(true);
                        }
                    }
                    if (trans2.GetPrimaryFundId() != -1) {
                        trans.SetAmount(amount - trans2.GetAmount()); //update amount of trans 1
                        account->AddTransaction(trans2);
                    }
                    account->AddTransaction(trans);

                }
                else {
                    if (!account->Withdraw(amount, trans.GetPrimaryFundId(), trans2)) { //if withdraw fail -> update err of trans
                        trans.SetError(true);
                    }
                    else {
                        if (!account2->Deposit(amount, trans.GetSecondaryFundId())) { // deposit fail -> update err of trans
                            trans.SetError(true);
                        }
                    }
                    if (trans2.GetPrimaryFundId() != -1) {
                        trans.SetAmount(amount - trans2.GetAmount()); //update amount of trans 1
                        //add transaction to both account sequentially
                        account->AddTransaction(trans);
                        account->AddTransaction(trans2);
                        account2->AddTransaction(trans);
                        account2->AddTransaction(trans2);
                    }
                    else {
                        account->AddTransaction(trans);
                        account2->AddTransaction(trans);
                    }
                }
            }
            break;
        case 'A':
            //add account
            if (accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                account->DisplayHistory();
                cout << endl;
            }
            else {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " not found. Display refused." << endl;
            }
            break;
        case 'F':
            //display by fund id
            if (accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                account->DisplayHistory(trans.GetPrimaryFundId());
                cout << endl;
            }
            else {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " not found. Display refused." << endl;
            }
            break;
        case 'O':
            if (accountList.Retrieve(trans.GetPrimaryAccountId(), account)) {
                cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " is already opened. Transaction refused." << endl;
            }
            else {
                //if the new accountID is possitive
                if (trans.GetPrimaryAccountId() > 0) {
                    account = new Account(trans.GetPrimaryAccountId(), trans.GetFirstName(), trans.GetLastName());
                    accountList.Insert(account);
                }
                // if the new accountID is negative
                else {
                    cerr << "ERROR: Account " << trans.GetPrimaryAccountId() << " is invalid. Open an account resquest refused." << endl;
                }
            }
            break;
        }
    }
}


void JollyBanker::Display() {
    cout << "FINAL BALANCES:" << endl;
    accountList.Display();
    return;
}
int main(int argc, char* argv[])
{
    JollyBanker JB;
    JB.LoadTransactions("bank_trans_in.txt");
    JB.HandleTransactions();
    JB.Display();
    
   /* if (JB.LoadTransactions(argv[1])) {
        JB.HandleTransactions();
        JB.Display();
    }
    else {
        return 0;
    }*/
}
