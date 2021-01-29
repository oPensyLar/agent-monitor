#include "Disk.h"


int Disk::GetFree(std::string disk)
{	
	unsigned __int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	
	GetDiskFreeSpaceEx(disk.c_str(), 
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);

	// i64FreeBytesToCaller /= (1024 * 1024);
	i64TotalBytes /= (1024 * 1024);
	i64FreeBytes /= (1024 * 1024);

	dskInf d = { disk, i64FreeBytes, i64TotalBytes };
	diskInfo.push_back(d);

	return 0;
}


int Disk::CalcUsage(int flag)
{
	switch (flag)
	{
		case ALL_DEVICES:
			GetQuantity();
			
			for (int i = 0x0; i < vectDisk.size(); i++)
				GetFree(vectDisk.at(i));

		break;

	}

	return 0;
}


std::vector<dskInf> Disk::GetDiskInfo()
{
	return diskInfo;
}


int Disk::GetQuantity()
{

	CHAR volName[MAX_PATH] = "";
	HANDLE volHandle = FindFirstVolume(volName, ARRAYSIZE(volName));
	BOOL haveVols;

	do
	{
		GetVolPath(volName);
		haveVols = FindNextVolume(volHandle, volName, ARRAYSIZE(volName));

	} while (haveVols == TRUE);

	return 0;
}


int Disk::GetVolPath(CHAR *vName)
{
	LPCH nam = (LPCH) new BYTE[MAX_PATH * sizeof(LPCH)];
	DWORD lenNam = MAX_PATH;
	DWORD retLen = 0x0;
	
	if (GetVolumePathNamesForVolumeName(vName, nam, lenNam, &retLen))
		vectDisk.push_back(nam);

	return 0;
}
