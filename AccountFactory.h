#pragma once
#include <memory>
#include "Account.h"
#include "AccountLoader.h"
#include "BankLoader.h"

using namespace std;

class AccountFactory {
public:
    AccountFactory(shared_ptr<BankLoader> bankLoader, shared_ptr<AccountLoader> accountLoader) {
        withdrawLimit = bankLoader->getWithdrawalLimit();
        this->accountLoader = accountLoader;
    }
    void preLoadAccount(shared_ptr<Account> account) const {
        account->setWithdrawLimit(withdrawLimit);
    }
    virtual shared_ptr<Account> createAccount() const = 0;

protected:
    shared_ptr<AccountLoader> accountLoader;
private:
    double withdrawLimit;
};