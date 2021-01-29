#include "Cpu.h"

CHAR Cpu::cpuusage(void)
{

    GetSystemTimesAddress();

    FILETIME               ft_sys_idle;
    FILETIME               ft_sys_kernel;
    FILETIME               ft_sys_user;

    ULARGE_INTEGER         ul_sys_idle;
    ULARGE_INTEGER         ul_sys_kernel;
    ULARGE_INTEGER         ul_sys_user;

    static ULARGE_INTEGER    ul_sys_idle_old;
    static ULARGE_INTEGER  ul_sys_kernel_old;
    static ULARGE_INTEGER  ul_sys_user_old;

    CHAR  usage = 0;

    // we cannot directly use GetSystemTimes on C language
    /* add this line :: pfnGetSystemTimes */
    s_pfnGetSystemTimes(&ft_sys_idle,    /* System idle time */
        &ft_sys_kernel,  /* system kernel time */
        &ft_sys_user);   /* System user time */


    // Could been optimized away...
    CopyMemory(&ul_sys_idle, &ft_sys_idle, sizeof(FILETIME)); 

    // Could been optimized away...
    CopyMemory(&ul_sys_kernel, &ft_sys_kernel, sizeof(FILETIME)); 

    // Could been optimized away...
    CopyMemory(&ul_sys_user, &ft_sys_user, sizeof(FILETIME)); 

    usage =
        (
            (
                (
                    (
                        (ul_sys_kernel.QuadPart - ul_sys_kernel_old.QuadPart) +
                        (ul_sys_user.QuadPart - ul_sys_user_old.QuadPart)
                        )
                    -
                    (ul_sys_idle.QuadPart - ul_sys_idle_old.QuadPart)
                    )
                *
                (100)
                )
            /
            (
                (ul_sys_kernel.QuadPart - ul_sys_kernel_old.QuadPart) +
                (ul_sys_user.QuadPart - ul_sys_user_old.QuadPart)
                )
            );

    ul_sys_idle_old.QuadPart = ul_sys_idle.QuadPart;
    ul_sys_user_old.QuadPart = ul_sys_user.QuadPart;
    ul_sys_kernel_old.QuadPart = ul_sys_kernel.QuadPart;

    return usage;

}
