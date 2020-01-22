#include "Figure.h"

Figure::Figure()
{
}

std::string Figure::generateSvgTag()
{
	return "";
}

#pragma region Circle

Circle::Circle()
{
	this->cx = "0";
	this->cy = "0";
	this->r = "0";
	this->fill = "red";
}

Circle::Circle(std::string cx, std::string cy, std::string r, std::string color)
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
#pragma endregion

#pragma region Rectangle
Rect::Rect()
{
	this->x = "0";
	this->y = "0";
	this->w = "0";
	this->h = "0";
	this->fill = "blue";
}

Rect::Rect(std::string x, std::string y, std::string w, std::string h, std::string color)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->fill = color;
	this->tag[0] = "<rect ";
	this->tag[1] = "/>\n";
}

//<rect x="100" y="100" width="100" height="150" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />
std::string Rect::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("x=\"" + this->x + "\" ");
	retVal.append("y=\"" + this->y + "\" ");
	retVal.append("width=\"" + this->w + "\" ");
	retVal.append("height=\"" + this->h + "\" ");
	retVal.append("fill=\"" + this->fill + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}
#pragma endregion

#pragma region Line
Line::Line()
{
	this->x1 = "0";
	this->y1 = "0";
	this->x2 = "0";
	this->y2 = "0";
	this->stroke = "black";
}

Line::Line(std::string x1, std::string y1, std::string x2, std::string y2, std::string color)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->stroke = color;
	this->tag[0] = "<line ";
	this->tag[1] = "/>\n";
}

//<line x1="0" y1="0" x2="200" y2="200" style="stroke:rgb(255,0,0);stroke-width:2" />
std::string Line::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("x1=\"" + this->x1 + "\" ");
	retVal.append("y1=\"" + this->y1 + "\" ");
	retVal.append("x2=\"" + this->x2 + "\" ");
	retVal.append("y2=\"" + this->y2 + "\" ");
	retVal.append("stroke=\"" + this->stroke + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}
#pragma endregion

#pragma region Polygon
Poly::Poly()
{
	this->p = "0";
	this->fill = "green";
}

Poly::Poly(std::string p, std::string color)
{
	this->p = p;
	this->fill = color;
	this->tag[0] = "<polygon ";
	this->tag[1] = "/>\n";
}

//<polygon points="220,10 300,210 170,250 123,234" style="fill:lime;stroke:purple;stroke-width:1" />
std::string Poly::generateSvgTag()
{
	std::string retVal = "";
	retVal.append("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	retVal.append(this->tag[0]);
	retVal.append("points=\"" + this->p + "\" ");
	retVal.append("fill=\"" + this->fill + "\" ");
	retVal.append(this->tag[1]);
	retVal.append("</svg>");
	return retVal;
}
#pragma endregion

