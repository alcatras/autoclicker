//
// Created by kamil on 31.03.16.
//

#ifndef AUTOCLICKER_VIRTUALMOUSE_H
#define AUTOCLICKER_VIRTUALMOUSE_H

#include "VirtualDevice.h"

class VirtualMouse : public VirtualDevice {
public:
    VirtualMouse(int xrel, int yrel);

    bool create() override;

    bool destroy() override;

    bool move(int x, int y, long delay = -1);

    bool click(__u16 button, long delay = -1);

    bool press(__u16 button, long delay = -1);

    bool release(__u16 button, long delay = -1);

    bool scroll(int amount, long delay = -1);

private:
    int xres;
    int yres;

    struct uinput_user_dev userDevice;
};


#endif //AUTOCLICKER_VIRTUALMOUSE_H