#pragma once
#include "AccountFactory.h"
#include "AccountDebit.h"

class AccountDebitFactory : public AccountFactory {
public:
    AccountDebitFactory(shared_ptr<AccountLoader> accountLoader) : AccountFactory(accountLoader) {}
    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountDebit> account(new AccountDebit(accountLoader));
        account->load();
        return account;
    }
};
