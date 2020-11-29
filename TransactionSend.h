#pragma once
#include "Transaction.h"

class TransactionSend : public Transaction {
public:
	TransactionSend(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void load() override {
		Transaction::load();
		accountSendTo = transactionLoader->getSendTo();
	}
	void commit(Bank* bank) override {
		bank->findAccount(getAccount())->decreaseBalance(getSum());
		bank->findAccount(getSendto())->increaseBalance(getSum());
		cout << "Перевод от " << this->getDate() << " выполнен" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->increaseBalance(getSum());
		bank->findAccount(getSendto())->decreaseBalance(getSum());
		cout << "Отмена перевода от " << this->getDate() << " выполнена" << endl << endl;
	}
private:
	string accountSendTo;
};
