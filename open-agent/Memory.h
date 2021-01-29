#pragma once

#define SWAP_MEMORY 0x1
#define VIRTUAL_MEMORY 0x2

#include <Windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <map>

class Memory
{

private:
	std::map<DWORD, DWORD> vecMemByProcs;

public:
	// Getters
	int GetFree(int flag);
	MEMORYSTATUSEX GetMemGlobal();
	int GetMemProcess(HANDLE hProc, PROCESS_MEMORY_COUNTERS_EX* pmc);
	int GetUsage(int flag);
	void GetTopUsage(std::vector<PROCESSENTRY32> openeables, int limit);
	
};

