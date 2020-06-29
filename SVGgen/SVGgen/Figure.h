#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#define ResultWidth 1920
#define ResultHeight 980

const int ForbiddenSignsSize = 3;
const char ForbiddenSigns[ForbiddenSignsSize] = {
	'"','\\','~'
};


typedef enum {
	CIRCLE = 1,
	SQUARE,
	RECTANGLE,
	TRIANGLE,
	LINE,
	CARTESIAN,
	FUNCTION_DRAWER
} generateType;

// Przyjrzyj sie setParams w klasie Figure i Circle!!! w twojej tez dodajesz taka metode i musisz powielic naglowek w ten sam sposob co jest teraz w klasie bazowej

class Figure {
public:
	Figure() {};
	virtual std::string generateSvgTag();
	virtual int setParams(std::vector<std::string> params) { return 1; };
	virtual std::vector<std::string> getParams() { return std::vector<std::string>(); };
	std::string tag[2];
	virtual const char* getName() { return "  "; };
	const char* figureName;
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
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Circle";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};

//nowa klasa do dodawania figur(nazwy jak w svg, na tym bazowaæ)
class Squa : public Figure {
public:
	Squa();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Square";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};

class Rect : public Figure {
public:
	Rect();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Rectangle";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};

class Triangle : public Figure {
public:
	Triangle();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Equilateral Triangle";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};

class Line : public Figure {
public:
	Line();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Isosceles Triangle";
	const char* getName() { return figureName; };
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

class FunctionDraw : public Figure {
public:
	FunctionDraw();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Function";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};

class Cartesian : public Figure {
public:
	Cartesian();
	int setParams(std::vector<std::string> params);
	std::vector<std::string> getParams() { return params; };
	std::string generateSvgTag();
	const char* figureName = "Cartesian System";
	const char* getName() { return figureName; };
private:
	std::vector<std::string> params;
};
