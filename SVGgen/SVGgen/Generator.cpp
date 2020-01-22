#include "Generator.h"

Generator::Generator()
{
	figure = new Circle();
	description = new Description();
	this->file = "";
	this->fileName = "Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
}

void Generator::generate(char* Description)
{	
	this->figure->setParams("100", "100", "50", "red");
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

void Generator::fileSave()
{
	_mkdir("Results/");
	std::ofstream File(this->fileName);
	if (File.is_open()) {
		File << this->file;
	}
	File.close();
}
