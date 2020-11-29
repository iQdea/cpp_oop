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
	void load() override {
		Account::load();
		setDuration(accountLoader->getDuration());
	}
	bool isDurationEnded() {
		return Date::getDays(date, startDate) > (int) duration;
	}
	virtual double getMaxWithdraw() {
		return isDurationEnded() ? Account::getMaxWithdraw() : 0;
	}
	double calcRate() {
		for (auto &i : rates)
			if (startBalance <= i.first)
				return i.second;

		return defaultRate;
	}
	virtual void increaseBalance(double sum) {
		if (balance == 0) {
			startDate = date;
			startBalance = sum;
			rate = calcRate();
		}
		Account::increaseBalance(sum);
	}
	void setDefaultRate(double defaultRate) {
		this->defaultRate = defaultRate;
	}
	void setRates(vector<pair<double, double>> rates) {
		this->rates = rates;
	}
	void setDuration(unsigned int duration) {
		if (duration > 0) {
			this->duration = duration;
		}
	}
private:
	string startDate = "";
	double startBalance = 0;
	unsigned int duration = 0;
	double defaultRate = 0;
	vector<pair<double, double>> rates;
};
