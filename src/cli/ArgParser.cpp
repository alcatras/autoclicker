//
// Created by kamil on 01.04.16.
//

#include "ArgParser.h"

void ArgParser::addOption(string shortName, string verboseName, string helpText, string argumentsTemplate,
                          function<bool(vector<string>)> callback) {
    struct Option opt;
    opt.shortName = shortName;
    opt.verboseName = verboseName;
    opt.helpText = helpText;
    opt.argumentsTemplate = argumentsTemplate;
    opt.callback = callback;
    options.push_back(opt);
}

void ArgParser::showHelp() {
    cout << "========================================" << endl << name << endl << "usage: " <<
    commandName << " " << baseUsage << endl << "========================================" << endl << endl;

    for (int i = 0; i < options.size(); ++i) {
        struct Option currentArgument = options[i];
        cout << "option:" << endl << "\t-" << currentArgument.shortName << ", --" << currentArgument.verboseName <<
        endl << "\t\t" << currentArgument.helpText << endl << "\t\tusage: " << currentArgument.shortName << " " <<
        currentArgument.argumentsTemplate << endl;
    }
    cout.flush();
}

void ArgParser::parse(int argc, const char **argv) {
    if (argc < 2) {
        showHelp();
        exit(EXIT_FAILURE);
    }

    string currentOption = string();
    auto currentData = vector<string>();

    for (int i = 1; i < argc; ++i) {
        string parsedArrgument = argv[i];

        if (parsedArrgument[0] == '-') {
            if (!currentOption.empty()) {
                evaluate(currentOption, currentData);
                currentData.clear();
            }
            currentOption = parsedArrgument.substr((parsedArrgument[1] == '-') ? 2 : 1);
        } else {
            currentData.push_back(parsedArrgument);
        }
    }
    evaluate(currentOption, currentData);
}

void ArgParser::evaluate(string option, vector<string> data) {
    for (int i = 0; i < options.size(); ++i) {
        auto currentOption = options[i];

        if (option.compare(currentOption.shortName) == 0 || option.compare(currentOption.verboseName) == 0) {
            if (!currentOption.callback(data)) {
                cout << "Option <" << option << "> with arguments: [ ";
                for (int j = 0; j < data.size(); ++j) {
                    cout << data[j] << " ";
                }
                cout << "] failed." << endl;
                exit(EXIT_FAILURE);
            }
            return;
        }
    }
    throw OptionNotSupported(("Cannot find given option: " + option).c_str());
}
