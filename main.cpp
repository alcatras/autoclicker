#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "ArgParser.h"
#include "devices/VirtualMouse.h"
#include "CommandExecutor.h"
#include "utils.h"
#include "commands.h"

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

    void run() {
        commandExecutor.run();
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
                            while (getline(file, line)) {
                                stringstream ss(line);
                                vector<string> _data;
                                string tmp;
                                while(!ss.eof()) {
                                    ss >> tmp;
                                    _data.push_back(tmp);
                                }
                                if (!commandExecutor.parseCommand(_data)) {
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
                "Executes command.",
                "[command1] [arguments1]",
                [&](vector<string> data) -> bool {
                    for (int i = 0; i < data.size(); ++i) {
                        if (!commandExecutor.parseCommand(data)) {
                            cout << "!> Error parsing command: " << data[i] << endl;
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
 *  mouse_left   [count = 1]  [delay = default_delay]
 *  mouse_right  [count = 1]  [delay = default_delay]
 *  mouse_middle [count = 1]  [delay = default_delay]
 *
 *  mouse_move   [x] [y]  [delay = default_delay]
 *  mouse_scroll [amount] [delay = default_delay]
 */
    void setup_executor() {
        commandExecutor.addCommand(
                "set_delay",
                [&](vector<string> data) -> bool {
                    virtualMouse.setDelay(get_uint(data));
                    return true;
                }
        );
        commandExecutor.addCommand(
                "mouse_left",
                [&] (vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_LEFT);
                }
        );
        commandExecutor.addCommand(
                "mouse_right",
                [&] (vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_RIGHT);
                }
        );
        commandExecutor.addCommand(
                "mouse_middle",
                [&] (vector<string> data) -> bool {
                    return mouse_click(data, virtualMouse, BTN_MIDDLE);
                }
        );
        commandExecutor.addCommand(
                "mouse_move",
                [&] (vector<string> data) -> bool {
                    return mouse_move(data, virtualMouse);
                }
        );
        commandExecutor.addCommand(
                "scroll",
                [&] (vector<string> data) -> bool {
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

    cout << "> Parsing input." << endl;
    mainClass.parse(argc, argv);

    cout << "> Initializing virtual devices." << endl;
    mainClass.create();

    mainClass.run();

    cout << "> Destroying virtual devices." << endl;
    mainClass.destroy();

    exit(EXIT_SUCCESS);
}

