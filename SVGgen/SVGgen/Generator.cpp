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

int Generator::generate(char* Description, generateType state, std::vector<std::string> params)
{	
	figure = setFigure(state);
	if (this->figure->setParams(params))
		return 1;
	this->description->setParams(Description);
	this->file.append(this->header);
	this->file.append(this->figure->generateSvgTag());
	this->file.append(this->description->generateDescription());
	fileSave();
	return 0;
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

int Generator::tryParams(std::vector<std::string> params)
{
	bool test = false;
	for (int i = 0; i < params.size() - 1; i++) {
		test |= !std::regex_match(params[i], this->numeric);
	}
	test |= !std::regex_match(params[params.size() - 1], this->alphabet);
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
