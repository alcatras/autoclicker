//
// Created by kamil on 31.03.16.
//

#include <string.h>
#include "VirtualMouse.h"
#include "utils.h"

VirtualMouse::VirtualMouse(int xres, int yres) : xres(xres), yres(yres) {
}

bool VirtualMouse::create() {
    for (int i = 0; i < sizeof(UINPUT_DIRS); ++i) {
        (fileDescriptor = open(UINPUT_DIRS[i], O_WRONLY));
        if (fileDescriptor > 0) {
            break;
        }
    }

    if (fileDescriptor < 0) {
        perror("Can't open uinput descriptor.");
        return false;
    }

    if (!_eioctl(ioctl(fileDescriptor, UI_SET_EVBIT, EV_KEY)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_LEFT)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_RIGHT)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_MIDDLE)))
        return false;

    if (!_eioctl(ioctl(fileDescriptor, UI_SET_EVBIT, EV_REL)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_RELBIT, REL_X)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_RELBIT, REL_Y)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_RELBIT, REL_WHEEL)))
        return false;

    if (!_eioctl(ioctl(fileDescriptor, UI_SET_EVBIT, EV_ABS)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_ABSBIT, ABS_X)))
        return false;
    if (!_eioctl(ioctl(fileDescriptor, UI_SET_ABSBIT, ABS_Y)))
        return false;

    if (!_eioctl(ioctl(fileDescriptor, UI_SET_EVBIT, EV_SYN)))
        return false;

    memset(&userDevice, 0, sizeof(userDevice));
    snprintf(userDevice.name, UINPUT_MAX_NAME_SIZE, "Auto clicker Virtual Mouse");
    userDevice.id.bustype = 0;
    userDevice.id.vendor = 0x1F;
    userDevice.id.product = 0x1E;
    userDevice.id.version = 0;

    userDevice.absmin[ABS_X] = 0;
    userDevice.absmax[ABS_X] = xres - 1;
    userDevice.absmin[ABS_Y] = 0;
    userDevice.absmax[ABS_Y] = yres - 1;

    if (!_ewrite(write(fileDescriptor, &userDevice, sizeof(userDevice)))) {
        return false;
    }
    if (!_eioctl(ioctl(fileDescriptor, UI_DEV_CREATE)))
        return false;

    sleep(2);

    return fileDescriptor > 0;
}

bool VirtualMouse::destroy() {
    if (fileDescriptor < 0) {
        perror("Cannot destroy uninitialized device.");
        return false;
    }

    sleep(2);

    if (!_eioctl(ioctl(fileDescriptor, UI_DEV_DESTROY)))
        return false;

    return _eclose(close(fileDescriptor));
}

bool VirtualMouse::move(int x, int y) {
    bool status = true;
    if (x != 0) {
        status = status && sendEvent(EV_REL, REL_X, x);
    }
    if (y != 0 && status) {
        status = status && sendEvent(EV_REL, REL_Y, y);
    }

    if (status) {
        sendEvent(EV_SYN, SYN_REPORT, 0);
    }
    return status;
}

bool VirtualMouse::click(__u16 button) {
    return sendEvent(EV_KEY, button, 1) &&
           sendEvent(EV_KEY, button, 0) &&
           sendEvent(EV_SYN, SYN_REPORT, 0);
}

bool VirtualMouse::press(__u16 button) {
    return sendEvent(EV_KEY, button, 1) &&
           sendEvent(EV_SYN, SYN_REPORT, 0);
}

bool VirtualMouse::release(__u16 button) {
    return sendEvent(EV_KEY, button, 0) &&
           sendEvent(EV_SYN, SYN_REPORT, 0);
}

bool VirtualMouse::setPosition(int x, int y) {
    x = max(x, 0);
    x = min(x, yres - 1);
    y = max(y, 0);
    y = min(y, yres - 1);

    return sendEvent(EV_ABS, ABS_X, x) &&
           sendEvent(EV_ABS, ABS_Y, y) &&
           sendEvent(EV_SYN, SYN_REPORT, 0);
}
