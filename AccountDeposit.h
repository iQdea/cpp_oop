#pragma once
#include "Account.h"

class AccountDeposit : public Account {
public:
	AccountDeposit(shared_ptr<AccountLoader> accountLoader) : Account(accountLoader) {}
	virtual ~AccountDeposit() {};
	double getStartBalance() const {
		return startBalance;
	}
	string getTypeName() override {
		return "Депозит";
	}
private:
	string startDate = "";
	double startBalance = 0;
};
