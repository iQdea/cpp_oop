#pragma once
#include "Bank.h"
#include "Transaction.h"

class TransactionHandler {
public:
	virtual ~TransactionHandler() {}

	shared_ptr<TransactionHandler> setNext(shared_ptr<TransactionHandler> transactionHandler) {
		nextTransactionHandler = transactionHandler;
		return transactionHandler;
	}
	virtual void run(Bank* bank, shared_ptr<Transaction> transaction) {
		if (nextTransactionHandler) {
			nextTransactionHandler->run(bank, transaction);
		}
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};