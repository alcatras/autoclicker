//
// Created by kamil on 01.04.16.
//

#ifndef AUTOCLICKER_ARGPARSER_H
#define AUTOCLICKER_ARGPARSER_H

#include <vector>
#include <functional>
#include <string>

using namespace std;

class ArgParser {
public:
    struct option {
        string short_name;
        string verbose_name;
        string help_text;
        string argt;
        std::function<bool(vector<string>)> callback;
    };

    ArgParser() : options() { }

    void addArgument(struct option argument) {
        options.push_back(argument);
    }

    void setName(string summary) {
        this->name = summary;
    }

    void setCommandName(string command) {
        this->command_name = command;
    }

    void setBaseUsage(string usage) {
        this->base_usage = usage;
    }

    void show_help();

    void parse(int argc, const char **argv);

private:
    std::vector<option> options;
    string name;
    string command_name;
    string base_usage;

    bool evaluate(string option, vector<string> data);
};


#endif //AUTOCLICKER_ARGPARSER_H
