//
// Created by kamil on 01.04.16.
//

#ifndef AUTOCLICKER_COMMANDEXECUTOR_H
#define AUTOCLICKER_COMMANDEXECUTOR_H

#include <string>
#include <functional>
#include <vector>
#include <sstream>

using namespace std;

class CommandExecutor {
public:
    struct Command {
        string name;
        function<bool(vector<string> data)> callback;
    };

    CommandExecutor() : template_commands() { }

    void addCommand(struct Command &cmd);

    void addCommand(string name, function<bool(vector<string>)> callback);

    bool parseCommand(vector<string> data);
private:
    vector<struct Command> template_commands;
};


#endif //AUTOCLICKER_COMMANDEXECUTOR_H
