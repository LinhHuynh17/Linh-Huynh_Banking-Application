/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

//#include<bits/stdc++.h> 
#include "account.h"
using namespace std;
Account::Account()
{
    id_ = -1;
    firstName_ = "";
    lastName_ = "";
    totalBalance_ = 0;
    funds.push_back(Fund(0, "Money Market", 0));
    funds.push_back(Fund(1, "Prime Money Market"));
    funds.push_back(Fund(2, "Long-Term Bond"));
    funds.push_back(Fund(3, "Short-Term Bond"));
    funds.push_back(Fund(4, "500 Index Fund"));
    funds.push_back(Fund(5, "Capital Value Fund"));
    funds.push_back(Fund(6, "Growth Equity Fund"));
    funds.push_back(Fund(7, "Growth Index Fund"));
}

Account::Account(int id, string firstName, string lastName)
{
    // this is a pointer that points to current object
    this->id_ = id;
    this->firstName_ = firstName;
    this->lastName_ = lastName;
    totalBalance_ = 0;
    funds.push_back(Fund(0, "Money Market", 0));
    funds.push_back(Fund(1, "Prime Money Market"));
    funds.push_back(Fund(2, "Long-Term Bond"));
    funds.push_back(Fund(3, "Short-Term Bond"));
    funds.push_back(Fund(4, "500 Index Fund"));
    funds.push_back(Fund(5, "Capital Value Fund"));
    funds.push_back(Fund(6, "Growth Equity Fund"));
    funds.push_back(Fund(7, "Growth Index Fund"));
}

Account::Account(const Account& rhs) {
    id_ = rhs.id_;
    firstName_ = rhs.firstName_;
    lastName_ = rhs.lastName_;
    totalBalance_ = rhs.totalBalance_;
    funds = rhs.funds;
    transactions = rhs.transactions;
}
Account& Account::operator=(const Account& rhs) {
    if (this != &rhs) {
        id_ = rhs.id_;
        firstName_ = rhs.firstName_;
        lastName_ = rhs.lastName_;
        totalBalance_ = rhs.totalBalance_;
        funds = rhs.funds;
        transactions = rhs.transactions;
    }
    return *this;
}

Account::~Account() {

}

bool Account::Deposit(int amount, int fundId) {
    if (amount < 0) {
        cerr << "ERROR: Invalid deposit amount" << endl;
        return false;
    }
    if (fundId < 0 || fundId > 7) {
        cerr << "ERROR: FundID " << fundId << " is invalid " << endl;
        return false;
    }
    else {
        int b = funds[fundId].GetBalance(); //old balance
        funds[fundId].SetBalance(b + amount);
        totalBalance_ += amount;
        return true;
    }
}

bool Account::Withdraw(int amount, int fundId, Transaction& trans) {
    // int b = funds[fundId].getBalance(); //old balance
    // funds[fundId].setBalance(b - amount);
    // totalBalance_ -= amount;
    if (amount < 0) {
        cerr << "ERROR: Invalid withdraw amount" << endl;
        return false;
    }
    if (fundId < 0 || fundId > 7) {
        cerr << "ERROR: FundID " << fundId << " is invalid " << endl;
        return false;
    }
    else {
        // W 1234 0 500
        // amount = 500
        switch (fundId) {
        case 0:
            if (amount > funds[0].GetBalance() + funds[1].GetBalance()) {
                cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << lastName_ << " "
                    << firstName_ << " " << funds[0].GetName() << endl;
                return false;
            }
            else {
                if (amount > funds[0].GetBalance()) { //fund 0 is not enoungh money to withdraw
                    //ex: amount: 500$, fund 0: 200$, fund 1: 700$
                    amount -= funds[0].GetBalance(); //amount = 500 - 200 = 300
                    // account->withDraw(account->getFund(0).getBalance(), 0); //withdraw all money from fund 0 (200$)
                    trans.SetPrimaryFundId(1);
                    trans.SetAmount(amount);
                    funds[0].SetBalance(0); //withdraw all money from fund 0 (200$)
                    funds[1].SetBalance(funds[1].GetBalance() - amount); //withdraw 300$ from fund 1
                }
                else {
                    funds[0].SetBalance(funds[0].GetBalance() - amount); //withdraw 500$ from fund 0
                }
            }
            return true;
            break;
        case 1:
            if (amount > funds[0].GetBalance() + funds[1].GetBalance()) {
                cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << lastName_ << " "
                    << firstName_ << " " << funds[1].GetName() << endl;
                return false;
            }
            else {
                if (amount > funds[1].GetBalance()) {
                    amount -= funds[1].GetBalance();
                    trans.SetPrimaryFundId(0);
                    trans.SetAmount(amount);
                    funds[1].SetBalance(0);
                    funds[0].SetBalance(funds[0].GetBalance() - amount);
                }
                else {
                    funds[1].SetBalance(funds[1].GetBalance() - amount);
                }
            }
            return true;
            break;
        case 2:
            if (amount > funds[2].GetBalance() + funds[3].GetBalance()) {
                cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << lastName_ << " "
                    << firstName_ << " " << funds[2].GetName() << endl;
                return false;
            }
            else {
                if (amount > funds[2].GetBalance()) {
                    amount -= funds[2].GetBalance();
                    trans.SetPrimaryFundId(3);
                    trans.SetAmount(amount);
                    funds[2].SetBalance(0);
                    funds[3].SetBalance(funds[3].GetBalance() - amount);
                }
                else {
                    funds[2].SetBalance(funds[2].GetBalance() - amount);
                }
            }
            return true;
            break;
        case 3:
            if (amount > funds[2].GetBalance() + funds[3].GetBalance()) {
                cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << lastName_ << " "
                    << firstName_ << " " << funds[3].GetName() << endl;
                return false;
            }
            else {
                if (amount > funds[3].GetBalance()) {
                    amount -= funds[3].GetBalance();
                    trans.SetPrimaryFundId(2);
                    trans.SetAmount(amount);
                    funds[3].SetBalance(0);
                    funds[2].SetBalance(funds[2].GetBalance() - amount);
                }
                else {
                    funds[3].SetBalance(funds[3].GetBalance() - amount);
                }
            }
            return true;
            break;
        default:
            if (amount > funds[fundId].GetBalance()) {
                cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << lastName_ << " "
                    << firstName_ << " " << funds[fundId].GetName() << endl;
                return false;
            }
            else {
                funds[fundId].SetBalance(funds[fundId].GetBalance() - amount);
            }
            return true;
            break;
        }
    }
}

void Account::DisplayHistory() {
    cout << "Transaction History for " << this->lastName_ << " " << this->firstName_ << " by fund." << endl;
    for (int idx = 0; idx <= 7; idx++) {
        //find that there is a transaction that related to this fund id
        int found = false; //assume that there is no transaction related to fundId (id)
        for (int i = 0; i < transactions.size(); i++) {//traverse through the trasaction list of this account and find the transaction that this fundId = id
            if (transactions[i].GetPrimaryFundId() == idx || transactions[i].GetSecondaryFundId() == idx) {
                found = true; //if found -> found = true -> break nested loop(loop to find related trans)
                break;
            }
        }
        //-----------------------
        if (found) {
            cout << funds[idx].GetName() << ": $" << funds[idx].GetBalance() << endl;
            for (int i = 0; i < transactions.size(); i++) {
                if (transactions[i].GetPrimaryFundId() == idx && transactions[i].GetPrimaryAccountId() == this->id_) {
                    cout << "  ";
                    transactions[i].Display();
                }
                if (transactions[i].GetSecondaryFundId() == idx && transactions[i].GetSecondaryAccountId() == this->id_) {
                    cout << "  ";
                    transactions[i].Display();
                }
            }

        }
    }
}
void Account::DisplayHistory(int fundId) {
    if (fundId < 0 || fundId > 7) {
        cerr << "ERROR: FundID " << fundId << " is invalid " << endl;
        return;
    }
    else {
        cout << "Transaction History for " << this->lastName_ << " " << this->firstName_ << " " << this->funds[fundId].GetName()
            << ": $" << this->funds[fundId].GetBalance() << endl;
        for (int i = 0; i < transactions.size(); i++) {
            if (transactions[i].GetPrimaryFundId() == fundId && transactions[i].GetPrimaryAccountId() == this->id_) {
                cout << "  ";
                transactions[i].Display();
            }
            if (transactions[i].GetSecondaryFundId() == fundId && transactions[i].GetSecondaryAccountId() == this->id_) {
                cout << "  ";
                transactions[i].Display();
            }
        }
    }
}
ostream& operator<<(ostream& stream, const Account& rhs) {
    stream << rhs.lastName_ << " " << rhs.firstName_ << " Account ID: " << rhs.id_ << endl;
    for (int i = 0; i <= 7; i++) {
        stream << "    " << rhs.funds[i].GetName() << ": " << rhs.funds[i].GetBalance() << endl;
    }
    return stream;
}

int Account::GetTotalBalance() const {
    return this->totalBalance_;
}

int Account::GetId() const {
    return this->id_;
}

string Account::GetFirstName() const {
    return this->firstName_;
}
string Account::GetLastName() const {
    return this->lastName_;
}

void Account::DisplayFunds() {
    cout << this->lastName_ << " " << this->firstName_ << " Account ID: " << this->id_ << endl;
    for (int i = 0; i <= 7; i++) {
        cout << "    ";
        funds[i].Display();
    }
}

Fund Account::GetFund(int fundId) const {
    return this->funds[fundId];
}

void Account::AddTransaction(Transaction transaction) {
    if ((transaction.GetPrimaryAccountId() == transaction.GetSecondaryAccountId()) && transaction.GetPrimaryFundId() == transaction.GetSecondaryFundId()) {
        return;
    }
    transactions.push_back(transaction);
}

void Account::SetId(int idx) {
    this->id_ = idx;
}
