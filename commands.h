
#ifndef AUTOCLICKER_COMMANDS_H
#define AUTOCLICKER_COMMANDS_H

long get_uint(vector<string> data);
bool mouse_move(vector<string> data, VirtualMouse virtualMouse);
bool mouse_click(vector<string> data, VirtualMouse& virtualMouse, __uint16_t button);
bool mouse_scroll(vector<string> data, VirtualMouse& virtualMouse);

#endif