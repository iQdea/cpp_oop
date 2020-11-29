#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"

class TransactionHandlerRefill : public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionRefill>(transaction)) {
			transaction->commit(bank);
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};