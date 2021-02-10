#include "cpuctl.hpp"

#include <cstring>
#include <iostream>

int choose_plane(char *plane_arg)
{
    int plane = 0;
    if (!strcmp(plane_arg, "--cpu_core")) {
        plane = CPU_CORE_PLANE;
    } else if (!strcmp(plane_arg, "--cpu_cache")) {
        plane = CPU_CACHE_PLANE;
    } else if (!strcmp(plane_arg, "--igpu")) {
        plane = IGPU_PLANE;
    } else if (!strcmp(plane_arg, "--system_agent")) {
        plane = SYSTEM_AGENT_PLANE;
    } else if (!strcmp(plane_arg, "--analog_io")) {
        plane = ANALOG_IO_PLANE;
    } else if (!strcmp(plane_arg, "--digital_io")) {
        plane = DIGITAL_IO_PLANE;
    } else {
        throw std::runtime_error("Invalid option");
    }
    return plane;
}

int main(int argc, char *argv[])
{
    try {
        if (argc == 2) {
            if (!strcmp(argv[1], "--show")) {
                print_all();
            } else {
                print_offset(choose_plane(argv[1]));
            }
        } else if (argc == 3) {
            if (!strcmp(argv[1], "--config")) {
                set_values_from_config(argv[2]);
            } else {
                int plane = choose_plane(argv[1]);
                int value = std::stoi(argv[2]);
                if (value < -250 || value > 10) {
                    throw std::runtime_error("Do you known what are you doing ?????");
                }

                set_offset(plane, value);
                print_offset(plane);
            }
        }
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
}
