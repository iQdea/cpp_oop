#pragma once
#include <vector>
#include <memory>
#include "ClientPart.h"

using namespace std;

class Client {
public:
    void addPart(shared_ptr<ClientPart> clientPart) {
        clientPartList.push_back(clientPart);
    }
private:
    vector<shared_ptr<ClientPart>> clientPartList;
};
