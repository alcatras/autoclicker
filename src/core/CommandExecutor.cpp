//
// Created by kamil on 01.04.16.
//

#include "CommandExecutor.h"

void CommandExecutor::addCommand(struct Command &cmd) {
    for (auto it = template_commands.begin(); it != template_commands.end(); ++it) {
        if (it->name == cmd.name)
            return;
    }
    template_commands.push_back(cmd);
}

void CommandExecutor::addCommand(string name, function<bool(vector<string> data)> callback) {
    struct Command cmd;
    cmd.name = name;
    cmd.callback = callback;
    addCommand(cmd);
}

bool CommandExecutor::parseCommand(vector<string> data) {
    if (data.empty()) {
        return true;
    }

    auto cmd = data[0];
    data.erase(data.begin());

    for (auto it = template_commands.begin(); it != template_commands.end(); ++it) {
        if (it->name.compare(cmd) == 0) {
            return it->callback(data);
        }
    }
    return false;
}
