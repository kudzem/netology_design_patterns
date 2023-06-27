#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include <windows.h>
#include <array>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <set>
#include <vector>

enum Severity {
    SYSTEM_WARNING,
    SYSTEM_ERROR,
    SYSTEM_FATAL
};

class Observer;

class Observable {

private:
    std::set<std::weak_ptr<Observer>, std::owner_less<std::weak_ptr<Observer>>> supscriptions;

public:
    void notify_all(Severity severity, const std::string& msg);
    int add_supscription(std::weak_ptr<Observer> new_subsciber);
    int delete_supscription(std::weak_ptr<Observer> old_subsciber);

    virtual ~Observable() {
        std::cout << "Destroy observable " << this << std::endl;
    }
};

class DiskMonitoringServer : public Observable {

public:
    void inform_disk_full();
    void inform_disk_corrupted();
};


class CpuMonitoringServer : public Observable {

public:
    void inform_about_high_load();
    void inform_about_high_temperature();
};


class Observer {
private:
    std::set<std::shared_ptr<Observable>> objects_to_watch;
    std::weak_ptr<Observer> _me;
public:
    void subsribe(std::shared_ptr<Observable> obj);
    void unsubsribe(std::shared_ptr<Observable> obj);
    virtual void update(Severity severity, const std::string& msg) = 0;
    //std::weak_ptr<Observer> get() {
    //    if (!me.expired()) return me;

    //    me = std::shared_ptr<Observer>(this);
    //    return me;
    //}

    std::weak_ptr<Observer> get() {
        return _me;
    }

    void setme(std::shared_ptr<Observer> me) {
        _me = me;
        return;
    }

    Observer()  {}
    //Observer(Observer& other) = default;
    //Observer(Observer&& other) = default;
    virtual ~Observer();
};



class LogMessageToConsole : public Observer {
public:
    LogMessageToConsole() : Observer() {}
protected:
    virtual void update(Severity severity, const std::string& msg);
};

class LogMsgToFile : public Observer {
private:
    std::string _filename;
public:
    LogMsgToFile(const std::string& filename) : Observer() {
        _filename = filename;
    }

protected:
    virtual void update(Severity severity, const std::string& msg);
};
