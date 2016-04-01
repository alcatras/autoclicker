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

static const char *UINPUT_DIRS[] = {"/dev/uinput", "dev/input/uinput", "dev/misc/uinput"};

class VirtualDevice {
public:
    ~VirtualDevice() {
        if (fileDescriptor > 0)
            destroy();
    }

    virtual bool create() = 0;

    virtual bool destroy() { return true; };

protected:
    int fileDescriptor;
    struct input_event inputEvent;

    bool _eioctl(int status);

    bool _ewrite(ssize_t status);

    bool _eclose(int status);

    bool sendEvent(__u16 type, __u16 code, __s32 value);
};


#endif //AUTOCLICKER_VIRTUALDEVICE_H

