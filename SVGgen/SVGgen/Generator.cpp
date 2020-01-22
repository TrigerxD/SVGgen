#include "Generator.h"

Generator::Generator()
{
	description = new Description();
	this->file = "";
	this->fileName = "Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
}

void Generator::generate(char* Description, generateType state)
{	
	figure = setFigure(state);
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
