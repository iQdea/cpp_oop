#pragma once
#include "Transaction.h"
#include <iostream>

using namespace std;

class TransactionRefill : public Transaction {
public:
	TransactionRefill(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void commit(Bank* bank) override {
		bank->findAccount(getAccount())->increaseBalance(getSum());
		cout << "���������� �� " << this->getDate() << " ���������" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->decreaseBalance(getSum());
		cout << "������ ���������� �� " << this->getDate() << " ���������" << endl << endl;
	}
};
