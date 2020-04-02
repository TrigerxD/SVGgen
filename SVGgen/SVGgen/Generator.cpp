#include "Generator.h"

Generator::Generator()
{
	this->file = "";
	this->fileName = "Results/";
	this->fileNameSample = std::regex("([[:alpha:]])[[:alnum:]]*");
	this->numeric = std::regex("[[:digit:]]*");
	this->alphabet = std::regex("[[:alpha:]]*");
}

mem* Generator::add(char* desc, generateType state, std::vector<std::string> params)
{	
	mem *memo = new mem;
	memo->figure = new Figure();
	memo->description = new Description();
	memo->figure = setFigure(state);
	if (memo->figure->setParams(params))
		return nullptr;
	memo->description->setParams(desc);
	return memo;
}

int Generator::generate(Description *description, Figure * figure)
{
	this->file.append(figure->generateSvgTag());
	//this->file.append(description->generateDescription());
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
		return new Squa();
	case RECTANGLE:
		return new Rect();
	case TRIANGLE1:
		return new Triangle1();
	case TRIANGLE2:
		return new Triangle2();
	case CARTESIAN:
		return new Cartesian();
	case FUNCTION_DRAWER:
		return new FunctionDraw();
	default:
		return new Circle();
	}
}

void Generator::fileSave(std::vector<mem*> svgs) 
{
	this->file.append(this->header);
	this->file.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""+std::to_string(ResultWidth)+"\" height=\"" + std::to_string(ResultHeight) + "\">\n");
	for (int i = 0; i < svgs.size(); i++) {
		if (generate(svgs[i]->description, svgs[i]->figure))
			return;
	}
	this->file.append("</svg>");

	_mkdir("Results/");
	std::ofstream File(this->fileName);
	if (File.is_open()) {
		File << this->file;
	}
	File.close();
}

void Generator::showFile(std::vector<mem*> svgs) {
	this->file.append(this->header);
	this->file.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" + std::to_string(ResultWidth) + "\" height=\"" + std::to_string(ResultHeight) + "\">\n");
	for (int i = 0; i < svgs.size(); i++) {
		if (generate(svgs[i]->description, svgs[i]->figure))
			return;
	}
	this->file.append("</svg>");

	_mkdir("Results/");
	std::ofstream File("Results/dummy.svg");
	if (File.is_open()) {
		File << this->file;
	}
	File.close();
}
