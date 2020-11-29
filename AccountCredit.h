#pragma once
#include "Account.h"

class AccountCredit : public Account {
public:
	AccountCredit(shared_ptr<AccountLoader> accountLoader) : Account(accountLoader) {}
	virtual ~AccountCredit() {};
	virtual void load() override {
		Account::load();
		setLimit(accountLoader->getCreditLimit());
		setFee(accountLoader->getCreditFee());
	}
	string getTypeName() override {
		return "Кредитный счет";
	}
	virtual double getMaxWithdraw() {
		return balance + limit;
	}
	void setLimit(double limit) {
		if (limit > 0) {
			this->limit = limit;
		}
	}
	void setFee(double fee) {
		if (fee > 0) {
			this->fee = fee;
		}
	}
	double getRate() override {
		return fee * -1.0;
	}
private:
	double limit = 0;
	double fee = 0;
};
