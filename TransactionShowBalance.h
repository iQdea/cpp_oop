#pragma once
#include "Transaction.h"
#include "Bank.h"

class TransactionShowBalance : public Transaction {
public:
	TransactionShowBalance(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void commit(Bank* bank) override {
		string accountName = getAccount();
		shared_ptr<Account> account = bank->findAccount(accountName);
		string clientName = account->getClientName();
		string date = getDate();
		string name = account->getTypeName();
		double balance = account->getBalance();
		cout << name << endl << date << endl << accountName << endl << clientName << endl << balance << endl << endl;
	}
};
