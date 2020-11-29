#pragma once
#include "AccountFactory.h"
#include "AccountDeposit.h"

class AccountDepositFactory : public AccountFactory {
public:
    AccountDepositFactory(shared_ptr<AccountLoader> accountLoader) : AccountFactory(accountLoader) {}

    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountDeposit> account(new AccountDeposit(accountLoader));
        account->load();
        return account;
    }
};
