#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionSend.h"
#include "TransactionHandler.h"

class TransactionHandlerSend : public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionSend>(transaction)) {
			transaction->commit(bank);
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
	//shared_ptr<ClientDirector> client;
	//(client->IsDoubtful() != 0)
};