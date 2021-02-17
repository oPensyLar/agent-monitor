#pragma once

#include <iostream>
#include <fstream>
#include <kissnet.hpp>
#include <vector>
#include <json.hpp>
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
	std::string passAuth;
	int reportMem;
	int reportDisk;
	int reportProcs;
	std::string localAuthPass;

public:
	int Example();
	void SetAuthPass(std::string arg0);
	int ParserRequest(kn::buffer<1024> arg0);
	void BuildAuthFail(bool flag);
	void BuildResponse(std::vector< PROCESSENTRY32> procs);
	void BuildResponse(CHAR cpuUsage);
	void BuildResponse(MEMORYSTATUSEX arg0);
	int LoadConfig();
	std::string GetPwdAtuh();
	void BuildResponse(std::multimap<std::pair<std::string, DWORD>, DWORD> arg0);
	int BuildResponse(std::vector<dskInf> arg0);
	json GetJsonObject();
	std::string GetResponse();

};

