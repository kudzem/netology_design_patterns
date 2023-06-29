#include "chained_log_handlers.h"
#include <iostream>
#include <queue>
#include <memory>


int main() 
{
    std::cout << "Welcome to Chain of Responsibility pattern demo" << std::endl;

    auto umh = std::make_shared<DefaultMsgHandler>();
    auto wh = std::make_shared<WarningMsgHandler>();
    wh->SetNextHandler(umh);
    auto eh = std::make_shared<ErrorMsgHandler>();
    eh->SetNextHandler(wh);
    auto fh = std::make_shared<FatalMsgHandler>();
    fh->SetNextHandler(eh);

    LogWarningMsg m1("Build is being closed soon");
    LogErrorMsg m2("Lift number 1 is out of service. Be careful");
    LogCriticalMsg m3("Fire in building");
    LogMessage m4("5p.m. no emergencies. Head of security?");

    fh->Handle(m1);
    fh->Handle(m2);
    fh->Handle(m3);
    fh->Handle(m4);
}