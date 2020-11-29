#pragma once
#include "Bank.h"
#include "Transaction.h"
#include "TransactionHandler.h"
#include "TransactionWithdrawal.h"
#include "TransactionSend.h"

class TransactionHandlerNeedPositive: public TransactionHandler {
public:
	void run(Bank* bank, shared_ptr<Transaction> transaction) override {
		if (dynamic_pointer_cast<TransactionWithdrawal>(transaction)
			||
			dynamic_pointer_cast<TransactionSend>(transaction))
		{
			shared_ptr<Account> account = bank->findAccount(transaction->getAccount());
			shared_ptr<Client> client = bank->findClient(account->getClientName());
			if (client->isDoubtful() && transaction->getSum() > account->getWithdrawLimit()) {
				throw invalid_argument("����� �� �������� ��� ������������� ������� �� ������ ��������� ����� �� �����");
			}

			if (transaction->getSum() > account->getMaxWithdraw()) {
				throw invalid_argument("����� �� �������� �� ������ ��������� ������������ ����� �� �����");
			}
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};