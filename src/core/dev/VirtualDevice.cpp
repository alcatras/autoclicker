//
// Created by kamil on 31.03.16.
//

#include "VirtualDevice.h"

void VirtualDevice::tryIoctlOrExit(int __fd, unsigned long int __request) {
    if (ioctl(__fd, __request, NULL) < 0) {
        printf("Error occurred when trying to call ioctl.");
        exit(EXIT_FAILURE);
    }
}

void VirtualDevice::tryIoctlOrExit(int __fd, unsigned long int __request, int extra) {
    if (ioctl(__fd, __request, extra) < 0) {
        perror("Error occurred when trying to call ioctl.");
        exit(EXIT_FAILURE);
    }
}

void VirtualDevice::tryWriteOrExit(int __fd, const void *__buf, size_t __n) {
    if (write(__fd, __buf, __n) < __n) {
        perror("Error occurred when trying to write to file.");
        exit(EXIT_FAILURE);
    }
}

void VirtualDevice::tryCloseOrExit(int __fd) {
    if (close(__fd) < 0) {
        perror("Error occurred when trying to destroy device.");
        exit(EXIT_FAILURE);
    }
}

bool VirtualDevice::sendEvent(__u16 type, __u16 code, __s32 value, long custom_delay) {
    if (fileDescriptor < 0) {
        perror("Cannot send event from uninitialized device.");
        return false;
    }

    usleep(delay);

    memset(&inputEvent, 0, sizeof(struct input_event));
    inputEvent.type = type;
    inputEvent.code = code;
    inputEvent.value = value;

    long bytes = write(fileDescriptor, &inputEvent, sizeof(struct input_event));

    if (bytes < sizeof(struct input_event)) {
        return false;
    }

    if (custom_delay == -1)
        delay = defaultDelay;
    else
        delay = (__useconds_t) custom_delay;
    return true;
}
