#include "iostream"
#include "exception"

#include "Config.h"
#include "ClientLoader.h"
#include "ClientBuilder.h"
#include "ClientDirector.h"

#include "AccountDebit.h"
#include "Bank.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout.setf(ios::fixed);
	cout.precision(2);

	try {
		shared_ptr<Config> config(new Config());
		config->readFile("test2.ini");
		
		Bank bank(config, "Bank1");
		bank.load();
	}
	catch (exception excep) {
		cout << excep.what() << endl;
	}
	catch (...) {
		cout << "Неизвестная ошибка." << endl;
	}

	return 0;
}