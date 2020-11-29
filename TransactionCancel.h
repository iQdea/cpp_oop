#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"
#include "TransactionHandlerWithdrawalCancel.h"
#include "TransactionHandlerSendCancel.h"
#include "TransactionHandlerRefillCancel.h"
class TransactionCancel : public Transaction {
public:
	TransactionCancel(shared_ptr<TransactionLoader> transactionLoader) : Transaction(transactionLoader) {}
	void load() override {
		transactionSection = transactionLoader->getTransaction();
	}
	void commit(Bank* bank) override {
		 shared_ptr<Transaction> transaction = bank->loadTransaction(transactionSection);

		 shared_ptr<TransactionHandler> transactionHandler = shared_ptr<TransactionHandler>(new TransactionHandler());
		 transactionHandler
			 ->setNext(shared_ptr<TransactionHandlerSendCancel>(new TransactionHandlerSendCancel()))
			 ->setNext(shared_ptr<TransactionHandlerWithdrawalCancel>(new TransactionHandlerWithdrawalCancel()))
			 ->setNext(shared_ptr<TransactionHandlerRefillCancel>(new TransactionHandlerRefillCancel()))
			 ;
		 transactionHandler->run(bank, transaction);

	}
private:
	string transactionSection = "";
};
