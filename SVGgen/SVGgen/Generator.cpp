#include "Generator.h"

Generator::Generator()
{
	this->file = "";
	this->fileName = "";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
}

void Generator::generate()
{

}

int Generator::appendFileName(char * fileName)
{
	if (std::regex_match(fileName, this->fileNameSample)) {
		this->fileName.append(fileName);
		return 1;
	}
	else {
		return 0;
	}
}

void Generator::fileSave()
{
}
