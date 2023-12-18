/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/

#include "transaction.h"
Transaction::Transaction() {
	type_ = ' ';
	primaryAccountId_ = -1;
	primaryFundId_ = -1;
	secondaryAccountId_ = -1;
	secondaryFundId_ = -1;
	amount_ = 0;
	firstName_ = "";
	lastName_ = "";
	error_ = false;
}

Transaction::Transaction(char type, int primaryAccountId, int primaryFundId, int amount)
{
	this->type_ = type;
	this->primaryAccountId_ = primaryAccountId;
	this->primaryFundId_ = primaryFundId;
	this->secondaryAccountId_ = -1;
	this->secondaryFundId_ = -1;
	this->amount_ = amount;
	this->firstName_ = "";
	this->lastName_ = "";
	error_ = false;
}

Transaction::Transaction(char type, int primaryAccountId, int primaryFundId, int secondaryAccountId, int secondaryFundId, int amount)
{
	this->type_ = type;
	this->primaryAccountId_ = primaryAccountId;
	this->primaryFundId_ = primaryFundId;
	this->secondaryAccountId_ = secondaryAccountId;
	this->secondaryFundId_ = secondaryFundId;
	this->amount_ = amount;
	this->firstName_ = "";
	this->lastName_ = "";
	error_ = false;
}

Transaction::Transaction(char type, int primaryAccountId)
{
	this->type_ = type;
	this->primaryAccountId_ = primaryAccountId;
	this->primaryFundId_ = -1;
	this->secondaryAccountId_ = -1;
	this->secondaryFundId_ = -1;
	this->amount_ = -1;
	this->firstName_ = "";
	this->lastName_ = "";
	error_ = false;
}

Transaction::Transaction(char type, int primaryAccountId, int primaryFundId)
{
	this->type_ = type;
	this->primaryAccountId_ = primaryAccountId;
	this->primaryFundId_ = primaryFundId;
	this->secondaryAccountId_ = -1;
	this->secondaryFundId_ = -1;
	this->amount_ = -1;
	this->firstName_ = "";
	this->lastName_ = "";
	error_ = false;
}

Transaction::Transaction(char type, int primaryAccountId, string firstName, string lastName)
{
	this->type_ = type;
	this->primaryAccountId_ = primaryAccountId;
	this->primaryFundId_ = -1;
	this->secondaryAccountId_ = -1;
	this->secondaryFundId_ = -1;
	this->amount_ = -1;
	this->firstName_ = firstName;
	this->lastName_ = lastName;
	error_ = false;
}

Transaction::Transaction(const Transaction& src) {
	this->type_ = src.type_;
	this->primaryAccountId_ = src.primaryAccountId_;
	this->primaryFundId_ = src.primaryFundId_;
	this->secondaryAccountId_ = src.secondaryAccountId_;
	this->secondaryFundId_ = src.secondaryFundId_;
	this->amount_ = src.amount_;
	this->firstName_ = src.firstName_;
	this->lastName_ = src.lastName_;
	this->error_ = src.error_;

}

Transaction& Transaction::operator=(const Transaction& src) {
	if (this != &src) {
		this->type_ = src.type_;
		this->primaryAccountId_ = src.primaryAccountId_;
		this->primaryFundId_ = src.primaryFundId_;
		this->secondaryAccountId_ = src.secondaryAccountId_;
		this->secondaryFundId_ = src.secondaryFundId_;
		this->amount_ = src.amount_;
		this->firstName_ = src.firstName_;
		this->lastName_ = src.lastName_;
		this->error_ = src.error_;
	}
	return *this;
}


int Transaction::GetType() const {
	return type_;
}
int Transaction::GetPrimaryAccountId() const {
	return primaryAccountId_;
}
int Transaction::GetPrimaryFundId() const {
	return primaryFundId_;
}
int Transaction::GetSecondaryAccountId() const {
	return secondaryAccountId_;
}
int Transaction::GetSecondaryFundId() const {
	return secondaryFundId_;
}
int Transaction::GetAmount() const {
	return amount_;
}
// void Transaction::setSecondaryFundId(int fundId){
// 	this->primaryFundId_ = fundId;
// }
void Transaction::SetPrimaryFundId(int fundId) {
	this->primaryFundId_ = fundId;
}
string Transaction::GetFirstName() const {
	return firstName_;
}
string Transaction::GetLastName() const {
	return lastName_;
}
bool Transaction::GetError() const {
	return error_;
}
void Transaction::SetAmount(int amount) {
	this->amount_ = amount;
}

void Transaction::Display() {
	if (this->type_ == 'D' || this->type_ == 'W') {
		cout << this->type_ << " " << this->primaryAccountId_ << " " << this->primaryFundId_ << " " << this->amount_;
	}

	if (this->type_ == 'T') {
		cout << this->type_ << " " << this->primaryAccountId_ << " " << this->primaryFundId_ << " " << this->secondaryAccountId_ << " " << this->secondaryFundId_ << " " << this->amount_;
	}

	if (this->type_ == 'A') {
		cout << this->type_ << " " << this->primaryAccountId_;
	}

	if (this->type_ == 'F') {
		cout << this->type_ << " " << this->primaryAccountId_ << " " << this->primaryFundId_;
	}

	if (this->type_ == 'O') {
		cout << this->type_ << " " << this->primaryAccountId_ << " " << this->lastName_ << " " << this->firstName_;
	}

	if (this->error_) {
		cout << " (Failed)" << endl;
	}
	else {
		cout << endl;
	}

}

void Transaction::SetError(bool error) {
	this->error_ = error;
}