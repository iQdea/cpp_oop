﻿#pragma once
#include <vector>
#include <memory>
#include "ClientPart.h"

using namespace std;

class Client {
public:
    void addPart(shared_ptr<ClientPart> clientPart) {
        clientPartList.push_back(clientPart);
    }
    bool isDoubtful() {
        return clientPartList.size() < 3;
    }
private:
    vector<shared_ptr<ClientPart>> clientPartList;
};
