//
// Created by kamil on 31.03.16.
//

#include "VirtualMouse.h"

bool VirtualMouse::create() {
    for (int i = 0; i < sizeof(UINPUT_DIRS); ++i) {
        (fileDescriptor = open(UINPUT_DIRS[i], O_WRONLY));
        if (fileDescriptor > 0) {
            printf("Detected uinput file at: %s.\n", UINPUT_DIRS[i]);
            break;
        }
    }

    if (fileDescriptor < 0) {
        printf("Can't open uinput file descriptor. Do you have uinput module installed?");
        exit(EXIT_FAILURE);
    }

    // Enable mouse buttons events
    tryIoctlOrExit(fileDescriptor, UI_SET_EVBIT, EV_KEY);
    tryIoctlOrExit(fileDescriptor, UI_SET_KEYBIT, BTN_LEFT);
    tryIoctlOrExit(fileDescriptor, UI_SET_KEYBIT, BTN_RIGHT);
    tryIoctlOrExit(fileDescriptor, UI_SET_KEYBIT, BTN_MIDDLE);

    // Enable mouse relative movement
    tryIoctlOrExit(fileDescriptor, UI_SET_EVBIT, EV_REL);
    tryIoctlOrExit(fileDescriptor, UI_SET_RELBIT, REL_X);
    tryIoctlOrExit(fileDescriptor, UI_SET_RELBIT, REL_Y);
    tryIoctlOrExit(fileDescriptor, UI_SET_RELBIT, REL_WHEEL);

    // Enable sync event
    tryIoctlOrExit(fileDescriptor, UI_SET_EVBIT, EV_SYN);

    memset(&userDevice, 0, sizeof(userDevice));
    snprintf(userDevice.name, UINPUT_MAX_NAME_SIZE, "Auto clicker Virtual Mouse");
    userDevice.id.bustype = 0;
    userDevice.id.vendor = 0x1F;
    userDevice.id.product = 0x1E;
    userDevice.id.version = 0;

    tryWriteOrExit(fileDescriptor, &userDevice, sizeof(userDevice));
    tryIoctlOrExit(fileDescriptor, UI_DEV_CREATE, 0);

    sleep(1);

    return fileDescriptor > 0;
}

bool VirtualMouse::destroy() {
    if (fileDescriptor < 0) {
        perror("Cannot destroy uninitialized device.");
        return false;
    }

    sleep(1);

    tryIoctlOrExit(fileDescriptor, UI_DEV_DESTROY, 0);
    tryCloseOrExit(fileDescriptor);
    
    return true;
}

bool VirtualMouse::move(int x, int y, long delay) {
    bool status = true;
    if (x != 0) {
        status = status && sendEvent(EV_REL, REL_X, x, 0);
    }
    if (y != 0 && status) {
        status = status && sendEvent(EV_REL, REL_Y, y, 0);
    }

    if (status) {
        sendEvent(EV_SYN, SYN_REPORT, 0, delay);
    }
    return status;
}

bool VirtualMouse::reset_position(long delay) {
    return move(-resX, -resY, delay);
}

bool VirtualMouse::click(__u16 button, long delay) {
    return sendEvent(EV_KEY, button, 1, 0) &&
           sendEvent(EV_KEY, button, 0, 0) &&
           sendEvent(EV_SYN, SYN_REPORT, 0, delay);
}

bool VirtualMouse::state(__u16 button, __u16 state, long delay) {
    return sendEvent(EV_KEY, button, 1, state) &&
           sendEvent(EV_SYN, SYN_REPORT, 0, delay);
}

bool VirtualMouse::scroll(int amount, long delay) {
    return sendEvent(EV_REL, REL_WHEEL, amount, 0) &&
           sendEvent(EV_SYN, SYN_REPORT, 0, delay);
}
