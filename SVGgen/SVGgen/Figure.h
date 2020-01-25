#pragma once
#include <string>
#include <vector>

const int ForbiddenSignsSize = 3;
const char ForbiddenSigns[ForbiddenSignsSize] = {
	'"','\\','~'
};

typedef enum {
	CIRCLE = 1,
	SQUARE
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