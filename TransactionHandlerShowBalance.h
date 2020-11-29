#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"

using namespace std;

class TransactionHandlerShowBalance : public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionShowBalance>(transaction)) {
			transaction->commit(bank);
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};
