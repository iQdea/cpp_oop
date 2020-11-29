#pragma once
#include <string>
#include "Loader.h"

using namespace std;

class TransactionLoader : public Loader {
public:
	TransactionLoader(shared_ptr<Config> config, string configSection = "") : Loader(config, configSection) {}
	string getAccount() { return getString("Account"); }
	string getDate() { return getString("Date"); }
	string getType() { return getString("Type"); }
	double getSum() { return getNumber<double>("Sum"); }
	string getSendTo() { return getString("SendTo"); }
	string getTransaction() { return getString("Transaction"); }
};