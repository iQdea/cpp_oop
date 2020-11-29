#pragma once
#include <stdexcept>
#include "ClientBuilder.h"
#include "ClientLoader.h"

using namespace std;

class ClientDirector
{
public:
	ClientDirector(shared_ptr<ClientLoader> clientLoader) {
		this->clientLoader = clientLoader;
		this->clientBuilder = shared_ptr<ClientBuilder>(new ClientBuilder());
	}
	void buildClient() {
		string name = clientLoader->getName();
		string surname = clientLoader->getSurname();
		string address = clientLoader->getAddress();
		string passport = clientLoader->getPassport();

		if (name == "" || surname == "") {
			throw invalid_argument("Имя и фамилия клиента обязательны");
		}

		this->clientBuilder->produceClientName(name, surname);

		if (address != "")
			this->clientBuilder->produceClientAddress(address);
		if (passport != "")
			this->clientBuilder->produceClientPassport(passport);
	}
	shared_ptr<Client> getClient() {
		return clientBuilder->getClient();
	}

private:
	shared_ptr<ClientLoader> clientLoader;
	shared_ptr<ClientBuilder> clientBuilder;
};
