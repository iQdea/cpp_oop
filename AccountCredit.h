#pragma once
#include "Account.h"

class AccountCredit : public Account {
public:
	AccountCredit(shared_ptr<AccountLoader> accountLoader) : Account(accountLoader) {}
	virtual ~AccountCredit() {};
	virtual void load() override {
		Account::load();
		creditLimit = accountLoader->getCreditLimit();
		creditFee = accountLoader->getCreditFee();
	}
	string getTypeName() override {
		return "Кредитный счет";
	}
private:
	double creditLimit = 0;
	double creditFee = 0;
};
