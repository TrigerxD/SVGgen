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
//ilo�c paramentr�w kt�ra b�dzie potrzebna
Rect::Rect()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("blue");
}

int Rect::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<rect ";
	this->tag[1] = "/>\n";
	return 0;
}

//<rect x="100" y="100" width="100" height="150" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />
std::string Rect::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("x=\"" + params[0] + "\" ");
	retVal.append("y=\"" + params[1] + "\" ");
	retVal.append("width=\"" + params[2] + "\" ");
	retVal.append("height=\"" + params[3] + "\" ");
	retVal.append("fill=\"" + params[4] + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}

Squa::Squa()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("blue");
}

int Squa::setParams(std::vector<std::string> params)
{
	if (params.size() != 4)
		return 1;
	this->params = params;
	this->tag[0] = "<rect ";
	this->tag[1] = "/>\n";
	return 0;
}

std::string Squa::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("x=\"" + params[0] + "\" ");
	retVal.append("y=\"" + params[1] + "\" ");
	retVal.append("width=\"" + params[2] + "\" ");
	retVal.append("height=\"" + params[2] + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}

Triangle1::Triangle1()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("blue");
}

int Triangle1::setParams(std::vector<std::string> params)
{
	if (params.size() != 4)
		return 1;
	this->params = params;
	this->tag[0] = "<polygon ";
	this->tag[1] = "/>\n";
	return 0;
}

std::string Triangle1::generateSvgTag()
{
	x = stoi(params[0]);
	y = stoi(params[1]);
	a = stoi(params[2]);

	x1 = x + a/2;
	sx1 << x1;

	x2 = a + x;
	y2 = (a*sqrt(3) / 2) + y;
	sx2 << x2;
	sy2 << y2;

	x3 = x;
	sx3 << x3;

	p1 = sx1.str() + "," + params[1];
	p2 = sx2.str() + "," + sy2.str();
	p3 = sx3.str() + "," + sy2.str();

	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("points=\"" + p1 + " " + p2 + " " + p3 + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}

Triangle2::Triangle2()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("blue");
}

int Triangle2::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<polygon ";
	this->tag[1] = "/>\n";
	return 0;
}

std::string Triangle2::generateSvgTag()
{
	x = stoi(params[0]);
	y = stoi(params[1]);
	a = stoi(params[2]);
	h = stoi(params[3]);

	x1 = x + a/2;
	sx1 << x1;

	x2 = x + a;
	y2 = y + h;
	sx2 << x2;
	sy2 << y2;

	x3 = x;
	sx3 << x3;

	p1 = sx1.str() + "," + params[1];
	p2 = sx2.str() + "," + sy2.str();
	p3 = sx3.str() + "," + sy2.str();

	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("points=\"" + p1 + " " + p2 + " " + p3 + "\" ");
	retVal.append("fill=\"" + params[4] + "\" ");
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

