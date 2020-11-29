#pragma once
#include <string>
#include "Account.h"

using namespace std;

class AccountDebit : public Account {
public:
	AccountDebit(shared_ptr<AccountLoader> accountLoader) : Account(accountLoader) {}
	virtual ~AccountDebit() {};
	string getTypeName() override {
		return "Дебетовый счет";
	}
};
