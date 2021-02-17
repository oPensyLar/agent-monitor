#include "JsonParser.h"


int JsonParser::ParserRequest(kn::buffer<1024> arg0)
{
	std::string data = reinterpret_cast<char*>(arg0.data());
	json j;
	auto o = j.parse(data);		
	std::string strKey;
			
	for (auto& [key, value] : o.items())
	{
		if (key.compare("req") == 0x0)
		{
			passAuth = value["auth"]["pass"];
			reportCpu = value["cpu"];
			reportMem = value["mem"];
			reportDisk = value["disk"];
			reportProcs = value["procs"];			
		}			
	}

	return 0x0;
}


void JsonParser::BuildAuthFail(bool flag)
{
	pObject["auth"]["state"] = flag;
}


int JsonParser::Example()
{
	// create an empty structure (null)
	json j;

	// add a number that is stored as double (note the implicit conversion of j to an object)
	j["pi"] = 3.141;

	// add a Boolean that is stored as bool
	j["happy"] = true;

	// add a string that is stored as std::string
	j["name"] = "Niels";

	// add another null object by passing nullptr
	j["nothing"] = nullptr;

	// add an object inside the object
	j["answer"]["everything"] = 42;

	// add an array that is stored as std::vector (using an initializer list)
	j["list"] = { 1, 0, 2 };

	// add another object (using an initializer list of pairs)
	auto c = { "currency", "USD" };
	j["object"] = { c, {"value", 42.99} };

	std::string a = j.dump();
	// std::cout << a << std::endl;

	return 0x0;

}


void JsonParser::SetAuthPass(std::string arg0)
{
	localAuthPass = arg0;
}


void JsonParser::BuildResponse(MEMORYSTATUSEX arg0)
{
	
	pObject["mem"].push_back({ 
		{"percent", arg0.dwMemoryLoad},
		{"avail_extended_virtual", arg0.ullAvailExtendedVirtual},
		{"avail_page_file", arg0.ullAvailPageFile},
		{"avail_phys", arg0.ullAvailPhys},
		{"avail_virtual", arg0.ullAvailVirtual},
		{"total_page_file", arg0.ullTotalPageFile},
		{"total_phys", arg0.ullTotalPhys},
		{"total_virtual", arg0.ullTotalVirtual}
		});	
}


int JsonParser::LoadConfig()
{
	std::filebuf fb;

	if (fb.open("config.json", std::ios::in))
	{
		std::istream iFile(&fb);
		json j;
		auto jCfg = j.parse(iFile);
		passAuth = jCfg["auth"]["password"];

		return 0x0;
	}

	else
		return 0x1;
}


std::string JsonParser::GetPwdAtuh()
{
	return passAuth;
}


void JsonParser::BuildResponse(std::multimap<std::pair<std::string, DWORD>, DWORD> arg0)
{
	for (auto a : arg0)
	{
		
		pObject["procs"].push_back({ 
			{"nam", a.first.first}, 
			{"cpu_usage", -1}, 
			{"mem_usage", a.second},
			{"pid", a.first.second} });
	}
}


int JsonParser::BuildResponse(std::vector<dskInf> arg0)
{

	for(dskInf cDisk : arg0)
	{
		pObject["disk"].push_back({ {"path", cDisk.dsk}, {"total", cDisk.totalSpace}, {"free", cDisk.freeSpace}});
	}

	// std::cout << pObject.dump();

	return 0x0;
}


void JsonParser::BuildResponse(std::vector<PROCESSENTRY32> procs)
{

	PROCESSENTRY32 cProc;
	std::string procName;

	for (int i = 0x0; i < 4; i++)
	{
		cProc = procs.at(i);
		procName = cProc.szExeFile;

		pObject["procs"].push_back({ {"nam", cProc.szExeFile}, {"mem_usage", -1},  {"cpu_usage", -1}, {"pid", cProc.th32ProcessID} });
	}

	// std::cout << pObject.dump() << std::endl;
}

void JsonParser::BuildResponse(CHAR cpuUsage)
{
	pObject["cpu"].push_back({ {"usage", (int)cpuUsage} });
}


json JsonParser::GetJsonObject()
{
	std::cout << pObject.dump() << std::endl;
	return pObject;
}


std::string JsonParser::GetResponse()
{	
	JsonParser jParser;

	if (passAuth != localAuthPass)
	{
		jParser.BuildAuthFail(false);
	}

		else
		{

			jParser.BuildAuthFail(true);

			if (reportCpu)
			{
				Cpu cpu;
				jParser.BuildResponse(cpu.cpuusage());
			}

			if (reportProcs)
			{
				Process procs;
				procs.Openeables();
				std::vector<PROCESSENTRY32> allProcs = procs.GetProcs(0x2);

				Memory mem;
				std::multimap<std::pair<std::string, DWORD>, DWORD> procMemUsage;
				procMemUsage = mem.GetTopUsage(allProcs, 0x4);
				jParser.BuildResponse(procMemUsage);
			}

			if (reportMem)
			{
				Memory mem;
				MEMORYSTATUSEX  memGlobal = mem.GetMemGlobal();
				jParser.BuildResponse(memGlobal);
			}

			if (reportDisk)
			{
				Disk disk;
				disk.CalcUsage(ALL_DEVICES);
				std::vector<dskInf> dskUsage = disk.GetDiskInfo();
				jParser.BuildResponse(dskUsage);

			}

		}


	json jObj = jParser.GetJsonObject();
	std::string ret = jObj.dump();
	return ret;
}
