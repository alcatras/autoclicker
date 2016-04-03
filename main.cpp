#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "ArgParser.h"
#include "devices/VirtualMouse.h"
#include "CommandExecutor.h"
#include "utils.h"

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
                    argParser.show_help();
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
                            cout << "> Reading file: " << data[i] << endl;
                            while (std::getline(file, line)) {
                                if (!commandExecutor.runCommand(line)) {
                                    cout << "!> Error parsing command: " << line << endl;
                                    exit(EXIT_FAILURE);
                                }
                            }
                            file.close();
                        } else {
                            cout << "!> Cannot open file: " << data[i] << endl;
                            exit(EXIT_FAILURE);
                        }
                    }
                    return true;
                }
        );

        argParser.addOption(
                "c",
                "command",
                "Executes commands.",
                "[command1] [command2] ...",
                [&](vector<string> data) -> bool {
                    for (int i = 0; i < data.size(); ++i) {
                        if (!commandExecutor.runCommand(data[i])) {
                            cout << "!> Error parsing command: " << data[i];
                            exit(EXIT_FAILURE);
                        }
                    }
                    return true;
                }
        );
    }

/*
 * setup commands:
 *  set_delay [device] [default_delay]
 *
 * mouse commands:
 *  mouse_left   [count = 1] [delay = default_delay]
 *  mouse_right  [count = 1] [delay = default_delay]
 *  mouse_middle [count = 1] [delay = default_delay]
 *
 *  mouse_move   [x] [y] [delay = default_delay]
 *  mouse_scroll [amount] [delay = default_delay]
 */

    void setup_executor() {
        commandExecutor.addCommand(
                "set_delay",
                [&](vector<string> data) -> bool {
                    __useconds_t delay;
                    if (data.size() >= 2) {
                        delay = atol(data[1]);
                        if (delay == 0) {
                            cout << "!> Invalid argument [" << data[1] << "] in function <set_delay>.";
                            exit(EXIT_SUCCESS);
                        }
                    }

                    if (data.size() >= 1) {
                        if (data[0].compare("mouse") == 0) {
                            virtualMouse.setDelay(delay);
                            return true;
                        }
                    }
                    return false;
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

    cout << "> Parsing input." << endl;
    mainClass.parse(argc, argv);

    cout << "> Initializing virtual devices." << endl;
    mainClass.create();


    cout << "> Destroying virtual devices." << endl;
    mainClass.destroy();

    exit(EXIT_SUCCESS);
}

