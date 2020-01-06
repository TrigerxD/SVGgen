#include "Generator.h"

Generator::Generator()
{
	figure = new Circle("100","100","50","red");
	this->file = "";
	this->fileName = "Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
}

void Generator::generate()
{
	this->file.append(this->header);
	this->file.append(this->figure->generateSvgTag());
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
