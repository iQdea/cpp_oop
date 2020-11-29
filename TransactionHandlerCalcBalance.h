#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"

using namespace std;

class TransactionHandlerCalcBalance : public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		transaction->calcBalance(bank);
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};
