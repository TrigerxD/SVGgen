#pragma once
#include <string>

const int ForbiddenSignsSize = 3;
const char ForbiddenSigns[ForbiddenSignsSize] = {
	'"','\\','~'
};

class Figure {
public:
	Figure();
	virtual std::string generateSvgTag();
	std::string tag[2];
};

class Text {
public:
	Text();
	virtual void setParams(char * text);
	virtual std::string generate();
	std::string tag[2];
	std::string text;
};

class Circle : public Figure {	
public:
	Circle();
	void setParams(std::string cx, std::string cy, std::string r, std::string color);
	std::string generateSvgTag();
private:
	std::string cx;
	std::string cy;
	std::string r;
	std::string fill;
};

class Description : public Text {
public:
	Description();
	void setParams(char * text);
	std::string generateDescription();
};

class Id : public Text {
public:
	Id();
	void setParams(char * text);
	std::string generateDescription();
};