#pragma once
#include "TransactionLoader.h"
#include "Bank.h"

class Transaction {
public:
	Transaction(shared_ptr<TransactionLoader> transactionLoader) {
		this->transactionLoader = transactionLoader;
	}
	virtual ~Transaction() = 0 {};
	string getAccount() {
		return account;
	}
	virtual void calcBalance(Bank* bank) {
		string accountName = getAccount();
		string date = getDate();
		shared_ptr<Account> account = bank->findAccount(accountName);
		account->calcBalance(date);
	}
	virtual void commit(Bank* bank) {}
	virtual void rollback(Bank* bank) {}
	double getSum() {
		return sum;
	}
	string getDate() {
		return date;
	}
	string getSendto() {
		return to;
	}
	virtual void load() {
		account = transactionLoader->getAccount();
		date = transactionLoader->getDate();
		sum = transactionLoader->getSum();
		to = transactionLoader->getSendTo();
	}
protected:
	string account;
	string date;
	double sum;
	string to;
	shared_ptr<TransactionLoader> transactionLoader;
};
