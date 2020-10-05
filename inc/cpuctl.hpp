#ifndef __CPUCTL_HPP__
#define __CPUCTL_HPP__

#include <string>
#include "ioctl.h"

class cpuctl {
    int fd;
public:
    cpuctl();
    ~cpuctl();
    
    offsets get_offsets(int what);
    void set_offsets(const offsets& );
};

void print_offset(int plane);
void print_all();
void set_offset(int plane, int voltage);
void set_values_from_config(const std::string& path);

#endif
