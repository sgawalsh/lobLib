// autoTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <string>
#include <fstream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "logLib.h"

static std::string filePath = "C:/Users/Stephen/Source/Repos/logLib/autoTests/autoTestLog/log.txt"; // file for autoTest log, file must exist in advance!
static unsigned int tCount = 10; // Threads created in multi-threading test

int main(int argc, char* argv[]) { int result = Catch::Session().run(argc, argv); return result; }

void clearFile(std::string fileName) {
	std::ofstream ofs;
	ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

TEST_CASE("File not present") {
	REQUIRE(!logMessage("test message", "a file name that does not exist"));
	std::cout << "1 finished!\n";
}

TEST_CASE("File present") {
	REQUIRE(logMessage("test message", filePath));
	clearFile(filePath);
	std::cout << "2 finished!\n";
}

TEST_CASE("Multithreading"){

	/*
	int sTotal = 0;

	std::thread t1(logMessage, "1", filePath);
	std::thread t2(logMessage, "2", filePath);
	std::thread t3(logMessage, "3", filePath);
	std::thread t4(logMessage, "4", filePath);
	std::thread t5(logMessage, "5", filePath);

	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	
	
	
	std::ifstream in;
	std::string s;
	in.open(filePath);

	while (!in.eof()) {
		getline(in, s);
		sTotal++;
	}

	//clearFile(filePath);

	REQUIRE(sTotal == 0);
	*/
	

	std::vector<std::thread> tVec;

	for (unsigned int i = 1; i < tCount + 1; ++i) {
		tVec.push_back(std::move(std::thread(logMessage, std::to_string(i), filePath)));
	}

	std::ofstream ofs;
	ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	for (std::vector<std::thread>::iterator it = tVec.begin(); it != tVec.end(); ++it) {
		it->join();
	}
	int sTotal = 0;

	std::ifstream in;
	std::string s;
	in.open(filePath);

	while (!in.eof()) {
		getline(in, s);
		sTotal++;
	}

	std::cout << sTotal << " - " << tCount;

	REQUIRE(sTotal == tCount * 2 + 1);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

