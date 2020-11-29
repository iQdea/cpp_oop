#pragma once
#include "AccountFactory.h"
#include "AccountDeposit.h"

class AccountDepositFactory : public AccountFactory {
public:
    AccountDepositFactory(
        shared_ptr<BankLoader> bankLoader, shared_ptr<AccountLoader> accountLoader
    ) : AccountFactory(bankLoader, accountLoader) {
        defaultDuration = bankLoader->getDepositDuration();
        defaultRate = bankLoader->getDepositRateDefault();
        rates = bankLoader->getDepositRates();
    }

    shared_ptr<Account> createAccount() const override {
        shared_ptr<AccountDeposit> account(new AccountDeposit(accountLoader));
        preLoadAccount(account);
        account->setDuration(defaultDuration);
        account->setDefaultRate(defaultRate);
        account->setRates(rates);
        account->load();
        return account;
    }
private:
    unsigned int defaultDuration;
    double defaultRate;
    vector<pair<double, double>> rates;
};
