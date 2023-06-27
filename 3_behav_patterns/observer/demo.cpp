#include "observer.h"
#include <iostream>
#include <queue>
#include <memory>


int main() 
{
    std::cout << "Welcome to  pattern demo" << std::endl;

    auto cpu0Server = std::make_shared<CpuMonitoringServer>();
    auto cpu1Server = std::make_shared<CpuMonitoringServer>();
    auto cpu2Server = std::make_shared<CpuMonitoringServer>();
    auto discServer = std::make_shared<DiskMonitoringServer>();

    auto notifier = std::make_shared<LogMessageToConsole>();
    auto logger = std::make_shared<LogMsgToFile>("system.log");

    notifier->setme(notifier);
    logger->setme(logger);

    notifier->subsribe(cpu0Server);
    notifier->subsribe(cpu1Server);
    notifier->subsribe(cpu2Server);
    notifier->subsribe(discServer);

    logger->subsribe(discServer);
    logger->subsribe(cpu0Server);

    std::cout << "All ready" << std::endl;

    cpu0Server->inform_about_high_load();
    cpu1Server->inform_about_high_load();
    cpu2Server->inform_about_high_temperature();

    discServer->inform_disk_full();

    notifier->unsubsribe(cpu2Server);
    logger->subsribe(cpu2Server);

    cpu2Server->inform_about_high_temperature();

    notifier->unsubsribe(cpu2Server);
}