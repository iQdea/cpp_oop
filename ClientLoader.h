#pragma once
#include <string>
#include "Loader.h"

using namespace std;

class ClientLoader : public Loader {
public:
	ClientLoader(shared_ptr<Config> config, string configSection = "") : Loader(config, configSection) {}
	string getName() { return getString("Name"); }
	string getSurname() { return getString("Surname"); }
	string getAddress() { return getString("Address"); }
	string getPassport() { return getString("Passport"); }
};