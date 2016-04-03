//
// Created by kamil on 01.04.16.
//

#ifndef AUTOCLICKER_COMMANDEXECUTOR_H
#define AUTOCLICKER_COMMANDEXECUTOR_H

#include <string>
#include <functional>
#include <vector>

using namespace std;

class CommandExecutor {
public:
    struct command {
        string name;
        function<bool(vector<string> data)> callback;
    };

    CommandExecutor() : commands() { }

    void addCommand(struct command &cmd);

    void addCommand(string name, function<bool(vector<string>)> callback);

    bool runCommand(string &line);

private:
    vector<struct command> commands;
};


#endif //AUTOCLICKER_COMMANDEXECUTOR_H
