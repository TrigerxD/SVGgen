#include "Generator.h"

Generator::Generator()
{
	//figure = new Circle("100","100","50","red");
	//figure = new Rect("50","50","100", "100", "blue"); //Kwadrat
	//figure = new Rect("50","50","100", "150", "blue"); //Prostok¹t
	//figure = new Line("20", "150", "400", "150", "black"); //Oœ x
	//figure = new Line("20", "20", "20", "150", "black");//Oœ y
	//figure = new Poly("200,10 300,210 100,210", "green"); //trójk¹t
	//figure = new Poly("100,10 40,198 190,78 10,78 160,198", "green"); //gwiazda
	figure = new Poly("100,10 200,10 250,150 50,150", "purple"); //trapez równor
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
