#include "Bank.h"
#include <string>
#include "Transaction.h"
#include "TransactionCancel.h"
#include "TransactionRefill.h"
#include "TransactionSend.h"
#include "TransactionShowBalance.h"
#include "TransactionWithdrawal.h"
#include "TransactionHandler.h"
#include "TransactionHandlerCheckSum.h"
#include "TransactionHandlerSend.h"
#include "TransactionHandlerCancel.h"
#include "TransactionHandlerRefill.h"
#include "TransactionHandlerWithdrawal.h"
#include "TransactionHandlerShowBalance.h"
#include "TransactionHandlerCalcBalance.h"
#include "TransactionHandlerNeedPositive.h"

using namespace std;

Bank::Bank(shared_ptr<Config> config, string configSection) {
	this->config = config;

	bankLoader = shared_ptr<BankLoader>(new BankLoader(config, configSection));

	accountLoader = shared_ptr<AccountLoader>(new AccountLoader(config));
	accountDebitFactory = shared_ptr<AccountDebitFactory>(new AccountDebitFactory(bankLoader, accountLoader));
	accountDepositFactory = shared_ptr<AccountDepositFactory>(new AccountDepositFactory(bankLoader, accountLoader));
	accountCreditFactory = shared_ptr<AccountCreditFactory>(new AccountCreditFactory(accountLoader));

	transactionHandler = shared_ptr<TransactionHandler>(new TransactionHandler());
	transactionHandler
		// пересчет баланса
		->setNext(shared_ptr<TransactionHandlerCalcBalance>(new TransactionHandlerCalcBalance()))

		// промежуточные проверки
		->setNext(shared_ptr<TransactionHandlerCheckSum>(new TransactionHandlerCheckSum()))
		->setNext(shared_ptr<TransactionHandlerNeedPositive>(new TransactionHandlerNeedPositive()))

		// окончательные действия
		->setNext(shared_ptr<TransactionHandlerSend>(new TransactionHandlerSend()))
		->setNext(shared_ptr<TransactionHandlerCancel>(new TransactionHandlerCancel()))
		->setNext(shared_ptr<TransactionHandlerRefill>(new TransactionHandlerRefill()))
		->setNext(shared_ptr<TransactionHandlerWithdrawal>(new TransactionHandlerWithdrawal()))
		->setNext(shared_ptr<TransactionHandlerShowBalance>(new TransactionHandlerShowBalance()))
		;
}

shared_ptr<Transaction> Bank::loadTransaction(string transactionSection) {
	shared_ptr<TransactionLoader> transactionLoader(new TransactionLoader(config, transactionSection));
	shared_ptr<Transaction> transaction = getTransaction(transactionLoader, transactionLoader->getType());
	
	transaction->load();

	return transaction;
}

void Bank::loadTransactions() {

	vector<string> transactionSectionList = bankLoader->getTransactions();
	for (string& transactionSection : transactionSectionList) {
		shared_ptr<Transaction> transaction = loadTransaction(transactionSection);

		if (transactionHandler) {
			try {
				transactionHandler->run(this, transaction);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}
	}
}

shared_ptr<Transaction> Bank::getTransaction(shared_ptr<TransactionLoader> transactionLoader, string transactionType) {
	if (transactionType == "Refill") {
		return shared_ptr<TransactionRefill>(new TransactionRefill(transactionLoader));
	}
	if (transactionType == "Withdrawal") {
		return shared_ptr<TransactionWithdrawal>(new TransactionWithdrawal(transactionLoader));
	}
	if (transactionType == "Send") {
		return shared_ptr<TransactionSend>(new TransactionSend(transactionLoader));
	}
	if (transactionType == "ShowBalance") {
		return shared_ptr<TransactionShowBalance>(new TransactionShowBalance(transactionLoader));
	}
	if (transactionType == "Cancel") {
		return shared_ptr<TransactionCancel>(new TransactionCancel(transactionLoader));
	}
	throw invalid_argument("Неизвестный тип транзакции: " + transactionType);
}
