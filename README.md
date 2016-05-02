# Flic SDK for Linux Beta

## UPDATE

First of all we at Shortcut Labs wants to thank all of you beta testers. Your feedback has made us realize that Bluez might not be ready to support Flic. The features we need in bluez are marked as experimental and there is a reason for that. This is the reason this repository hasn't seen any new releases in a while.

However, we have been working on a new solution that's now ready to be released as a beta. We really believe that this new SDK will work much better, and we hope that you will try it out. The new SDK uses HCI instead of Bluez, and we have worked hard to reduce the number of dependencies. This means that we will support more platforms.

The link to the new SDK will come here very soon.

Cheers, Fabian from Shortcut Labs

## Discussion (not code related)
https://community.flic.io/topic/10/flic-for-pi3

## Issues
Please check out the issues tab here on GitHub

## Download

The library is distributed as a tarball and can be found under https://github.com/50ButtonsEach/fliclib-linux-dist/releases

## Whats included
The release tarball include both library files and documentation for the Flic client library
* `daemon` - This is the central daemon that manages all buttons. Run it with `./daemon -l -f flic.sqlite3`
* `fliclib-cpp/doc` - HTML documentation for the C++ client library
* `fliclib-cpp/flic` - This is a command line tool for managing the daemon. Type help to see available commands
* `fliclib-cpp/flic.hpp` - These are the header files for the C++ client library
* `fliclib-cpp/libflic.a` - This is the C++ client library
* `fliclib-cpp/ffi/java/doc` - HTML documentation for the Java bindings for the Flic client library
* `fliclib-cpp/ffi/java/flic.jar` - Java bindings for the Flic client library
* `fliclib-cpp/ffi/java/libflicjava.so` - Flic JNI library. The sample code expects this to be copied to `/usr/lib/libflicjava.so`
* `fliclib-cpp/ffi/python/doc` - HTML documentation for the Python2.7 bindings for the Flic client library
* `fliclib-cpp/ffi/python/flic/dist/flic-0.1-py2.7.egg` - Python2.7 bindings for the Flic client library. Install with `sudo easy_install flic-0.1-py2.7.egg`

## Supported platforms
Binaries and libraries has been compiled for `x86_64`, `i386` and `armv6l`. All code has been compiled and tested on Ubuntu 15.10 for desktop and Raspbian Jessy. This means it should be compatible with desktop systems and both raspberrypi 1 & 2. I have tried to make the binaries as portable as possible.
## Bluetooth controllers
We haven't tested compability with all common Bluetooth controllers. The following devices has been tested and confirmed:
* Plugable USB Bluetooth 4.0 Low Energy Micro Adapter
* Broadcom BCM20702 Bluetooth 4.0
* Raspberry pi 3 model B

## Requirements
### Packages
The following libraries should be installed on your system:
```
libglib2.0-0
libglib2.0-dev
libdbus-1-dev
libudev-dev
automake
libtool

install with: sudo apt-get install or similar
```
### Bluez
Flic requires a more recent version of Bluez than most distros provide. Users has reported problems with 5.38+, but 5.37 seems to work good.
### Building
```
git clone git://git.kernel.org/pub/scm/bluetooth/bluez.git

cd bluez

git checkout 5.37

./bootstrap

./configure --enable-experimental --enable-library

make

sudo make install
```

### Running
The easiest way to get started is to run bluetoothd directly from the src folder. Be sure to disable any other bluetoothd service.

```
cd src
sudo ./bluetoothd -nEd
```
When running bluez from your distro, you may need to add the experimental flag via `systemctl edit bluetooth`:
```
[Service]
ExecStart=
ExecStart=/usr/lib/bluetooth/bluetoothd -E
```
## Example
In one terminal run `sudo ./bluetoothd -nEd` or `systemctl start bluetooth`

In another terminal run `./daemon -l -f flic.sqlite3`

In a third terminal run `./flic`

In the third terminal enter the command `startScan`. Now press your Flic button and wait for it to appear. When it does, enter the command `stopScan`. Hold your Flic button for 8 seconds to make it public, and make sure that it glows red. Then enter the command `connect <MAC>` where MAC is the address that appeared during scan. The button should now connect and you will see click events appear.

## Samples
### C++
Compile with
```
CXXFLAGS="-I../../../fliclib-cpp/" LDFLAGS="-L../../../fliclib-cpp/"  make
```
Modify CXXFLAGS and LDFLAGS according to where fliclib-cpp is located.

Run with
```
./main
```

### Java
Compile with
```
CLASSPATH="../../../fliclib-cpp/ffi/java/flic.jar:." make
```
Modify CLASSPATH according to where fliclib-cpp is located

Run with
```
CLASSPATH="../../../fliclib-cpp/ffi/java/flic.jar:." java Main
```
### Python (2.7)
Run with ```python2.7 main.py```

## Troubleshooting
If you get the error message "D-Bus setup failed: Name already in use" when starting bluetoothd you can try "ps aux | grep blue" and then "sudo kill " for the appropriate process.

Your bluetooth controller may be down for various reasons. Verify that it's up with ```hciconfig```, and if needed bring it up with ```sudo hciconfig hci0 up```

If you get the error message `Failed to start scan: GDBus.Error:org.bluez.Error.NotReady: Resource Not Ready, 36`, make sure to power on your bluetooth adapter via `bluetoothctl`, `power on`
