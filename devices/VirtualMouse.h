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

    bool move(int x, int y);
    bool setPosition(int x, int y);
    bool click(__u16 button);
    bool press(__u16 button);
    bool release(__u16 button);

private:
    int xres;
    int yres;

    struct uinput_user_dev userDevice;
};


#endif //AUTOCLICKER_VIRTUALMOUSE_H
