#pragma once

#include <windows.h>
#include <fileapi.h>
#include <iostream>
#include <vector>
#include <map>

#define ALL_DEVICES 0x1

typedef struct dskInf
{
	std::string dsk;
	unsigned __int64 freeSpace;
	unsigned __int64 totalSpace;
};


class Disk
{

private:
	std::vector<std::string> vectDisk;
	std::vector<dskInf> diskInfo;

public:
	// Getters
	int GetFree(std::string disk);
	int CalcUsage(int flag);
	std::vector<dskInf> GetDiskInfo();
	int GetQuantity();
	int GetVolPath(CHAR *vName);
	
};

