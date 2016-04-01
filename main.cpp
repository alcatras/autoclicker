#include <stdlib.h>
#include "ArgParser.h"

int main(int argc, const char **argv) {
    ArgParser argParser = ArgParser();

    argParser.setName("Mouse emulator.");
    argParser.setCommandName(argv[0]);
    argParser.setBaseUsage("[option1] [args1] [option2] [args2] ...");

    ArgParser::option helpArg = ArgParser::option();
    helpArg.short_name = "h";
    helpArg.verbose_name = "help";
    helpArg.help_text = "Shows this help page.";
    helpArg.argt = "";
    helpArg.callback = [&](vector<string>) -> bool {
        argParser.show_help();
        exit(EXIT_SUCCESS);
    };
    argParser.addArgument(helpArg);

    ArgParser::option fileArg = ArgParser::option();
    fileArg.short_name = "f";
    fileArg.verbose_name = "file";
    fileArg.help_text = "Loads chain of commands from files.";
    fileArg.argt = "[filename1] [filename2] ...";
    argParser.addArgument(fileArg);

    ArgParser::option commandArg = ArgParser::option();
    commandArg.short_name = "c";
    commandArg.verbose_name = "command";
    commandArg.help_text = "Executes commands.";
    commandArg.argt = "[command1] [command2] ...";
    argParser.addArgument(commandArg);

    argParser.parse(argc, argv);
    exit(EXIT_SUCCESS);
}