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

void Memory::GetTopUsage(std::vector<PROCESSENTRY32> openeables, int limit)
{	
	HANDLE hProc;

	for (int i = 0x0; i < openeables.size(); i++)
	{
		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, openeables.at(i).th32ProcessID);
		GetMemProcess(hProc);
		CloseHandle(hProc);
	}

	return;
}
