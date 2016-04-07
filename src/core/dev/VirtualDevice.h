//
// Created by kamil on 31.03.16.
//

#ifndef AUTOCLICKER_VIRTUALDEVICE_H
#define AUTOCLICKER_VIRTUALDEVICE_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/syslog.h>
#include <string.h>

#include "../utils.h"

static const char *UINPUT_DIRS[] = {"/dev/uinput", "dev/input/uinput", "dev/misc/uinput"};

class VirtualDevice {
public:
    VirtualDevice() : defaultDelay(100000), delay(0) { }

    ~VirtualDevice() {
        if (fileDescriptor > 0)
            destroy();
    }

    virtual bool create() = 0;

    virtual bool destroy() { return true; };

    void setDelay(long delay) {
        if (delay > 0)
            defaultDelay = (__useconds_t) delay;
    }

protected:
    int fileDescriptor;
    struct input_event inputEvent;

    __useconds_t defaultDelay;

    void tryIoctlOrExit(int __fd, unsigned long int __request);

    void tryIoctlOrExit(int __fd, unsigned long int __request, int extra);

    void tryWriteOrExit(int __fd, const void *__buf, size_t __n);

    void tryCloseOrExit(int __fd);

    bool sendEvent(__u16 type, __u16 code, __s32 value, long custom_delay = -1);

private:
    __useconds_t delay;
};


#endif //AUTOCLICKER_VIRTUALDEVICE_H

