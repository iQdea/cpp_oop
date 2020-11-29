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
	string getClientName() {
		return clientName;
	}
	virtual void load() {
		clientName = accountLoader->getClient();
	}
	virtual void increaseBalance(double sum) {
		balance += sum;
	}
	void decreaseBalance(double sum) {
		balance -= sum;
	}
	void setRate(double rate) {
		this->rate = rate;
	}
	virtual double getMaxWithdraw() {
		return balance;
	}
	void calcIncome(string date) {
		int diffDays = Date::getDays(this->date, date);
		if (diffDays < 0) {
			throw invalid_argument("Неверный порядок дат в тестовом файле");
		}

		if (diffDays > 0 && balance > 0) {
			double delta = (rate / 100) / 365 * diffDays * balance;
			cout << "Начислены проценты " << delta << " с " << this->date << " по " << date << endl;
			income += delta;
			this->date = date;
		}
	}

	virtual void calcBalance(string date) {
		if (this->date == "") {
			this->date = date;
			return;
		}

		string currDate = Date::firstDayOfNextMonth(this->date);
		while (currDate <= date) {
			calcIncome(currDate);
			cout << "Зачислены на счет проценты " << income << " по " << this->date << endl;
			balance += income;
			income = 0;
			currDate = Date::firstDayOfNextMonth(currDate);
		}

		calcIncome(date);
	}
protected:
	string clientName = "";
	double rate = 0;
	double balance = 0;
	double income = 0;
	string date = "";
	shared_ptr<AccountLoader> accountLoader;
};
