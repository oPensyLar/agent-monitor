#pragma once
#include <iostream>

class Protocol
{

	/*
	
	get
	{
		"disk" : 1,
		"mem" : 1,
		"process" : 1
	}

	*/

	/*
	
		process {

			"1" : {

			"pid" : 123,
			"nam" : "explorer.exe",
			"path" : "C:\\explorer.exe",

			},

			"2" : {

			"pid" : 444,
			"nam" : "taskmgr.exe",
			"path" : "C:\\taskmgr.exe",

			}

		}

	
	*/

	int ParserRequest(std::string req);
	int BuildResponse();
	int BuildProcess();
	int BuildMem();
	int BuildUsageCpu();

};

