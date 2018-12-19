/*
 Usage: see printUsage()
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

void printUsage()
{
	std::cout << "  This utility has three possible usages: \n";
	std::cout << "  For Type A with 10 pole DIP switches \n";
	std::cout << "    Use: sudo ./send <groupCode> <nChannelCode> <command>\n";
	std::cout << "         sGroup        Code of the switch group (refers to DIP switches 1..5 where '1' = on and '0' = off, if all DIP switches\n";
	std::cout << "         nChannelCode  Number of the switch itself (1..4)\n";
	std::cout << "    Example: sudo ./send 01011 3 1\n";
	std::cout << "  \n";
	std::cout << "  For Type B with two rotary/sliding switches \n";
	std::cout << "    Use: sudo ./send <nAddressCode> <nChannelCode> <command>\n";
	std::cout << "         nAddressCode  Number of the switch group (1..4)\n";
	std::cout << "         nChannelCode  Number of the switch itself (1..4)\n";
	std::cout << "    Example: sudo ./send 2 3 1\n";
	std::cout << "  \n";
	std::cout << "  For Type C Intertechno \n";
	std::cout << "    Use: sudo ./send <sFamily> <nGroup> <nDevice> <command>\n";
	std::cout << "         sFamily  Familycode (a..f)\n";
	std::cout << "         nGroup   Number of group (1..4)\n";
	std::cout << "         nDevice  Number of device (1..4)\n";
	std::cout << "    Example: sudo ./send b 3 1 1\n";
	std::cout << "  \n";
	std::cout << "  Command is 0 for OFF and 1 for ON\n";
	std::cout << "  \n";
	std::cout << "  See http://code.google.com/p/rc-switch/wiki/HowTo_OperateLowCostOutlets for more information about supported switches\n";
}

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 3;
	if (wiringPiSetup () == -1) return 1;
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
	
	if(argc == 4)
	{
		char* sGroup = argv[1];
		int nSwitchNumber = atoi(argv[2]);

		int command  = atoi(argv[3]);
		
		if(strlen(sGroup) > 2)
		{
			//Type A: 10 pole DIP switches
			printf("sending [Type A] groupCode[%s] nChannelCode[%i] command[%i]\n", sGroup, nSwitchNumber, command);

			switch(command) {
				case 1:
					mySwitch.switchOn(sGroup, nSwitchNumber);
					break;
				case 0:
					mySwitch.switchOff(sGroup, nSwitchNumber);
					break;
				default:
					printf("command[%i] is unsupported\n", command);
					printUsage();
					return -1;
			}
			return 0;
		} else {
			//Type B: Two rotary/sliding switches
			int nGroupNumber = atoi(sGroup);
			printf("sending [Type B] groupNumber[%i] switchNumber[%i] command[%i]\n", nGroupNumber, nSwitchNumber, command);
			switch(command) {
				case 1:
					mySwitch.switchOn(nGroupNumber, nSwitchNumber);
					break;
				case 0:
					mySwitch.switchOff(nGroupNumber, nSwitchNumber);
					break;
				default:
					printf("command[%i] is unsupported\n", command);
					printUsage();
					return -1;
			}
			return 0;
		}
	}
	else if(argc == 5)
	{
	    //Type C: Intertechno
		char* sFamily = argv[1];
		int nGroup = atoi(argv[2]);
		int nDevice = atoi(argv[3]);
		
		int command = atoi(argv[4]);
    
		printf("sending [Type C] family[%s] groupNumber[%i] switchNumber[%i] command[%i]\n", sFamily, nGroup, nDevice, command);

		switch(command) {
			case 1:
				mySwitch.switchOn(sFamily[0], nGroup, nDevice);
				break;
			case 0:
				mySwitch.switchOff(sFamily[0], nGroup, nDevice);
				break;
			default:
				printf("command[%i] is unsupported\n", command);
				printUsage();
				return -1;
		}
		return 0;
	}
	else
	{
		printUsage();
	}
	return 1;
}
