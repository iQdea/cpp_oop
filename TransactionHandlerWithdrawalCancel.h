#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionWithdrawal.h"
#include "TransactionHandler.h"

class TransactionHandlerWithdrawalCancel : public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionWithdrawal>(transaction)) {
			transaction->rollback(bank);
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};