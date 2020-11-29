#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"

class TransactionHandlerWithdrawal : public TransactionHandler{
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionWithdrawal>(transaction)) {
			transaction->commit(bank);
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
	//shared_ptr<ClientDirector> client;
	//&& (client->IsDoubtful() != 0)
	//else {cout << "Клиент сомнительный, операция не возможна!" << endl << endl;}
};