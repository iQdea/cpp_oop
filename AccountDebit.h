#pragma once
#include <string>
#include "Account.h"
#include "Date.h"

using namespace std;

class AccountDebit : public Account {
public:
	AccountDebit(shared_ptr<AccountLoader> accountLoader) : Account(accountLoader) {}
	virtual ~AccountDebit() {};
	string getTypeName() override {
		return "Дебетовый счет";
	}

	// 2020-10-02 => 2020-12-10
	// 2020-10-02 => 2020-11-01 => 2020-12-01 => 2020-12-10
};
