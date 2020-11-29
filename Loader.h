#pragma once
#include <string>
#include "Config.h"

using namespace std;

class Loader {
public:
	Loader(shared_ptr<Config> config, string configSection = "") {
		this->config = config;
		this->configSection = configSection;
	}
	virtual ~Loader() = 0 {}

	void setConfigSection(string configSection) {
		this->configSection = configSection;
	}
	template<typename T> T get(string param, T defaultValue) {
		T result;

		try {
			result = config->lookup(configSection, param).getValue<T>();
		}
		catch (...) {
			result = defaultValue;
		}

		return result;
	}
	string getString(string param, string defaultValue = "") {
		return get<string>(param, defaultValue);
	}
	template<typename T> T getNumber(string param, T defaultValue = 0) {
		return get<T>(param, defaultValue);
	}
	template<typename T> vector<T> getList(string param, char delim = ',') {
		vector<T> result;
		T item;
		string str;
		stringstream items(getString(param));
		while (getline(items, str, delim)) {
			stringstream ss(str);
			ss >> item;
			result.push_back(item);
		}
		return result;
	}
	template<typename T> vector<pair<T, T>> getPairList(string param, char delim1 = '|', char delim2 = ':') {
		vector<pair<T, T>> result;
		vector<string> list = getList<string>(param, delim1);
		for (string str1 : list) {
			vector<T> items;
			T item;
			string str2;
			stringstream pair(str1);
			while (getline(pair, str2, delim2)) {
				stringstream ss(str2);
				ss >> item;
				items.push_back(item);
			}
			if (items.size() == 2) {
				result.push_back(make_pair(items[0], items[1]));
			}
		}
		sort(result.begin(), result.end());

		return result;
	}
private:
	string configSection = "";
	shared_ptr<Config> config = 0;
};
