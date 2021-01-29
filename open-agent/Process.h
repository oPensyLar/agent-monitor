#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <iostream>
#include <map>

class Process
{

private:
	std::vector<PROCESSENTRY32> vectorProcs;
	std::vector<PROCESSENTRY32> vectorOpeneables;

public:
	void Enumerate();
	void Openeables();
	std::vector<PROCESSENTRY32> GetProcs(int flag);
};

