# User land application my [kernel module](https://github.com/L0czek/cpuctl_drv)
This repo implements a simple service which sends voltages to set to the kernel module. The settings are obtained from an ini config file. It also provides a simple command line interface.

## Building
```sh
mkdir build
cd build
cmake ..
make
sudo make install
```

## Using
Set the necessary voltages in `/etc/cpuctl/config.ini` and restart `cpuctl` service or run `sudo cpuctl --config <config file>`. To show applied voltages run `sudo cpuctl --show`.
