#pragma once
#include "Transaction.h"

class TransactionWithdrawal : public Transaction {
public:
	TransactionWithdrawal(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void commit(Bank* bank) override 
	{
		bank->findAccount(getAccount())->decreaseBalance(getSum());
		cout << "Снятие денег от " << this->getDate() << " выполнено" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->increaseBalance(getSum());
		cout << "Отмена снятия денег от " << this->getDate() << " выполнена" << endl << endl;
	}
};
