# About

rcswitch-pi is for controlling rc remote controlled power sockets 
with the raspberry pi. 

Kudos to the projects 
[rc-switch](http://code.google.com/p/rc-switch),
[wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi)
[r10r/rcswitch-pi] (https://github.com/r10r/rcswitch-pi) for adapting the rc-switch code to use the wiringpi library instead of the library provided by the arduino.

I just adapted the send.cpp and usage message to allow the use with all types of switches (type A, B and Intertechno C)

## Usage

First you have to install the [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) library.
For this, just execute the following commands:
```
git clone git://git.drogon.net/wiringPi
cd wiringPi
git pull origin
./build
```
Then you may install this library.
```
git clone https://github.com/mar1u50/rcswitch-pi
cd rcswitch-pi
```
Open send.cpp and update the variable PIN.
I'm using BCM GPIO pin 22 and in wiring pi this means PIN=3

Compile the example program executing `make`.

Run `sudo ./send` to print the usage.
