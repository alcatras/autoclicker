//
// Created by kamil on 01.04.16.
//

#include <stdlib.h>
#include <iostream>
#include "ArgParser.h"

void ArgParser::show_help() {
    cout << "========================================" << endl << this->name << endl << "usage: " <<
    this->command_name << " " << this->base_usage << endl << "========================================" << endl << endl;

    for (int i = 0; i < this->options.size(); ++i) {
        struct option current_argument = this->options[i];
        cout << "option:" << endl << "\t-" << current_argument.short_name << ", --" << current_argument.verbose_name <<
        endl << "\t\t" << current_argument.help_text << endl << "\t\tusage: " << current_argument.short_name << " " <<
        current_argument.argt << endl;
    }
}

void ArgParser::parse(int argc, const char **argv) {
    if (argc < 2) {
        show_help();
        exit(EXIT_FAILURE);
    }

    string current_option = string();
    vector<string> current_data = vector<string>();

    for (int i = 1; i < argc; ++i) {
        string current_argument = argv[i];

        if (current_argument[0] == '-') {
            if (!current_option.empty()) {
                evaluate(current_option, current_data);
                current_data.clear();
            }
            current_option = current_argument.substr(current_argument[1] == '-' ? 2 : 1);
        } else {
            current_data.push_back(current_argument);
        }
    }
    evaluate(current_option, current_data);
}

bool ArgParser::evaluate(string option, vector<string> data) {
    for (int i = 0; i < this->options.size(); ++i) {
        struct option current_option = this->options[i];

        if (option.compare(current_option.short_name) == 0 || option.compare(current_option.verbose_name) == 0) {
            current_option.callback(data);
            return true;
        }
    }
    return false;
}
