#pragma once
#include <string>
#include "ClientPart.h"

using namespace std;

class ClientAddress : public ClientPart
{
public:
	ClientAddress(string address) : ClientPart() {
		this->address = address;
	}
	~ClientAddress() {}

private:
	string address;
};
