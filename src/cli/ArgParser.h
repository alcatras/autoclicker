//
// Created by kamil on 01.04.16.
//

#ifndef AUTOCLICKER_ARGPARSER_H
#define AUTOCLICKER_ARGPARSER_H

#include <vector>
#include <functional>
#include <string>
#include <stdlib.h>

using namespace std;

class ArgParser {
public:
    class OptionNotSupported : logic_error {
    public:
        OptionNotSupported(const char* msg) : logic_error(msg) { }
    };

    struct Option {
        string shortName;
        string verboseName;
        string helpText;
        string argumentsTemplate;
        function<bool(vector<string>)> callback;
    };

    ArgParser() : options() { }

    void addOption(struct Option &argument) {
        options.push_back(argument);
    }

    void addOption(string shortName, string verboseName, string helpText, string argumentsTemplate,
                   function<bool(vector<string>)> callback);

    void setName(string summary) {
        this->name = summary;
    }

    void setCommandName(string command) {
        this->commandName = command;
    }

    void setBaseUsage(string usage) {
        this->baseUsage = usage;
    }

    void showHelp();

    void parse(int argc, const char **argv);

private:
    std::vector<Option> options;
    string name;
    string commandName;
    string baseUsage;

    void evaluate(string option, vector<string> data);
};


#endif //AUTOCLICKER_ARGPARSER_H
