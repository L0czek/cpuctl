#ifndef __IOCTL_H__
#define __IOCTL_H__

#include <sys/ioctl.h>

#define CPU_CORE_PLANE 0
#define IGPU_PLANE 1
#define CPU_CACHE_PLANE 2
#define SYSTEM_AGENT_PLANE 3
#define ANALOG_IO_PLANE 4
#define DIGITAL_IO_PLANE 5
#define PLANES 6

#define CPU_CORE 0x01
#define IGPU 0x02
#define CPU_CACHE 0x04
#define SYSTEM_AGENT 0x08
#define ANALOG_IO 0x10
#define DIGITAL_IO 0x20

struct offsets {
    unsigned int what;
    int values[PLANES];
};

#define IOCTL_BASE 'W'
#define CPUCTL_GET_OFFSETS _IOR(IOCTL_BASE, 1, struct offsets)
#define CPUCTL_SET_OFFSETS _IOW(IOCTL_BASE, 2, struct offsets)

#endif
