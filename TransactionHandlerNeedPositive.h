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
				throw invalid_argument("Сумма по операции для сомнительного клиента не должна превышать лимит на вывод");
			}

			double maxWithdraw = account->getMaxWithdraw();
			if (transaction->getSum() > maxWithdraw) {
				if (maxWithdraw == 0 && account->getBalance() > 0 && dynamic_pointer_cast<AccountDeposit>(account)) {
					throw invalid_argument("Операция снятия и перевода по депозиту запрещены до истечения его срока");
				}
				else {
					throw invalid_argument("Сумма по операции не должна превышать максимальную сумму на вывод");
				}
			}
		}
		TransactionHandler::run(bank, transaction);
	}
private:
	shared_ptr<TransactionHandler> nextTransactionHandler;
};