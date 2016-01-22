# Flic SDK for Linux Beta

## Whats included
* daemon - This is the central daemon that manages all buttons. Run it with ./daemon -l -f flic.sqlite3
* fliclib-cpp/flic - This is a command line tool for managing the daemon. Type help to see available commands
* fliclib-cpp/flic.hph - These are the header files for the C++ client library
* fliclib-cpp/libflic.a - This is the C++ client library
* fliclib-cpp/ffi/java/flic.jar - Java bindings for the Flic client library
* fliclib-cpp/ffi/java/libflicjava.so - Flic JNI library. The sample code expects this to be copied to /usr/lib/libflicjava.so
* fliclib-cpp/ffi/python/flic/dist/flic-0.1-py2.7.egg - Python2.7 bindings for the Flic client library. Install with sudo easy_install flic-0.1-py2.7.egg
* fliclib-cpp/ffi/samples/java/Main.java - Sample Java code. Run with java -cp "../../java/flic.jar:." Main
* fliclib-cpp/ffi/samples/java/Makefile - Makefile for the Java sample
* fliclib-cpp/ffi/samples/python/main.py - Sample Python2.7 code. Run with python2 main.py

## Supported platforms
Binaries and libraries has been compiled for x86_64, i386, armv6l and armv7l. All code has been compiled and tested on Ubuntu 15.10 for desktop and Raspbian Jessy.
## Bluetooth controllers
We haven't tested compability with common Bluetooth controllers. The following devices has been tested and confirmed:
* Plugable USB Bluetooth 4.0 Low Energy Micro Adapter

## Requirements
### Bluez
Flic requires the latest bluez HEAD to work well
### Build directives
git clone git://git.kernel.org/pub/scm/bluetooth/bluez.git
cd bluez
./bootstrap
./configure --enable-experimental --enable-library
make
sudo make install

### Running
The easiest way to get started is to run bluetoothd directly from the src folder. Be sure to disable any other bluetoothd service.

cd src
sudo ./bluetoothd -nEd

