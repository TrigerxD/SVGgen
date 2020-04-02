#include "Figure.h"

std::string Figure::generateSvgTag()
{
	return "";
}

#pragma region Circle

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
	retVal.append(this->tag[0]);
	retVal.append("cx=\"" + params[0] + "\" ");
	retVal.append("cy=\"" + params[1] + "\" ");
	retVal.append("r=\"" + params[2] + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
	return retVal;
}
//iloœc paramentrów która bêdzie potrzebna
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
	retVal.append(this->tag[0]);
	retVal.append("x=\"" + params[0] + "\" ");
	retVal.append("y=\"" + params[1] + "\" ");
	retVal.append("width=\"" + params[2] + "\" ");
	retVal.append("height=\"" + params[3] + "\" ");
	retVal.append("fill=\"" + params[4] + "\" ");
	retVal.append(this->tag[1]);
	return retVal;
}
#pragma endregion

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
	retVal.append(this->tag[0]);
	retVal.append("x=\"" + params[0] + "\" ");
	retVal.append("y=\"" + params[1] + "\" ");
	retVal.append("width=\"" + params[2] + "\" ");
	retVal.append("height=\"" + params[2] + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
	return retVal;
}
#pragma endregion

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
	retVal.append(this->tag[0]);
	retVal.append("points=\"" + p1 + " " + p2 + " " + p3 + "\" ");
	retVal.append("fill=\"" + params[3] + "\" ");
	retVal.append(this->tag[1]);
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
	retVal.append(this->tag[0]);
	retVal.append("points=\"" + p1 + " " + p2 + " " + p3 + "\" ");
	retVal.append("fill=\"" + params[4] + "\" ");
	retVal.append(this->tag[1]);
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

Cartesian::Cartesian()
{
	this->params.push_back("-1,1");
	this->params.push_back("-1,1");
}

int Cartesian::setParams(std::vector<std::string> params)
{
	if (params.size() != 3)
		return 1;
	this->params = params;
	this->tag[0] = "<path d=\" ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" fill=\"none\"/>\n";
	return 0;
}

std::string Cartesian::generateSvgTag()
{
	std::string retVal = "";
	std::string xrange = params[0];
	std::string yrange = params[1];
	std::string center = params[2];

	int coma = xrange.find_first_of(',');
	int xmin = atoi((xrange.substr(0, coma)).c_str());
	int xmax = atoi((xrange.substr(coma + 1, xrange.size() - 1)).c_str());
	coma = yrange.find_first_of(',');
	int ymin = atoi((yrange.substr(0, coma)).c_str());
	int ymax = atoi((yrange.substr(coma + 1, yrange.size() - 1)).c_str());
	coma = center.find_first_of(',');
	int x = atoi((center.substr(0, coma)).c_str());
	int y = atoi((center.substr(coma + 1, center.size() - 1)).c_str());

	retVal.append(this->tag[0]);
	retVal.append("M" + std::to_string(x + xmin) + " " + std::to_string(y - 1) + " ");
	retVal.append("L" + std::to_string(x + xmin) + " " + std::to_string(y + 1) + " ");
	retVal.append("L" + std::to_string(x + xmax) + " " + std::to_string(y + 1) + " ");
	retVal.append("L" + std::to_string(x + xmax) + " " + std::to_string(y - 1) + " Z");
	retVal.append(this->tag[1]);
	for (int i = 0; i < xmax/100; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("M" + std::to_string(x + (i + 1) * 100 + 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 - 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 - 1) + " " + std::to_string(y - 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 + 1) + " " + std::to_string(y - 20) + " Z");
		retVal.append(this->tag[1]);
	}
	for (int i = (xmin) / 100; i < 0; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("M" + std::to_string(x + (i) * 100 + 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 - 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 - 1) + " " + std::to_string(y - 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 + 1) + " " + std::to_string(y - 20) + " Z");
		retVal.append(this->tag[1]);
	}
	retVal.append(this->tag[0]);
	retVal.append("M" + std::to_string(x + 1) + " " + std::to_string(y + ymin) + " ");
	retVal.append("L" + std::to_string(x - 1) + " " + std::to_string(y + ymin) + " ");
	retVal.append("L" + std::to_string(x - 1) + " " + std::to_string(y + ymax) + " ");
	retVal.append("L" + std::to_string(x + 1) + " " + std::to_string(y + ymax) + " Z");
	retVal.append(this->tag[1]);
	for (int i = 0; i < ymax / 100; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("M" + std::to_string(x + 20) + " " + std::to_string(y + (i + 1) * 100 + 1) + " ");
		retVal.append("L" + std::to_string(x + 20) + " " + std::to_string(y + (i + 1) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i + 1) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i + 1) * 100 + 1) + " Z");
		retVal.append(this->tag[1]);
	}
	for (int i = (ymin) / 100; i < 0; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("M" + std::to_string(x + 20) + " " + std::to_string(y + (i) * 100 + 1) + " ");
		retVal.append("L" + std::to_string(x + 20) + " " + std::to_string(y + (i) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i) * 100 + 1) + " Z");
		retVal.append(this->tag[1]);
	}
	return retVal;
}
