#pragma once
#include "AccountFactory.h"
#include "AccountDebit.h"
#include "BankLoader.h"

class AccountDebitFactory : public AccountFactory {
public:
    AccountDebitFactory(
        shared_ptr<BankLoader> bankLoader, shared_ptr<AccountLoader> accountLoader
    ) : AccountFactory(bankLoader, accountLoader) {
        defaultRate = bankLoader->getDebitRate();
    }
    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountDebit> account(new AccountDebit(accountLoader));
        preLoadAccount(account);
        account->setRate(defaultRate);
        account->load();        
        
        return account;
    }
private:
    double defaultRate;
};
