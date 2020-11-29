#pragma once
#include "AccountLoader.h"

class Account {
public:
	Account(shared_ptr<AccountLoader> accountLoader) {
		this->accountLoader = accountLoader;
	}
	virtual ~Account() {};
	virtual string getTypeName() = 0 {}
	double getBalance() {
		return balance;
	}
	string getClientName() {
		return clientName;
	}
	virtual void load() {
		clientName = accountLoader->getClient();
	}
	void increaseBalance(double sum) {
		balance += sum;
	}
	void decreaseBalance(double sum) {
		balance -= sum;
	}
protected:
	string clientName = "";
	double balance = 0;
	shared_ptr<AccountLoader> accountLoader;
};
