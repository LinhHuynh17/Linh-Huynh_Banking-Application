/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#include "fund.h"

Fund::Fund()
{
	id_ = -1;
	name_ = "";
	balance_ = 0;
}

Fund::Fund(int id, string name, int balance)
{
	this->id_ = id;
	this->name_ = name;
	this->balance_ = balance;
}

Fund::Fund(int id, string name)
{
	this->id_ = id;
	this->name_ = name;
	this->balance_ = 0;
}

Fund::Fund(const Fund& F) {
	this->id_ = F.id_;
	this->name_ = F.name_;
	this->balance_ = F.balance_;
}

Fund& Fund::operator=(const Fund& rhs) {
	if (this != &rhs) {
		this->id_ = rhs.id_;
		this->name_ = rhs.name_;
		this->balance_ = rhs.balance_;
	}
	return *this;
}

int Fund::GetBalance() const {
	return this->balance_;
}

void Fund::SetBalance(int b) {
	this->balance_ = b;
}

string Fund::GetName() const {
	return this->name_;
}

int Fund::GetId() const {
	return this->id_;
}

void Fund::Display() {
	cout << this->name_ << ": $" << this->balance_ << endl;
}
