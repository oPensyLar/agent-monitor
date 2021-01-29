#include "Process.h"

void Process::Enumerate()
{

	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe = { 0 };	
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(h, &pe))
	{
		do
		{		
			vectorProcs.push_back(pe);

		} while (Process32Next(h, &pe));
	}

	CloseHandle(h);
}

void Process::Openeables()
{
	Enumerate();
	HANDLE hProc;
	std::multimap<DWORD, HANDLE> mapOpeneables;
	for(int i = 0x0; i < vectorProcs.size(); i++)
	{

		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, vectorProcs.at(i).th32ProcessID);

		if (hProc != NULL)
		{			
			vectorOpeneables.push_back(vectorProcs.at(i));
		}

		CloseHandle(hProc);
	}

	return;
}


std::vector<PROCESSENTRY32> Process::GetProcs(int flag)
{
	switch (flag)
	{
		case 0x1:
			return vectorProcs;
		break;

		case 0x2:
			return vectorOpeneables;
		break;
	}
		
	return vectorProcs;
}
