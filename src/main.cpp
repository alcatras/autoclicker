#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "cli/ArgParser.h"
#include "core/dev/VirtualMouse.h"
#include "core/CommandExecutor.h"
#include "core/commands.h"

using namespace std;

class MainClass {
public:
    MainClass() : argParser(), commandExecutor(), virtualMouse(screenWidth(), screenHeight()) { }

    void create() {
        virtualMouse.create();
    }

    void destroy() {
        virtualMouse.destroy();
    }

    void parse(int argc, const char **argv) {
        argParser.parse(argc, argv);
    }

    void setup_options(string appName) {
        argParser.setName("Mouse emulator.");
        argParser.setCommandName(appName);
        argParser.setBaseUsage("[option1] [args1] [option2] [args2] ...");

        argParser.addOption(
                "h",
                "help",
                "Shows this help page.",
                "",
                [&](vector<string>) -> bool {
                    argParser.showHelp();
                    exit(EXIT_SUCCESS);
                }
        );

        argParser.addOption(
                "f",
                "file",
                "Loads chain of commands from files.",
                "[filename1] [filename2] ...",
                [&](vector<string> data) -> bool {
                    string line;
                    for (int i = 0; i < data.size(); ++i) {
                        ifstream file;
                        file.open(data[i]);
                        if (file.is_open()) {
                            printf("Reading file: %s.\n", data[i].c_str());
                            while (getline(file, line)) {
                                stringstream ss(line);
                                vector<string> _data;
                                string tmp;
                                while (!ss.eof()) {
                                    ss >> tmp;
                                    _data.push_back(tmp);
                                }
                                if (!commandExecutor.parseCommand(_data)) {
                                    printf("Error parsing command: %s.\n", line.c_str());
                                    exit(EXIT_FAILURE);
                                }
                            }
                            file.close();
                        } else {
                            printf("Cannot open file: %s.\n", data[i].c_str());
                            exit(EXIT_FAILURE);
                        }
                    }
                    return true;
                }
        );

        argParser.addOption(
                "c",
                "command",
                "Executes command.",
                "[command1] [arguments1]",
                [&](vector<string> data) -> bool {
                    if (!commandExecutor.parseCommand(data)) {
                        printf("Error parsing command: %s.\n", data[0].c_str());
                        exit(EXIT_FAILURE);
                    }

                    return true;
                }
        );
    }

    void setup_executor() {
        commandExecutor.addCommand(
                "set_delay",
                [&](vector<string> data) -> bool {
                    auto result = get_int_property(data);
                    if(result.first.compare("mouse") == 0) {
                        virtualMouse.setDelay(result.second);
                    }
                    return true;
                }
        );
        commandExecutor.addCommand(
                "mouse_left",
                [&](vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_LEFT);
                }
        );
        commandExecutor.addCommand(
                "mouse_right",
                [&](vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_RIGHT);
                }
        );
        commandExecutor.addCommand(
                "mouse_middle",
                [&](vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_MIDDLE);
                }
        );
        commandExecutor.addCommand(
                "mouse_move",
                [&](vector<string> data) -> bool {
                    return mouse_move(data, virtualMouse);
                }
        );
        commandExecutor.addCommand(
                "mouse_reset",
                [&](vector<string> data) -> bool {
                    return mouse_reset(data, virtualMouse);
                }
        );
        commandExecutor.addCommand(
                "mouse_scroll",
                [&](vector<string> data) -> bool {
                    return mouse_scroll(data, virtualMouse);
                }
        );
    }

private:
    ArgParser argParser;
    CommandExecutor commandExecutor;
    VirtualMouse virtualMouse;
};

int main(int argc, const char **argv) {

    MainClass mainClass;
    mainClass.setup_options(argv[0]);
    mainClass.setup_executor();

    printf("Initializing virtual devices.\n");
    mainClass.create();

    printf("Parsing input.\n");
    mainClass.parse(argc, argv);

    printf("Destroying virtual devices.\n");
    mainClass.destroy();

    exit(EXIT_SUCCESS);
}

