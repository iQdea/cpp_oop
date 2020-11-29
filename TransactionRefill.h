#pragma once
#include "Transaction.h"
#include <iostream>

using namespace std;

class TransactionRefill : public Transaction {
public:
	TransactionRefill(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void commit(Bank* bank) override {
		string accountName = getAccount();
		string date = getDate();
		shared_ptr<Account> account = bank->findAccount(accountName);
		account->calcBalance(date);
		account->increaseBalance(getSum());
		cout << "���������� �� " << this->getDate() << " ���������" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->decreaseBalance(getSum());
		cout << "������ ���������� �� " << this->getDate() << " ���������" << endl << endl;
	}
};
