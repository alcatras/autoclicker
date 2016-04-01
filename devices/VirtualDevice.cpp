//
// Created by kamil on 31.03.16.
//

#include <string.h>
#include "VirtualDevice.h"

bool VirtualDevice::_eioctl(int status) {
    if (status < 0) {
        perror("Error occurred when trying to configure ioctl.");
        return false;
    }
    return true;
}

bool VirtualDevice::_ewrite(ssize_t status) {
    if (status < sizeof(struct input_event)) {
        perror("Error occurred when trying to write to file.");
        return false;
    }
    return true;
}

bool VirtualDevice::_eclose(int status) {
    if (status < 0) {
        perror("Error occurred when trying to destroy device.");
        return false;
    }
    return true;
}

bool VirtualDevice::sendEvent(__u16 type, __u16 code, __s32 value) {
    if (fileDescriptor < 0) {
        perror("Can't send event from uninitialized device.");
        return false;
    }

    memset(&inputEvent, 0, sizeof(struct input_event));
    inputEvent.type = type;
    inputEvent.code = code;
    inputEvent.value = value;

    long bytes = write(fileDescriptor, &inputEvent, sizeof(struct input_event));

    if (!_ewrite(bytes)) {
        return false;
    }

    usleep(100000);
    return true;
}
