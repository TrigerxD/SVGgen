#pragma once
#include <string>

const int ForbiddenSignsSize = 3;
const char ForbiddenSigns[ForbiddenSignsSize] = {
	'"','\\','~'
};

// Przyjrzyj sie setParams w klasie Figure i Circle!!! w twojej tez dodajesz taka metode i musisz powielic naglowek w ten sam sposob co jest teraz w klasie bazowej

class Figure {
public:
	Figure();
	virtual std::string generateSvgTag();
	virtual void setParams(std::string cx, std::string cy, std::string r, std::string color) {};
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
	void setParams(std::string cx, std::string cy, std::string r, std::string color) override;
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