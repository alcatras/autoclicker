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
    printf("========================================\n%s\nusage: %s %s\n========================================\n\n",
    name.c_str(), commandName.c_str(), baseUsage.c_str());

    for (int i = 0; i < options.size(); ++i) {
        struct Option currentArgument = options[i];
        printf("option:\n\t-%s, --%s\n\t\t%s\n\t\tusage: %s %s\n",
        currentArgument.shortName.c_str(), currentArgument.verboseName.c_str(), currentArgument.helpText.c_str(),
               currentArgument.shortName.c_str(), currentArgument.argumentsTemplate.c_str());
    }
    fflush(stdout);
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
                printf("Option <%s> with arguments: [ ", option.c_str());
                for (int j = 0; j < data.size(); ++j) {
                    printf("%s ", data[j].c_str());
                }
                printf("] failed.\n");
                exit(EXIT_FAILURE);
            }
            return;
        }
    }
    throw OptionNotSupported(("Cannot find given option: " + option).c_str());
}
