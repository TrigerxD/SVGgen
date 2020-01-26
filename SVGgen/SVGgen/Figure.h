#pragma once
#include <string>
#include <vector>
#include<sstream>
#include<cmath>

const int ForbiddenSignsSize = 3;
const char ForbiddenSigns[ForbiddenSignsSize] = {
	'"','\\','~'
};

typedef enum {
	CIRCLE = 1,
	SQUARE = 2,
	RECTANGLE = 3,
	TRIANGLE1 = 4,
	TRIANGLE2 = 5
} generateType;

// Przyjrzyj sie setParams w klasie Figure i Circle!!! w twojej tez dodajesz taka metode i musisz powielic naglowek w ten sam sposob co jest teraz w klasie bazowej

class Figure {
public:
	Figure() {};
	virtual std::string generateSvgTag();
	virtual int setParams(std::vector<std::string> params) { return 1; };
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
	int setParams(std::vector<std::string> params);
	std::string generateSvgTag();
private:
	std::vector<std::string> params;
};

//nowa klasa do dodawania figur(nazwy jak w svg, na tym bazowaæ)
class Squa : public Figure {
public:
	Squa();
	int setParams(std::vector<std::string> params);
	std::string generateSvgTag();
private:
	std::vector<std::string> params;
};

class Rect : public Figure {
public:
	Rect();
	int setParams(std::vector<std::string> params);
	std::string generateSvgTag();
private:
	std::vector<std::string> params;
};

class Triangle1 : public Figure {
public:
	Triangle1();
	int setParams(std::vector<std::string> params);
	std::string generateSvgTag();
private:
	std::vector<std::string> params;
	int x, y, a, x1, y1, x2, y2, x3, y3;
	std::string p1, p2, p3;
	std::stringstream sx1, sx2, sy2, sx3, sy3;
};

class Triangle2 : public Figure {
public:
	Triangle2();
	int setParams(std::vector<std::string> params);
	std::string generateSvgTag();
private:
	std::vector<std::string> params;
	int x, y, a, h, x1, y1, x2, y2, x3, y3;
	std::string p1, p2, p3;
	std::stringstream sx1, sy1, sx2, sy2, sx3, sy3;
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