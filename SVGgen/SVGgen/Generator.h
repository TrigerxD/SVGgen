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
	void generate(char* Description, generateType state, char* p1, char* p2, char* p3, char* p4);
	int appendFileName(char* fileName);
	int tryParams(char*p1, char*p2, char*p3, char*p4);
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