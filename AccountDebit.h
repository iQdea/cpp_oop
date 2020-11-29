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
	void calcIncome(string date) {
		int diffDays = Date::getDays(this->date, date);
		if (diffDays < 0) {
			throw invalid_argument("Неверный порядок дат в тестовом файле");
		}

		if (diffDays > 0 && balance > 0) {
			double delta = (defaultRate / 100) / 365 * diffDays * balance;
			cout << "Начислены проценты " << delta << " с " << this->date << " по " << date << endl;
			income += delta;
			this->date = date;
		}
	}

	void calcBalance(string date) override {
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
};
