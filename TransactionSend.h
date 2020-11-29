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
		string date = getDate();

		shared_ptr<Account> account = bank->findAccount(getAccount());
		account->calcBalance(date);

		shared_ptr<Account> sendTo = bank->findAccount(getSendto());
		sendTo->calcBalance(date);

		account->decreaseBalance(getSum());
		sendTo->increaseBalance(getSum());

		cout << "Перевод от " << date << " выполнен" << endl << endl;
	}
	void rollback(Bank* bank) override {
		bank->findAccount(getAccount())->increaseBalance(getSum());
		bank->findAccount(getSendto())->decreaseBalance(getSum());
		cout << "Отмена перевода от " << this->getDate() << " выполнена" << endl << endl;
	}
private:
	string accountSendTo;
};
