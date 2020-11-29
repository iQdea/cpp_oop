#pragma once
#include <string>
#include "ClientPart.h"

using namespace std;

class ClientName : public ClientPart
{
public:
	ClientName(string name, string surname) : ClientPart() {
		this->name = name;
		this->surname = surname;
	}
	~ClientName() {}
private:
	string name;
	string surname;
};
