#pragma once

#include <kissnet.hpp>
#include <iostream>
#include "JsonParser.h"

namespace kn = kissnet;

#define REAL_ENDPOINT "0.0.0.0:7777"

class Socket
{

public:
	int DeployServer(std::string ipAddr, int port);

};

