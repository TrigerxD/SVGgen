#pragma once
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <vector>

#include "Figure.h"

typedef struct Mem {
	Figure * figure;
	Description * description;
}mem;

class Generator {
public:
	Generator();
	mem* add(char* Description, generateType state, std::vector<std::string> params);
	int appendFileName(char* fileName);
	void showFile(std::vector<mem*> svgs);
	void fileSave(std::vector<mem*> svgs);
	int tryParams(std::vector<std::string> params);
private:
	Figure * setFigure(generateType state);
	int generate(Description *description, Figure * figure);
	std::string fileName;
	std::string file;
	std::regex fileNameSample, numeric, alphabet;
	std::string header = "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n";
};