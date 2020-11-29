#pragma once
#include "Transaction.h"

class TransactionWithdrawal : public Transaction {
public:
	TransactionWithdrawal(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void commit(Bank* bank) override 
	{
		bank->findAccount(getAccount())->decreaseBalance(getSum());
		cout << "������ ����� �� " << this->getDate() << " ���������" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->increaseBalance(getSum());
		cout << "������ ������ ����� �� " << this->getDate() << " ���������" << endl << endl;
	}
};
