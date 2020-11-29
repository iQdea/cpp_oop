#pragma once

#include <string>
#include <vector>
#include "Loader.h"

using namespace std;

class AccountLoader : public Loader {
public:
	AccountLoader(shared_ptr<Config> config, string configSection = "") : Loader(config, configSection) {}
	string getClient() { return getString("Client"); }
	string getType() { return getString("Type"); }
	string getStartDate() { return getString("StartDate"); }
	double getStartBalance() { return getNumber<double>("StartBalance"); }
	double getCreditLimit() { return getNumber<double>("CreditLimit"); }
	double getCreditFee() { return getNumber<double>("CreditFee"); }
};
//Client = Client2
//Type = Deposit
//StartDate = 2020 - 11 - 01
//StartBalance = 70000
//CreditLimit
