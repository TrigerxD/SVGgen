#include "Figure.h"

std::string Figure::generateSvgTag()
{
	return "";
}

Circle::Circle()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("red");
}

int Circle::setParams(std::vector<std::string> params)
{
	if (params.size() != 4)
		return 1;
	this->params = params;
	this->tag[0] = "<circle ";
	this->tag[1] = "/>\n";
	return 0;
}

//<circle r="84" cy="104" cx="108" fill="#ff7f00"/>
std::string Circle::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("cx=\"" + params[0] + "\" ");
	retVal.append("cy=\"" + params[1] + "\" ");
	retVal.append("r=\"" + params[2] + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}

Description::Description()
{
	this->tag[0] = "<description text=\"";
	this->tag[1] = "\"/>";
	this->text = "";
}

void Description::setParams(char * text)
{
	this->text = text;
}

std::string Description::generateDescription()
{
	std::string retVal = "\n";
	retVal.append(this->tag[0]);
	for (int i = 0; i < (this->text).length(); i++) {
		for (int j = 0; j < ForbiddenSignsSize; j++) {
			if(this->text[i] == ForbiddenSigns[j])
				retVal.append("\\");
		}
		retVal += (this->text[i]);
	}
	retVal.append(this->tag[1]);
	return retVal;
}

Text::Text()
{
}

void Text::setParams(char * text)
{
}

std::string Text::generate()
{
	return std::string();
}

