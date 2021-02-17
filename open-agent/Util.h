#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <Windows.h>


class Util
{

public:

	std::multimap<DWORD, DWORD> invert(std::map<DWORD, DWORD>&mymap)
	{

		std::multimap<DWORD, DWORD> multiMap;
		std::map<DWORD, DWORD> ::iterator it;

		for (it = mymap.begin(); it != mymap.end(); it++)
		{
			multiMap.insert(std::make_pair(it->second, it->first));
		}

		return multiMap;

	}

};


