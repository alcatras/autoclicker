#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdexcept>
#include <vector>

#include "dev/VirtualMouse.h"

using namespace std;

class InvalidNumberOfArguments : logic_error {
public:
    InvalidNumberOfArguments(string msg) : logic_error(msg.c_str()) {}
};

pair<string, string> get_property(vector<string> data);

pair<string, int> get_int_property(vector<string> data);

bool mouse_move(vector<string> data, VirtualMouse& virtualMouse);

bool mouse_reset(vector<string> data, VirtualMouse &virtualMouse);

bool mouse_click(vector<string> data, VirtualMouse &virtualMouse, __u16 button);

bool mouse_scroll(vector<string> data, VirtualMouse &virtualMouse);

#endif