//
// Created by kamil on 01.04.16.
//

#include <sstream>
#include "CommandExecutor.h"

void CommandExecutor::addCommand(struct command &cmd) {
    for(vector<struct command>::iterator it = template_commands.begin(); it != template_commands.end(); ++it) {
        if(it->name == cmd.name)
            return;
    }
    cmd.id = template_commands.size();
    template_commands.push_back(cmd);
}

void CommandExecutor::addCommand(string name, function<bool(vector<string> data)> callback) {
    struct command cmd;
    cmd.name = name;
    cmd.callback = callback;
    addCommand(cmd);
}

void CommandExecutor::run() {
    for(vector<struct execution_command>::iterator it = execution_commands.begin(); it != execution_commands.end(); ++it) {
        template_commands[it->id].callback(it->data);
    }
}

bool CommandExecutor::parseCommand(string line) {
    if(line.empty()) {
        return true;
    }

    stringstream ss(line);
    string cmd, tmp;
    vector<string> data;

    ss >> cmd;
    while(!ss.eof()) {
        ss >> tmp;
        data.push_back(tmp);
    }

    for(vector<struct command>::iterator it = template_commands.begin(); it != template_commands.end(); ++it) {
        if(it->name.compare(cmd) == 0) {
            struct execution_command command;
            command.id = it->id;
            command.data = data;
            execution_commands.push_back(command);
            return true;
        }
    }
    return false;
}
