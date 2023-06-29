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

enum MessageType {
    LOG_UNKNOWN,
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARNING
};

class LogMessage {
protected:
    std::string _message;
    MessageType _type;

public:
    LogMessage(MessageType type, std::string message) : _message(message), _type(type) {}
    LogMessage(std::string message) : _message(message), _type(LOG_UNKNOWN) {}
    MessageType get_type() const { return _type; }
    const std::string& get_message() const { return _message; }
};

class LogCriticalMsg : public LogMessage {
public:
    LogCriticalMsg(std::string message) : LogMessage(LOG_FATAL, message) {}
};

class LogWarningMsg : public LogMessage {
public:
    LogWarningMsg(std::string message) : LogMessage(LOG_WARNING, message) {}
};

class LogErrorMsg : public LogMessage {
public:
    LogErrorMsg(std::string message) : LogMessage(LOG_ERROR, message) {}
};


class ResponsibleHandler {
protected:
    std::shared_ptr<ResponsibleHandler> _nextHandler;
public:
    ResponsibleHandler(std::shared_ptr<ResponsibleHandler>& next) : _nextHandler(next){}
    ResponsibleHandler() = default;
    virtual ~ResponsibleHandler() = default;

    void SetNextHandler(std::shared_ptr<ResponsibleHandler> next) {
        _nextHandler = next;
    }

    virtual bool ChechICanDo(LogMessage& job) = 0;

    int Handle(LogMessage& job) {
        if (!ChechICanDo(job)) {
            if (_nextHandler) return _nextHandler->Handle(job);
            return -1;
        }

        return Execute(job);
    }

private:

    virtual int Execute(LogMessage& job) = 0;
};

class FatalMsgHandler : public  ResponsibleHandler {
private:
    virtual int Execute(LogMessage& job) override {
        std::cout << "Please leave your building immideately" << std::endl;
        std::cout << "FATAL!!!: " << job.get_message() << std::endl;
        return 0;
    }

    virtual bool ChechICanDo(LogMessage& job) override {
        return job.get_type() == LOG_FATAL;
    }
};

class ErrorMsgHandler : public  ResponsibleHandler {
private:
    virtual int Execute(LogMessage& job) override {
        std::cout << "Error: " << job.get_message() << std::endl;
        return 0;
    }

    virtual bool ChechICanDo(LogMessage& job) override {
        return job.get_type() == LOG_ERROR;
    }
};

class WarningMsgHandler : public  ResponsibleHandler {
private:
    virtual int Execute(LogMessage& job) override {
        std::cout << "Warning: " << job.get_message() << std::endl;
        return 0;
    }

    virtual bool ChechICanDo(LogMessage& job) override {
        return job.get_type() == LOG_WARNING;
    }
};

class DefaultMsgHandler : public  ResponsibleHandler {
private:
    virtual int Execute(LogMessage& job) override {
        std::cout << "Log: " << job.get_message() << std::endl;
        return 0;
    }

    virtual bool ChechICanDo(LogMessage& job) override {
        return true;
    }
};

