#pragma once
#include "AccountFactory.h"
#include "AccountCredit.h"

using namespace std;

class AccountCreditFactory : public AccountFactory {
public:
    AccountCreditFactory(
        shared_ptr<BankLoader> bankLoader, shared_ptr<AccountLoader> accountLoader
    ) : AccountFactory(bankLoader, accountLoader) {
        limitDefault = bankLoader->getCreditLimitDefault();
        feeDefault = bankLoader->getCreditFeeDefault();
    }

    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountCredit> account(new AccountCredit(accountLoader));
        preLoadAccount(account);
        account->setLimit(limitDefault);
        account->setFee(feeDefault);
        account->load();
        return account;
    }
private:
    double limitDefault;
    double feeDefault;
};
