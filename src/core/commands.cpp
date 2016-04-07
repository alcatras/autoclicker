#include "commands.h"

using namespace std;

pair<string, string> get_property(vector<string> data) {
    if(data.size() != 2) {
        throw InvalidNumberOfArguments("Invalid number of arguments provided. Expecting 2, got: " + data.size());
    }

    return pair<string, string>(data[0], data[1]);
}

pair<string, int> get_int_property(vector<string> data) {
    auto pai = get_property(data);
    return pair<string, int>(pai.first, atoi(pai.second.c_str()));
};

bool mouse_move(vector<string> data, VirtualMouse& virtualMouse) {
    if(data.size() < 2 || data.size() > 3) {
        throw InvalidNumberOfArguments("Invalid number of arguments provided. Expecting 2 or 3, got: " + data.size());
    }

    long delay = -1;
    if(data.size() == 3) {
        delay = atol(data[2].c_str());
    }

    auto x = atoi(data[0].c_str());
    auto y = atoi(data[1].c_str());

    if(virtualMouse.move(x, y, delay)) {
        printf("Moving mouse by (%d, %d).\n", x, y);
        return true;
    }
    return false;
}

bool mouse_reset(vector<string> data, VirtualMouse &virtualMouse) {
    if(data.size() > 1) {
        throw InvalidNumberOfArguments("Invalid number of arguments provided. Expecting 0 or 1, got: " + data.size());
    }

    long delay = -1;
    if (data.size() == 1) {
        delay = atol(data[1].c_str());
    }
    if(virtualMouse.reset_position(delay)) {
        printf("Resetting mouse position.\n");
        return true;
    }
    return false;
}

bool mouse_click(vector<string> data, VirtualMouse &virtualMouse, __u16 button) {
    if(data.size() > 2) {
        throw InvalidNumberOfArguments("Invalid number of arguments provided. Expecting 0 or 1, got: " + data.size());
    }

    uint count = 1;
    long delay = -1;
    if(data.size() > 0) {
        count = (uint) atoi(data[0].c_str());
    }
    if(data.size() > 1) {
        delay = atol(data[1].c_str());
    }
    for (int i = 0; i < count; ++i) {
        if(virtualMouse.click(button, delay)) {
            string btn;
            if (button == BTN_LEFT) btn = "left";
            else if (button == BTN_RIGHT) btn = "right";
            else if (button == BTN_MIDDLE) btn = "middle";
            else btn = "unknown";
            printf("Performing mouse click with %s button.\n", btn.c_str());
        } else {
            return false;
        }
    }
    return true;
}

bool mouse_scroll(vector<string> data, VirtualMouse &virtualMouse) {
    if(data.size() == 0 || data.size() > 2) {
        throw InvalidNumberOfArguments("Invalid number of arguments provided. Expecting 1 or 2, got: " + data.size());
    }

    int amount = 0;
    long delay = -1;
    if (data.size() == 2) {
        delay = atol(data[1].c_str());
    }
    if (data.size() > 0) {
        amount = atoi(data[1].c_str());
    }

    if(virtualMouse.scroll(amount, delay)) {
        printf("Scrolling mouse by: %d.\n", amount);
        return true;
    }
    return false;
}