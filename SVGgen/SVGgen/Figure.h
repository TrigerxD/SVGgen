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