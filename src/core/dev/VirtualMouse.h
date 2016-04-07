//
// Created by kamil on 31.03.16.
//

#ifndef AUTOCLICKER_VIRTUALMOUSE_H
#define AUTOCLICKER_VIRTUALMOUSE_H

#include <string.h>

#include "VirtualDevice.h"

class VirtualMouse : public VirtualDevice {
public:
    VirtualMouse(int resX, int resY) : resX(resX), resY(resY) { }

    bool create() override;

    bool destroy() override;

    bool move(int x, int y, long delay = -1);

    bool reset_position(long delay);

    bool click(__u16 button, long delay = -1);

    bool state(__u16 button, __u16 state, long delay = -1);

    bool scroll(int amount, long delay = -1);

private:
    int resX;
    int resY;

    struct uinput_user_dev userDevice;
};


#endif //AUTOCLICKER_VIRTUALMOUSE_H
