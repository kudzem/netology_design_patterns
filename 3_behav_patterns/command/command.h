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

class Command {
protected:
    std::string _cmd;
    bool _cancelled;
    virtual void apply() {};
public:
    Command(const std::string& cmd) : _cmd(cmd), _cancelled(false) {}
    Command(const Command& cmd) = default;
    virtual ~Command() = default;

    void cancel() {
        _cancelled = true;
    }

    void execute() {
        if (_cancelled == true) return;
        apply();
    }
};

class SystemCommand : public Command {
public:
    SystemCommand(const std::string& cmd) : Command(cmd) {}
    virtual ~SystemCommand() = default;
protected:
    //virtual void apply() override { WinExec(_cmd.c_str(), 1); }
    virtual void apply() {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(_cmd.c_str(), "r"), _pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        std::cout << result << std::endl;
        return;
    }
};

class LogMessageToConsole : public Command {
public:
    LogMessageToConsole(const std::string& msg) : Command(msg) {}
    virtual ~LogMessageToConsole() = default;
protected:
    virtual void apply() override {
        std::cout << "Log: " << _cmd << std::endl;
    }
};

class LogMsgToFile : public Command {
private:
    std::string _filename;
public:
    LogMsgToFile(const std::string& filename, const std::string& msg) : Command(msg) {
        _filename = filename;
    }

protected:
    virtual void apply() override {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::ofstream logfile(_filename, std::fstream::out | std::fstream::app);

        logfile << "Log: " << std::ctime(&now_time) << " : " << _cmd << std::endl;
    }
};
