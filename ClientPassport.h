#pragma once
#pragma once
#include <string>
#include "ClientPart.h"

using namespace std;

class ClientPassport : public ClientPart
{
public:
	ClientPassport(string passport) : ClientPart() {
		this->passport = passport;
	}
	~ClientPassport() {}

private:
	string passport;
};
