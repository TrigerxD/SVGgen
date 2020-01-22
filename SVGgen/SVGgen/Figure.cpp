#include "Figure.h"

std::string Figure::generateSvgTag()
{
	return "";
}

Circle::Circle()
{
	this->cx = "0";
	this->cy = "0";
	this->r = "0";
	this->fill = "red";
}

void Circle::setParams(std::string cx, std::string cy, std::string r, std::string color)
{
	this->cx = cx;
	this->cy = cy;
	this->r = r;
	this->fill = color;
	this->tag[0] = "<circle ";
	this->tag[1] = "/>\n";
}

//<circle r="84" cy="104" cx="108" stroke-width="5" stroke="#000000" fill="#ff7f00"/>
std::string Circle::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("cx=\"" + this->cx + "\" ");
	retVal.append("cy=\"" + this->cy + "\" ");
	retVal.append("r=\"" + this->r + "\" ");
	retVal.append("fill=\"" + this->fill + "\" ");
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

