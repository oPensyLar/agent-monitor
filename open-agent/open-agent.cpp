#include "Socket.h"
#include <iostream>
#include "JsonParser.h"
#include <vector>
#include <iostream>

int main()
{
    Socket sck;
    JsonParser jCfg;
    
    if (jCfg.LoadConfig())
    {
        std::cerr << "[!] FAIL load config" << std::endl;
        return 0x1;
    }

        else
        {
            std::cout << "[+] Load config" << std::endl;
            std::cout << "[+] Listen on 0.0.0.0:9000" << std::endl;
            sck.SetCfg(jCfg);
            sck.DeployServer("0.0.0.0", 9000);
        }

    return 0x0;   
}