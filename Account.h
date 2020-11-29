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
	virtual void calcBalance(string date) {}
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
	void setDefaultRate(double defaultRate) {
		this->defaultRate = defaultRate;
	}
	virtual double getMaxWithdraw() {
		return balance;
	}
protected:
	string clientName = "";
	double defaultRate = 0;
	double balance = 0;
	double income = 0;
	string date = "";
	shared_ptr<AccountLoader> accountLoader;
};
