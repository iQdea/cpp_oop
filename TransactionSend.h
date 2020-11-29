#pragma once
#include "Transaction.h"

class TransactionSend : public Transaction {
public:
	TransactionSend(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void load() override {
		Transaction::load();
		accountSendTo = transactionLoader->getSendTo();
	}
	virtual void calcBalance(Bank* bank) {
		Transaction::calcBalance(bank);

		string accountName = getSendto();
		string date = getDate();
		shared_ptr<Account> account = bank->findAccount(accountName);
		account->calcBalance(date);
	}
	void commit(Bank* bank) override {
		string date = getDate();
		shared_ptr<Account> account = bank->findAccount(getAccount());
		shared_ptr<Account> sendTo = bank->findAccount(getSendto());

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
