#pragma once
#include <string>

class Figure {
public:
	Figure();
	virtual std::string generateSvgTag();
	std::string tag[2];
};

class Circle : public Figure {
public:
	Circle();
	Circle(std::string cx, std::string cy, std::string r, std::string color);
	std::string generateSvgTag();
private:
	std::string cx;
	std::string cy;
	std::string r;
	std::string fill;
};


class Rect : public Figure {
public:
	Rect();
	Rect(std::string x, std::string y, std::string w, std::string h, std::string color);
	std::string generateSvgTag();
private:
	std::string x;
	std::string y;
	std::string w;
	std::string h;
	std::string fill;
};

class Line : public Figure {
public:
	Line();
	Line(std::string x1, std::string y1, std::string x2, std::string y2, std::string color);
	std::string generateSvgTag();
private:
	std::string x1;
	std::string y1;
	std::string x2;
	std::string y2;
	std::string stroke;
};

class Poly : public Figure {
public:
	Poly();
	Poly(std::string p, std::string color);
	std::string generateSvgTag();
private:
	std::string p;
	std::string fill;
};