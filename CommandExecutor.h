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
        ulong id;
        string name;
        function<bool(vector<string> data)> callback;
    };

    CommandExecutor() : template_commands(), execution_commands() { }

    void addCommand(struct command &cmd);

    void addCommand(string name, function<bool(vector<string>)> callback);

    bool parseCommand(vector<string> data);

    void run();

private:
    struct execution_command {
        ulong id;
        vector<string> data;
    };
    vector<struct command> template_commands;
    vector<struct execution_command> execution_commands;
};


#endif //AUTOCLICKER_COMMANDEXECUTOR_H
