// logLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "logLib.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <filesystem>
#include <fstream>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <vector>

void writeToFile(std::string wString, HANDLE hFile) {

	char DataBuffer[4096];
	strncpy(DataBuffer, wString.c_str(), sizeof(wString));

	// declaring character array 
	//char DataBuffer[] = "This is some test data to write to the file.";
	DWORD dwBytesToWrite = (DWORD)(wString.length());
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		DataBuffer,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);
}

bool logMessage(std::string logMessage, std::string filePath = ""){
	if(filePath.empty()){// if string is empty, log to console
		std::cout << logMessage;
		return TRUE;
	}
	else {// log to specified log file
		//attempt open file in try catch, if fails, try again
		std::cout << "printing to specified file" << std::endl;
		time_t my_time = time(NULL);//timestamp
		char dateString[26];
		ctime_s(dateString, sizeof dateString, &my_time);

		if (!std::experimental::filesystem::exists(filePath)) {//check if file exists
			std::cout << "file not found" << std::endl;
			return FALSE;
		}

		FILE* filepoint;
		errno_t err;
		while (TRUE) { //open log file if available, otherwise, spin and try again
			try {
				/*//fopen method
				fopen_s(&filepoint, filePath.c_str(), "a");
				fputs((dateString + std::string(" - ") + logMessage + "\n").c_str(), filepoint);
				fclose(filepoint);
				*/

				// createfile method

				HANDLE hFile;

				LPCWSTR sw = std::wstring(filePath.begin(), filePath.end()).c_str();
				hFile = CreateFile(sw, FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile == INVALID_HANDLE_VALUE) {
					Sleep(100);
					continue;
				}
				writeToFile(std::string(dateString) + " - ", hFile);
				writeToFile(logMessage + "\n", hFile);

				std::string wString = std::string(dateString) + " - ";
				
				CloseHandle(hFile);
				std::cout << "Logged " + logMessage << std::endl;
				return TRUE;
			}
			catch (...) {
				std::cout << "caught! cannot access file, looping\n";
				Sleep(100);
				continue;
			}
		}
	}
}

std::vector<char> stringToVec(std::string s) {
	std::vector<char> v(s.length());
	std::copy(s.begin(), s.end(), v.begin());

	return v;
}

