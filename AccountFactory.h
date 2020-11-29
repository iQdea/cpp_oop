#pragma once
#include <memory>
#include "Account.h"
#include "AccountLoader.h"

using namespace std;

class AccountFactory {
public:
    AccountFactory(shared_ptr<AccountLoader> accountLoader) {
        this->accountLoader = accountLoader;
    }
    virtual shared_ptr<Account> createAccount() const = 0;
    virtual void load() {
        // string client = accountLoader->getClient();
    }
protected:
    shared_ptr<AccountLoader> accountLoader;
};