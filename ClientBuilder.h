#pragma once
#include <string>
#include "Client.h"
#include "ClientName.h"
#include "ClientAddress.h"
#include "ClientPassport.h"

using namespace std;

class ClientBuilder {
public:
    ClientBuilder() {
        reset();
    }
    void reset() {
        client = shared_ptr<Client>(new Client());
    }
    void produceClientName(string name, string surname) const {
        client->addPart(shared_ptr<ClientName>(new ClientName(name, surname)));
    }
    void produceClientAddress(string address) const {
        client->addPart(shared_ptr<ClientAddress>(new ClientAddress(address)));
    }
    void produceClientPassport(string passport) const {
        client->addPart(shared_ptr<ClientPassport>(new ClientPassport(passport)));
    }
    shared_ptr<Client> getClient() {
        shared_ptr<Client> result = client;
        this->reset();
        return result;
    }
private:
    shared_ptr<Client> client;
};