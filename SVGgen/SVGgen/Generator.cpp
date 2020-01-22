#include "Generator.h"

Generator::Generator()
{
	description = new Description();
	this->file = "";
	this->fileName = "Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
	this->numeric = std::regex("[[:digit:]]*");
	this->alphabet = std::regex("[[:alpha:]]*");
}

void Generator::generate(char* Description, generateType state, char* p1, char* p2, char* p3, char* p4)
{	
	figure = setFigure(state);
	this->figure->setParams(std::string(p1), std::string(p2), std::string(p3), std::string(p4));
	this->description->setParams(Description);
	this->file.append(this->header);
	this->file.append(this->figure->generateSvgTag());
	this->file.append(this->description->generateDescription());
	fileSave();
}

int Generator::appendFileName(char * fileName)
{
	if (std::regex_match(fileName, this->fileNameSample)) {
		this->fileName.append(fileName);
		this->fileName.append(".svg");
		return 1;
	}
	else {
		return 0;
	}
}

int Generator::tryParams(char * p1, char * p2, char * p3, char * p4)
{
	bool test = false;
	test = !std::regex_match(p1, this->numeric);
	test = !std::regex_match(p2, this->numeric);
	test = !std::regex_match(p3, this->numeric);
	test = !std::regex_match(p4, this->alphabet);
	if (test) {
		return 0;
	}
	else {
		return 1;
	}
}

Figure * Generator::setFigure(generateType state)
{
	switch (state) 
	{
	case CIRCLE:
		return new Circle();
	case SQUARE:
	default:
		return new Circle();
	}
}

void Generator::fileSave()
{
	_mkdir("Results/");
	std::ofstream File(this->fileName);
	if (File.is_open()) {
		File << this->file;
	}
	File.close();
}
