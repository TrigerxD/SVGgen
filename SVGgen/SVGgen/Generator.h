#pragma once
#include <windows.h>
#include <string>
#include <regex>

class Generator {
public:
	Generator();
	void generate();
	int appendFileName(char* fileName);
private:
	void fileSave();
	std::string fileName;
	std::string file;
	std::regex fileNameSample;
};