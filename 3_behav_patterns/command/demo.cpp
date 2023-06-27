#include "command.h"
#include <iostream>
#include <queue>
#include <memory>


int main() 
{
    std::cout << "Welcome to Command pattern demo" << std::endl;

    std::queue<Command*> todo_list;

    while (true) {
        std::cout << "Enter a new command? (y/n) ";
        std::string choise;
        std::cin >> choise;
        if (choise != "y") break;

        std::cout << "Which command ? " << std::endl << std::flush;
        std::string cmd;
        std::cin.ignore();
        std::getline(std::cin, cmd);

        todo_list.push(new LogMessageToConsole(cmd));
        todo_list.push(new SystemCommand(cmd));
        todo_list.push(new LogMsgToFile("actions.log", cmd));
    }

    while(!todo_list.empty()) {
        auto task = todo_list.front();
        todo_list.pop();
        task->execute();
        delete task;
    }

}