#include <iostream>
#include "log.h"
#include "config.h"
#include "app.h"

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

    bump::Config cfg;
    if(!cfg.load(argv[1])) {
        LOG_ERROR("Failed to read config from %s", argv[1]);
        return 1;
    }

    bump::App app;
    if(!app.init(cfg)) {
        LOG_ERROR("Failed to initialize App");
        return 1;
    }

    if(!app.run()) {
        LOG_ERROR("Something wrong happened during App::run");
        return 1;
    }

    return 0;
}
