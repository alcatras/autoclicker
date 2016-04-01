#include <stdlib.h>
#include <iostream>
#include "ArgParser.h"
#include "devices/VirtualMouse.h"
#include "CommandExecutor.h"

int main(int argc, const char **argv) {

    CommandExecutor commandExecutor = CommandExecutor();

    ArgParser argParser = ArgParser();

    argParser.setName("Mouse emulator.");
    argParser.setCommandName(argv[0]);
    argParser.setBaseUsage("[option1] [args1] [option2] [args2] ...");

    ArgParser::option helpOpt = ArgParser::option();
    helpOpt.short_name = "h";
    helpOpt.verbose_name = "help";
    helpOpt.help_text = "Shows this help page.";
    helpOpt.argt = "";
    helpOpt.callback = [&](vector<string>) -> bool {
        argParser.show_help();
        exit(EXIT_SUCCESS);
    };
    argParser.addArgument(helpOpt);

    ArgParser::option fileOpt = ArgParser::option();
    fileOpt.short_name = "f";
    fileOpt.verbose_name = "file";
    fileOpt.help_text = "Loads chain of commands from files.";
    fileOpt.argt = "[filename1] [filename2] ...";
    fileOpt.callback = [&](vector<string> data) -> bool {
        cout << "--file option is not implemented at this point." << endl;
        return false;
    };
    argParser.addArgument(fileOpt);

    ArgParser::option commandOpt = ArgParser::option();
    commandOpt.short_name = "c";
    commandOpt.verbose_name = "command";
    commandOpt.help_text = "Executes commands.";
    commandOpt.argt = "[command1] [command2] ...";
    commandOpt.callback = [&](vector<string> data) -> bool {
        for (int i = 0; i < data.size(); ++i) {
            cout << "executing commands: " << data[i];
        }
        return true;
    };
    argParser.addArgument(commandOpt);

    cout << "> Parsing input." << endl;
    argParser.parse(argc, argv);

    cout << "> Initializing virtual devices." << endl;
    VirtualMouse virtualMouse = VirtualMouse(1920, 1080);
    virtualMouse.create();



    cout << "> Destroying virtual devices." << endl;
    virtualMouse.destroy();

    exit(EXIT_SUCCESS);
}