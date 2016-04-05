#ifndef AUTOCLICKER_COMMANDS_H
#define AUTOCLICKER_COMMANDS_H

#include "dev/VirtualMouse.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

long get_uint(vector<string> data);

bool mouse_move(vector<string> data, VirtualMouse &virtualMouse);

bool mouse_reset(vector<string> data, VirtualMouse &virtualMouse);

bool mouse_click(vector<string> data, VirtualMouse &virtualMouse, __uint16_t button);

bool mouse_scroll(vector<string> data, VirtualMouse &virtualMouse);

#endif