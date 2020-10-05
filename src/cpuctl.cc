#include "cpuctl.hpp"

#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

cpuctl::cpuctl() {
    fd = open("/dev/cpuctl", O_RDWR);
    if (fd < 0) 
        throw std::runtime_error("Cannot open /dev/cpuctl");
}

cpuctl::~cpuctl() {
    close(fd);
}


offsets cpuctl::get_offsets(int what) {
    offsets off;
    off.what = what;
    int status = ioctl(fd, CPUCTL_GET_OFFSETS, &off);
    if (status < 0)
        throw std::runtime_error("Cannot get offsets");
    return off;
}

void cpuctl::set_offsets(const offsets& off) {
    int status = ioctl(fd, CPUCTL_SET_OFFSETS, &off);
    if (status < 0)
        throw std::runtime_error("Cannot set offsets");
}

int convert_voltage_to_offset(int mv) {
    return ((int)std::round(mv * 1.024))<<21;
}

double convert_offset_to_voltage(int offset) {
    return (offset >> 21) / 1.024;
}

void print_offset(int plane) {
    cpuctl cpu;
    offsets off = cpu.get_offsets(1ULL << plane);
    std::cout << "Offset: " << convert_offset_to_voltage(off.values[plane]) << "\n";
}

void set_offset(int plane, int voltage) {
    cpuctl cpu;
    offsets off;
    off.what = 1ULL << plane;
    off.values[plane] = convert_voltage_to_offset(voltage);
    cpu.set_offsets(off);
}

const std::unordered_map<std::string, int> options = {
    { "offset.cpu_core", CPU_CORE_PLANE },
    { "offset.cpu_cache", CPU_CACHE_PLANE },
    { "offset.igpu", IGPU_PLANE },
    { "offset.system_agent", SYSTEM_AGENT_PLANE },
    { "offset.digital_io", DIGITAL_IO_PLANE },
    { "offset.analog_io", ANALOG_IO_PLANE }
};

void set_values_from_config(const std::string& path) {
    cpuctl cpu;
    offsets off;
    off.what = 0;
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(path, pt);

    for (const auto & option : options) {
        const auto & [ name, plane ] = option;
        boost::optional<int> value = pt.get_optional<int>(name);
        if (value) {
            off.what |= (1ULL << plane);
            off.values[plane] = convert_voltage_to_offset(*value);
        }
    }
    cpu.set_offsets(off); 
}

void print_all() {
    cpuctl cpu;
    offsets off = cpu.get_offsets(0b111111);
    for (const auto & option : options) {
        const auto & [ name, plane ] = option;
        std::cout << name << std::setw(25 - name.length()) << " => " << convert_offset_to_voltage(off.values[plane]) << "mv\n"; 
    }
}
