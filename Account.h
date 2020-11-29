#pragma once
#include "AccountLoader.h"
#include "Date.h"

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
	virtual double getRate() {
		return rate;
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

		double rate = getRate();
		if (diffDays > 0 && balance > 0 && rate != 0) {
			double delta = (rate / 100) / 365 * diffDays * balance;
			if (rate > 0) {
				cout << "Начислены проценты ";
			}
			else {
				cout << "Рассчитана комиссия ";
			}
			cout << delta << " с " << this->date << " по " << date << endl;
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
			if (income > 0) {
				cout << "Зачислены на счет проценты ";
			}
			else {
				cout << "Списана со счета комиссия ";
			}
			cout << income << " по " << this->date << endl;
			balance += income;
			income = 0;
			currDate = Date::firstDayOfNextMonth(currDate);
		}

		calcIncome(date);
	}
	void setWithdrawLimit(double withdrawLimit) {
		if (withdrawLimit > 0) {
			this->withdrawLimit = withdrawLimit;
		}
	}
	double getWithdrawLimit() {
		return withdrawLimit;
	}
protected:
	string clientName = "";
	double rate = 0;
	double balance = 0;
	double income = 0;
	double withdrawLimit = 0;
	string date = "";
	shared_ptr<AccountLoader> accountLoader;
};
