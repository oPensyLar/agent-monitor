#include "Memory.h"


int Memory::GetFree(int flag)
{
	return 0;
}


int Memory::GetMemProcess(HANDLE hProc, PROCESS_MEMORY_COUNTERS_EX *pmc)
{

	GetProcessMemoryInfo(hProc, (PPROCESS_MEMORY_COUNTERS)pmc, sizeof(pmc));

	return 0x0;
}


MEMORYSTATUSEX Memory::GetMemGlobal()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	GlobalMemoryStatusEx(&memInfo);

	return memInfo;
}


int Memory::GetUsage(int flag)
{

	switch (flag)
	{
		case SWAP_MEMORY:			
		break;
	}

	return 0;
}


std::map<DWORD, DWORD> Memory::GetPair(int flag)
{
	switch (flag)
	{
		case 0x1:
			return pairMemPid;
		break;
	}

	return std::map<DWORD, DWORD>();
}


std::multimap<std::pair<std::string, DWORD>, DWORD> Memory::GetTopUsage(std::vector<PROCESSENTRY32> openeables, int limit)
{	
	HANDLE hProc;
	PROCESS_MEMORY_COUNTERS_EX procMemEx;	

	for (int i = 0x0; i < openeables.size(); i++)
	{
		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, openeables.at(i).th32ProcessID);
		GetProcessMemoryInfo(hProc, (PPROCESS_MEMORY_COUNTERS)&procMemEx, sizeof(procMemEx));
		pairMemPid.insert({ procMemEx.PrivateUsage / 1024, i });
		CloseHandle(hProc);
	}

	auto usageAsc = invert(pairMemPid);
	std::multimap<DWORD, DWORD> ::iterator iter = pairMemPid.begin();	
	int indexLimit = usageAsc.size() - limit;

	// Set iterator on last 4 lements
	std::advance(iter, indexLimit);

	// Keep last elements
	pairMemPid.erase(pairMemPid.begin(), iter);


	// Return multimap
	std::multimap<std::pair<std::string, DWORD>, DWORD> mapFinal;
	PROCESSENTRY32 cProc;

	for (auto a : pairMemPid)
	{
		cProc = openeables.at(a.second);
		mapFinal.insert({ {cProc.szExeFile, cProc.th32ProcessID}, a.first });
	}

	return mapFinal;
}
