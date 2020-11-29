#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "AccountFactory.h"
#include "ClientDirector.h"
#include "BankLoader.h"
#include "ClientLoader.h"
#include "Config.h"
#include "AccountDebitFactory.h"
#include "AccountDepositFactory.h"
#include "AccountCreditFactory.h"
#include "TransactionLoader.h"

class Transaction;
class TransactionHandler;

using namespace std;

class Bank {
public:
	Bank(shared_ptr<Config> config, string configSection);
	void addAccount(string& accountSection, const shared_ptr<AccountFactory> factory) {
		accountList[accountSection] = factory->createAccount();
	}
	void addClient(string& clientSection, ClientDirector& clientDirector) {
		clientDirector.buildClient();
		clientList[clientSection] = clientDirector.getClient();
	}
	void load() {
		loadClients();
		loadAccounts();
		loadTransactions();
	}
	shared_ptr<AccountFactory> getAccountFactory(string factoryType) {
		if (factoryType == "Debit") {
			return accountDebitFactory;
		}
		if (factoryType == "Deposit") {
			return accountDepositFactory;
		}
		if (factoryType == "Credit") {
			return accountCreditFactory;
		}
		throw invalid_argument("Неизвестный тип счета: " + factoryType);
	}
	void loadAccounts() {
		vector<string> accountSectionList = bankLoader->getAccounts();
		for (string& accountSection : accountSectionList) {
			accountLoader->setConfigSection(accountSection);
			addAccount(accountSection, getAccountFactory(accountLoader->getType()));
		}
	}
	void loadClients() {
		shared_ptr<ClientLoader> clientLoader(new ClientLoader(config));
		ClientDirector clientDirector(clientLoader);

		vector<string> clientSectionList = bankLoader->getClients();
		for (string& clientSection : clientSectionList) {
			clientLoader->setConfigSection(clientSection);
			addClient(clientSection, clientDirector);
		}
	}

	shared_ptr<Transaction> getTransaction(shared_ptr<TransactionLoader> transactionLoader, string transactionType);
	shared_ptr<Transaction> loadTransaction(string transactionSection);
	void loadTransactions();

	shared_ptr<Account> findAccount(string accountSection) {
		if (accountList.count(accountSection) > 0) {
			return accountList[accountSection];
		}
		throw invalid_argument("Счет не найден: " + accountSection);
	}

	shared_ptr<Client> findClient(string clientSection) {
		if (clientList.count(clientSection) > 0) {
			return clientList[clientSection];
		}
		throw invalid_argument("Клиент не найден: " + clientSection);
	}
private:
	string configSection = "";
	map<string, shared_ptr<Account>> accountList;
	map<string, shared_ptr<Client>> clientList;
	shared_ptr<Config> config = 0;
	shared_ptr<BankLoader> bankLoader;
	shared_ptr<AccountLoader> accountLoader;
	shared_ptr<AccountDebitFactory> accountDebitFactory;
	shared_ptr<AccountDepositFactory> accountDepositFactory;
	shared_ptr<AccountCreditFactory> accountCreditFactory;
	shared_ptr<TransactionHandler> transactionHandler;
};