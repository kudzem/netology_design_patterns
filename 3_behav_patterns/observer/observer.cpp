#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "observer.h"

void
Observable::notify_all(Severity severity, const std::string& msg) {
    for (auto& subscriber : supscriptions) {
        subscriber.lock()->update(severity, msg);
    }
}

int Observable::add_supscription(std::weak_ptr<Observer> new_subsciber) {
    supscriptions.insert(new_subsciber);
    std::cout << "Observable(" << this << "): New subscriber " << new_subsciber.lock() << std::endl;
    std::cout << "Observable(" << this << "): Number of subscribers = " << supscriptions.size() << std::endl;
    return 0;
}

int Observable::delete_supscription(std::weak_ptr<Observer> old_subsciber) {
    if (supscriptions.find(old_subsciber) == supscriptions.end()) return 1;

    std::cout << "Observable(" << this << "): Number of subscribers = " << supscriptions.size() << std::endl;
    std::cout << "Observable(" << this << "): Erase subscriber " << old_subsciber.lock() << std::endl;
    supscriptions.erase(old_subsciber);
    std::cout << "Observable(" << this << "): Number of subscribers = " << supscriptions.size() << std::endl;
    return 0;
}

void DiskMonitoringServer::inform_disk_full() {
   notify_all(SYSTEM_WARNING, "Disk is full");
}

void DiskMonitoringServer::inform_disk_corrupted() {
   notify_all(SYSTEM_FATAL, "Disk is corrupted");
}


void CpuMonitoringServer::inform_about_high_load() {
   notify_all(SYSTEM_WARNING, "CPU is loaded fully");
}

void CpuMonitoringServer::inform_about_high_temperature() {
   notify_all(SYSTEM_FATAL, "High temperature. Risk of system reset");
};

//уметь добавлять не владеющие указатели на наблюдателей,
//оповещать наблюдателей о вызове каждого из методов,
//корректно обрабатывать разрушение объектов - наблюдателей.

void Observer::subsribe(std::shared_ptr<Observable> obj) {

    objects_to_watch.insert(obj);
    obj->add_supscription(get());
}

void Observer::unsubsribe(std::shared_ptr<Observable> obj) {

    if (objects_to_watch.find(obj) == objects_to_watch.end()) return;
    objects_to_watch.erase(obj);
    obj->delete_supscription(get());
    std::cout << "Observer(" << this << "): exit unsubscribe" << std::endl;
}

Observer::~Observer() {
    std::cout << "Observer(" << this << "): Destructor. Subscribers = " << objects_to_watch.size() << std::endl;

    for (auto& obj: objects_to_watch) {
        std::cout << "Observer(" << this << "): observes: " << obj << std::endl;
    }

    while(!objects_to_watch.empty()) {
        unsubsribe(*objects_to_watch.begin());
        std::cout << "Observer(" << this << "): Left subscribers = " << objects_to_watch.size() << std::endl;
    }
    std::cout << "Observer(" << this << "): Destructors end" << std::endl;
}

void LogMessageToConsole::update(Severity severity, const std::string& msg) {
    std::cout << "Log: " << msg << std::endl;
}

void LogMsgToFile::update(Severity severity, const std::string& msg) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::ofstream logfile(_filename, std::fstream::out | std::fstream::app);
        logfile << "Log: " << std::ctime(&now_time) << " : " << msg << std::endl;
}
