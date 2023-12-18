/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#ifndef FUND_H_
#define FUND_H_
#include <iostream>
#include <string>
using namespace std;
class Fund {

public:
    Fund();
    Fund(int id, string name, int balance); // create fund with id, name and balance(= 0 or != 0)
    Fund(int id, string name); //balance = 0
    Fund(const Fund& F); //copy constructor
    Fund& operator=(const Fund& rhs); //assignment operator
    int GetBalance() const;
    void SetBalance(int b);
    string GetName() const;
    int GetId() const;
    void Display();
private:
    string name_; //id = 0 -> name = "money market"
    int id_; //0->7
    int balance_;
};
#endif