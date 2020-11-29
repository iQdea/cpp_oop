#include "iostream"
#include "exception"

#include "Config.h"
#include "ClientLoader.h"
#include "ClientBuilder.h"
#include "ClientDirector.h"

#include "AccountDebit.h"
#include "Bank.h"
//#include "FileSystem.h"
//#include "StorageArchive.h"
//#include "StorageSeparate.h"
//#include "Test.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	try {
		shared_ptr<Config> config(new Config());
		config->readFile("test1.ini");
		
		Bank bank(config, "Bank1");
		bank.load();


		//ClientBuilder clientBuilder;
		//ClientDirector clientDirector(&clientBuilder, &clientLoader);
		//ClientList clientList;

		//clientLoader.setSection("Client1");
		//clientDirector.buildClient();
		//clientList.add(clientBuilder.getClient());

		//clientLoader.setSection("Client2");
		//clientDirector.buildClient();
		//clientList.add(clientBuilder.getClient());

		//clientLoader.setSection("Client3");
		//clientDirector.buildClient();
		//clientList.add(clientBuilder.getClient());
	}
	catch (exception excep) {
		cout << excep.what() << endl;
	}
	catch (...) {
		cout << "Неизвестная ошибка." << endl;
	}

	return 0;
}