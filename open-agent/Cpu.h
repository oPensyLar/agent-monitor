#pragma once

#include <windows.h>
#include <stdio.h>

typedef BOOL(__stdcall* pfnGetSystemTimes)(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
static pfnGetSystemTimes s_pfnGetSystemTimes = NULL;


class Cpu
{    

    HMODULE s_hKernel = NULL;
    
    void GetSystemTimesAddress()
    {
        if (s_hKernel == NULL)
        {
            s_hKernel = LoadLibrary("kernel32.dll");
            if (s_hKernel != NULL)
            {
                s_pfnGetSystemTimes = (pfnGetSystemTimes)GetProcAddress(s_hKernel, "GetSystemTimes");
                if (s_pfnGetSystemTimes == NULL)
                {
                    FreeLibrary(s_hKernel); s_hKernel = NULL;
                }
            }
        }
    }

public:
    CHAR cpuusage(void);
};

