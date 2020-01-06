#include "Generator.h"

Generator::Generator()
{
	this->file = "";
	this->fileName = "../../Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
}

void Generator::generate()
{
	this->file.append("<?xml version=\"1.0\" standalone=\"no\"?>\n");
	this->file.append("<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\"\n");
	this->file.append("\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n");
	this->file.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	this->file.append("\t<circle cx=\"100\" cy=\"50\" r=\"40\" stroke=\"black\" stroke-width=\"2\" fill=\"red\" />\n");
	this->file.append("</svg>\n");
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
	std::ofstream File(this->fileName);
	if (File.is_open()) {
		File << this->file;
	}
	File.close();
}
