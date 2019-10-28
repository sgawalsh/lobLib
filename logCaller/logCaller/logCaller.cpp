// logCaller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "logLib.h"

int main()
{
	
	std::string passString = "test";
	std::string filePath = "C:/Users/Stephen/Source/Repos/logCaller/log/logFile.txt";
	logMessage(passString, filePath)
}
