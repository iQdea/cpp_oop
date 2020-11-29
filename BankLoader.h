#pragma once

#include <string>
#include <vector>
#include "Loader.h"

using namespace std;

class BankLoader : public Loader {
public:
	BankLoader(shared_ptr<Config> config, string configSection = "") : Loader(config, configSection) {}
	vector<string> getClients() { return getList<string>("Clients"); }
	vector<string> getAccounts() { return getList<string>("Accounts"); }
	vector<string> getTransactions() { return getList<string>("Transactions"); }
	double getDebitRate() { return getNumber<double>("DebitRate"); }
	int getDepositDuration() { return getNumber<int>("DepositDuration"); }
	double getDepositRateDefault() { return getNumber<double>("DepositRateDefault"); }
	vector<pair<double, double>> getDepositRates() { return getPairList<double>("DepositRates"); }
	double getCreditLimitDefault() { return getNumber<double>("CreditLimitDefault"); }
	double getCreditFeeDefault() { return getNumber<double>("CreditFeeDefault"); }
	double getWithdrawalLimit() { return getNumber<double>("WithdrawalLimit"); }
};
/*
Clients=Client2,Client3
Accounts=Account4,Account5
DebitRate=1
DepositDuration=365
DepositRateDefault=4
DepositRates=50000:3|100000:3.5
CreditLimitDefault=10000
CreditFeeDefault=15
WithdrawalLimit=5000
*/