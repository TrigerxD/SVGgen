#pragma once
#include <windows.h>
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <direct.h>

#include "Figure.h"



class Generator {
public:
	Generator();
	int generate(char* Description, generateType state, std::vector<std::string> params);
	int appendFileName(char* fileName);
	int tryParams(std::vector<std::string> params);
private:
	Figure * setFigure(generateType state);
	Figure *figure;
	Description * description;
	void fileSave();
	std::string fileName;
	std::string file;
	std::regex fileNameSample, numeric, alphabet;
	std::string header = "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n";
};