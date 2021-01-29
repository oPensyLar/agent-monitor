#pragma once

#include <iostream>
#include <kissnet.hpp>
#include <vector>
#include <json.hpp>
#include <Windows.h>
#include <tlhelp32.h>
#include "Cpu.h"
#include "Process.h"
#include "Memory.h"
#include "Disk.h"

using json = nlohmann::json;
namespace kn = kissnet;

class JsonParser
{

private:
	json pObject;
	int reportCpu;
	int reportMem;
	int reportDisk;
	int reportProcs;

public:
	int Example();
	int ParserRequest(kn::buffer<1024> arg0);
	void BuildResponse(std::vector< PROCESSENTRY32> procs);
	void BuildResponse(CHAR cpuUsage);
	void BuildResponse(MEMORYSTATUSEX arg0);
	int BuildResponse(std::vector<dskInf> arg0);
	json GetJsonObject();
	std::string GetResponse();

};

