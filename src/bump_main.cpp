#include <iostream>
#include "bump_log.h"

int main(int argc, char *argv[])
{
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " configFile logFile" << std::endl;
        return 1;
    }

    #ifdef ENABLE_LOG
    if(!bump::Logger::initSingleton(argv[2], bump::Logger::LEVEL_DEBUG)) {
        std::cerr << "Failed to setup log" << std::endl;
        return 1;
    }
    #endif

    LOG_INFO("Program initialized");

    return 0;
}
