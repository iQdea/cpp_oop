#pragma once
#include "AccountFactory.h"
#include "AccountCredit.h"

using namespace std;

class AccountCreditFactory : public AccountFactory {
public:
    AccountCreditFactory(shared_ptr<AccountLoader> accountLoader) : AccountFactory(accountLoader) {}

    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountCredit> account(new AccountCredit(accountLoader));
        account->load();
        return account;
    }
};
