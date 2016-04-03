//
// Created by kamil on 01.04.16.
//

#include "CommandExecutor.h"

void CommandExecutor::addCommand(struct command &cmd) {
    commands.push_back(cmd);
}

void CommandExecutor::addCommand(string name, function<bool(vector<string> data)> callback) {
    struct command cmd;
    cmd.name = name;
    cmd.callback = callback;
    commands.push_back(cmd);
}

bool CommandExecutor::runCommand(string &line) {
    return false;
}
