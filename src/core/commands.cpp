#include "commands.h"

//TODO: number of arguments errors checking is not working

long get_uint(vector<string> data) {
    long integer = -1;
    if(data.size() > 2) {
        cout << "!> Invalid number of arguments provided. Expecting 2, got: " << data.size() << endl;
        return false;
    }
    if (data.size() == 2) {
        integer = atol(data[1].c_str());
        if (integer == 0) {
            cout << "!> Invalid argument [" << data[1] << "] in function <set_*>." << endl;
            return -1;
        }
    }

    if (data.size() >= 1) {
        if (data[0].compare("mouse") == 0) {
            cout << "Setting default delay to " << integer << "us." << endl;
            return integer;
        }
    }
    return -1;
}

bool mouse_move(vector<string> data, VirtualMouse &virtualMouse) {
    long x = 0;
    long y = 0;
    long delay = -1;
    if (data.size() == 3) {
        delay = atol(data[2].c_str());
    }
    if (data.size() >= 2) {
        x = atol(data[0].c_str());
        y = atol(data[1].c_str());
        virtualMouse.move((int) x, (int) y, delay);
        cout << "Moving mouse by (" << x << ", " << y << ")." << endl;
        return true;
    } else {
        cout << "!> Invalid number of arguments provided. Expecting 2 or 3, got: " << data.size() << endl;
        return false;
    }
}

bool mouse_reset(vector<string> data, VirtualMouse &virtualMouse) {
    long delay = -1;
    if (data.size() == 1) {
        delay = atol(data[2].c_str());
    } else if (data.size() > 1) {
        cout << "!> Invalid number of arguments provided. Expecting 0 or 1, got: " << data.size() << endl;
        return false;
    }
    virtualMouse.reset_position(delay);
    return true;
}

bool mouse_click(vector<string> data, VirtualMouse &virtualMouse, __uint16_t button) {
    uint count = 1;
    long delay = -1;
    if (data.size() >= 2) {
        delay = atol(data[1].c_str());
    }
    if (data.size() >= 1) {
        count = (uint) atoi(data[0].c_str());
        if (count == 0) {
            cout << "!> Cannot parse [" << data[0] << "] as valid integer." << endl;
            return false;
        }
    }
    for (int i = 0; i < count; ++i) {
        virtualMouse.click(button, delay);
        string btn;
        if (button == BTN_LEFT) btn = "left";
        else if (button == BTN_RIGHT) btn = "right";
        else if (button == BTN_MIDDLE) btn = "middle";
        else btn = "unknown";
        cout << "Performing mouse click with " << btn << " button." << endl;
    }
    return true;
}

bool mouse_scroll(vector<string> data, VirtualMouse &virtualMouse) {
    int amount = 0;
    long delay = -1;
    if (data.size() >= 2) {
        delay = atol(data[1].c_str());
    }
    if (data.size() >= 1) {
        amount = atoi(data[1].c_str());
        if (amount != 0) {
            virtualMouse.scroll(amount, delay);
            cout << "Scrolling by: " << amount << '.' << endl;
            return true;
        }
    }
    return false;
}
