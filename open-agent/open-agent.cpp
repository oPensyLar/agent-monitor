#include "Socket.h"
#include <iostream>
#include "JsonParser.h"
#include "Memory.h"
#include "Disk.h"
#include "Cpu.h"
#include "Process.h"
#include <vector>
#include <iostream>
#include <Windows.h>

int main()
{

    JsonParser jParser;      

    Process procs;
    procs.Openeables();
    std::vector<PROCESSENTRY32> allProcs = procs.GetProcs(0x2);

    Memory mem;
    mem.GetTopUsage(allProcs, 0x4);
    // mem.GetTopUsage(0x4);
    // HANDLE hProc = NULL;
    // mem.GetMemProcess(hProc);

    // MEMORYSTATUSEX memInf = mem.GetMemGlobal();
    // mem.GetMemProcess(GetCurrentProcess());

    Socket sck;
    std::cout << "[+] Listen on 0.0.0.0:9000" << std::endl;
    sck.DeployServer("0.0.0.0", 9000);

    return 0x0;
    
    // jParser.ParserRequest();
    // Process procs;
    // procs.Enumerate();
    // std::vector< PROCESSENTRY32> vecProcs = procs.GetProcs();
    // jParser.BuildResponse(vecProcs);
}