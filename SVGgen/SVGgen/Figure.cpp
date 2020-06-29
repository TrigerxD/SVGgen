#include "Figure.h"
#include "exprtk.hpp"

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
	this->params.push_back("none");
}

int Circle::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string Circle::generateSvgTag()
{
	int circleX, circleY, circleR;
	std::string retVal = "";

	circleX = stoi(params[0]);
	circleY = stoi(params[1]);
	circleR = stoi(params[2]);


	retVal.append(this->tag[0]);
	retVal.append("id=\"" + params[4] + "\" ");

	retVal.append("d=\"M" + std::to_string(circleX - circleR) + "," + params[1] + " ");
	retVal.append("a " + std::to_string(circleR) + "," + std::to_string(circleR) + " 0 1,0 " + std::to_string(circleR+ circleR) + ",0 ");
	retVal.append("a " + std::to_string(circleR) + "," + std::to_string(circleR) + " 0 1,0 -" + std::to_string(circleR + circleR) + ",0 ");

	retVal.append("M" + std::to_string(circleX - circleR + 1) + "," + params[1] + " ");
	retVal.append("a " + std::to_string(circleR-1) + "," + std::to_string(circleR) + " 0 1,0 " + std::to_string(circleR + circleR-2) + ",0 ");
	retVal.append("a " + std::to_string(circleR-1) + "," + std::to_string(circleR) + " 0 1,0 -" + std::to_string(circleR + circleR-2) + ",0 ");

	retVal.append("\" fill= \"" + params[3]);
	retVal.append(this->tag[1]);
	return retVal;
}
#pragma endregion


#pragma region Rectangle
Rect::Rect()
{
	//Tu zmiana
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("none");
}

int Rect::setParams(std::vector<std::string> params)
{
	if (params.size() !=7)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string Rect::generateSvgTag()
{
	//Tu zmiana
	int rectX, rectY, rectW, rectH, rectWidth, rectHeight;
	std::string retVal = "";

	rectX = stoi(params[0]);
	rectY = stoi(params[1]);
	rectW = stoi(params[2]);
	rectH = stoi(params[3]);

	//obliczenia

	rectWidth = rectX + rectW;
	rectHeight = rectY + rectH;

	//operacje na stringach

	if (params[4] == "black")
	{	

	retVal.append(this->tag[0]);

	retVal.append("id=\"" + params[5] + "\" ");

	//Zewnêtrzna kreska
	retVal.append("d=\"M" + params[0] + " " + params[1] + " ");
	retVal.append("L" + std::to_string(rectWidth) + " " + params[1] + " ");
	retVal.append("L" + std::to_string(rectWidth) + " " + std::to_string(rectHeight) + " ");
	retVal.append("L" + params[0] + " " + std::to_string(rectHeight) + " ");
	retVal.append("L" + params[0] + " " + params[1] + " ");
	//Wewnêtrzna kreska
	retVal.append("M" + std::to_string(rectX + 2) + " " + std::to_string(rectY + 2) + " ");
	retVal.append("L" + std::to_string(rectWidth - 2) + " " + std::to_string(rectY + 2) + " ");
	retVal.append("L" + std::to_string(rectWidth - 2) + " " + std::to_string(rectHeight - 2) + " ");
	retVal.append("L" + std::to_string(rectX + 2) + " " + std::to_string(rectHeight - 2) + " ");
	retVal.append("L" + std::to_string(rectX + 2) + " " + std::to_string(rectY + 2) + " ");

	retVal.append("\" fill= \"" + params[4]);
	retVal.append(this->tag[1]);

	}
	else
	{


	retVal.append(this->tag[0]);

	retVal.append("id=\"" + params[5] + "\" ");

	//Zewnêtrzna górna, pozioma kreska
	retVal.append("d=\"M" + params[0] + " " + params[1] + " ");
	retVal.append("L" + std::to_string(rectWidth) + " " + params[1] + " ");
	//Wewnêtrzna górna, pozioma kreska
	retVal.append("M" + std::to_string(rectX + 2) + " " + std::to_string(rectY + 2) + " ");
	retVal.append("L" + std::to_string(rectWidth - 2) + " " + std::to_string(rectY + 2) + " ");
	//Zewnêtrzna dolna, pozioma kreska
	retVal.append("M" + params[0] + " " + std::to_string(rectHeight) + " ");
	retVal.append("L" + std::to_string(rectWidth) + " " + std::to_string(rectHeight) + " ");
	//Wewnêtrzna dolna, pozioma kreska
	retVal.append("M" + std::to_string(rectX + 2) + " " + std::to_string(rectHeight - 2) + " ");
	retVal.append("L" + std::to_string(rectWidth - 2) + " " + std::to_string(rectHeight - 2) + " ");

	retVal.append("\" fill= \"" + params[4]);
	retVal.append(this->tag[1]);



	retVal.append(this->tag[0]);

	retVal.append("id=\"" + params[6] + "\" ");

	//Zewnêtrzna lewa, pionowa kreska
	retVal.append("d=\"M" + params[0] + " " + params[1] + " ");
	retVal.append("L" + params[0] + " " + std::to_string(rectHeight) + " ");
	//Wewnêtrzna lewa, pionowa kreska
	retVal.append("M" + std::to_string(rectX + 2) + " " + std::to_string(rectY + 2) + " ");
	retVal.append("L" + std::to_string(rectX + 2) + " " + std::to_string(rectHeight - 2) + " ");
	//Zewnêtrzna prawa, pionowa kreska
	retVal.append("M" + std::to_string(rectWidth) + " " + params[1] + " ");
	retVal.append("L" + std::to_string(rectWidth) + " " + std::to_string(rectHeight) + " ");
	//Wewnêtrzna prawa, pionowa kreska
	retVal.append("M" + std::to_string(rectWidth - 2) + " " + std::to_string(rectY + 2) + " ");
	retVal.append("L" + std::to_string(rectWidth - 2) + " " + std::to_string(rectHeight - 2) + " ");

	retVal.append("\" fill= \"" + params[4]);
	retVal.append(this->tag[1]);

	}



	return retVal;
}
#pragma endregion


#pragma region Square
Squa::Squa()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("none");
}

int Squa::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string Squa::generateSvgTag()
{
	int sqareX, sqareY, sqareA, sqareWidth, sqareHeight;

	std::string retVal = "";

	sqareX = stoi(params[0]);
	sqareY = stoi(params[1]);
	sqareA = stoi(params[2]);

	sqareWidth = sqareX + sqareA;
	sqareHeight = sqareY + sqareA;

	retVal.append(this->tag[0]);
	retVal.append("id=\"" + params[4] + "\" ");

	//Zewnêtrzna kreska
	retVal.append("d=\"M" + params[0] + " " + params[1] + " ");
	retVal.append("L" + std::to_string(sqareWidth) + " " + params[1] + " ");
	retVal.append("L" + std::to_string(sqareWidth) + " " + std::to_string(sqareWidth) + " ");
	retVal.append("L" + params[0] + " " + std::to_string(sqareHeight) + " ");
	retVal.append("L" + params[0] + " " + params[1] + " ");
	//Wewnêtrzna kreska
	retVal.append("M" + std::to_string(sqareX + 2) + " " + std::to_string(sqareY + 2) + " ");
	retVal.append("L" + std::to_string(sqareWidth - 2) + " " + std::to_string(sqareY + 2) + " ");
	retVal.append("L" + std::to_string(sqareWidth - 2) + " " + std::to_string(sqareHeight - 2) + " ");
	retVal.append("L" + std::to_string(sqareX + 2) + " " + std::to_string(sqareHeight - 2) + " ");
	retVal.append("L" + std::to_string(sqareX + 2) + " " + std::to_string(sqareY + 2) + " ");

	retVal.append("\" fill= \"" + params[3]);
	retVal.append(this->tag[1]);

	return retVal;
}
#pragma endregion


#pragma region Tringle
Triangle::Triangle()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("none");
}

int Triangle::setParams(std::vector<std::string> params)
{
	if (params.size() != 7)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string Triangle::generateSvgTag()
{
	std::string A = params[0];
	std::string B = params[1];
	std::string C = params[2];
	std::string retVal = "";

	//param0 A(x,y), param1 B(x,y), param2 C(x,y), param3 fill, param4 desc1. param5 desc2, param6 desc3
	int coma = A.find_first_of(',');
	int AX = atoi((A.substr(0, coma)).c_str());
	int AY = atoi((A.substr(coma + 1, A.size() - 1)).c_str());
	coma = B.find_first_of(',');
	int BX = atoi((B.substr(0, coma)).c_str());
	int BY = atoi((B.substr(coma + 1, B.size() - 1)).c_str());
	coma = C.find_first_of(',');
	int CX = atoi((C.substr(0, coma)).c_str());
	int CY = atoi((C.substr(coma + 1, C.size() - 1)).c_str());


	if (params[3] == "black")
	{

		retVal.append(this->tag[0]);
		retVal.append("id=\"" + params[4] + "\" ");

		//Tu obs³uga z wype³nieniem
		retVal.append("d=\"M" + std::to_string(AX) + " " + std::to_string(AY) + " ");
		retVal.append("L" + std::to_string(BX) + " " + std::to_string(BY)+ " ");
		retVal.append("L" + std::to_string(CX) + " " + std::to_string(CY) + " ");
		retVal.append("L" + std::to_string(AX) + " " + std::to_string(AY) + " ");

		retVal.append("\" fill=\"" + params[3] + " ");
		retVal.append(this->tag[1]);
	}
	else
	{
		//A
		retVal.append(this->tag[0]);
		retVal.append("id=\"" + params[4] + "\" ");

		//Tu obs³uga z Lini A(X,Y)
		retVal.append("d=\"M" + std::to_string(AX) + " " + std::to_string(AY) + " ");
		retVal.append("L" + std::to_string(BX) + " " + std::to_string(BY) + " ");


		retVal.append("\" fill=\"" + params[3] + " ");
		retVal.append(this->tag[1]);

		//B
		retVal.append(this->tag[0]);
		retVal.append("id=\"" + params[5] + "\" ");

		//Tu obs³uga z Lini B(X,Y)
		retVal.append("d=\"M" + std::to_string(BX) + " " + std::to_string(BY) + " ");
		retVal.append("L" + std::to_string(CX) + " " + std::to_string(CY) + " ");


		retVal.append("\" fill=\"" + params[3] + " ");
		retVal.append(this->tag[1]);

		//C
		retVal.append(this->tag[0]);
		retVal.append("id=\"" + params[6] + "\" ");

		//Tu obs³uga z Lini C(X,Y)
		retVal.append("d=\"M" + std::to_string(CX) + " " + std::to_string(CY) + " ");
		retVal.append("L" + std::to_string(AX) + " " + std::to_string(AY) + " ");


		retVal.append("\" fill=\"" + params[3] + " ");
		retVal.append(this->tag[1]);

	}



	return retVal;
}
#pragma endregion


#pragma region Line
Line::Line()
{
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("0");
	this->params.push_back("none");
}

int Line::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string Line::generateSvgTag()
{
	int lineX1, lineY1, lineX2, lineY2;

	std::string retVal = "";

	lineX1 = stoi(params[0]);
	lineY1 = stoi(params[1]);
	lineX2 = stoi(params[2]);
	lineY2 = stoi(params[3]);

	retVal.append(this->tag[0]);
	retVal.append("id=\"" + params[4] + "\" ");


	if (lineX1 == lineX2 && lineY1 == lineY2)
	{
		retVal.append("d=\"M" + params[0] + " " + params[1] + " ");
		retVal.append("L" + params[2] + " " + params[3] + " ");
	}


	if (lineX1 < lineX2 && lineY1 == lineY2) //1
	{
		retVal.append("d=\"M" + std::to_string(lineX1) + " " + std::to_string(lineY1 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2) + " " + std::to_string(lineY1 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1) + " " + std::to_string(lineY1 - 1) + " ");
	}

	if (lineX1 < lineX2 && lineY1 < lineY2) //2
	{
		retVal.append("d=\"M" + std::to_string(lineX1+1) + " " + std::to_string(lineY1 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2+1) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2-1) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1-1) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1+1) + " " + std::to_string(lineY1 - 1) + " ");
	}
	if (lineX1 == lineX2 && lineY1 < lineY2) //3
	{
		retVal.append("d=\"M" + std::to_string(lineX1+1) + " " + std::to_string(lineY1) + " ");
		retVal.append("L" + std::to_string(lineX2+1) + " " + std::to_string(lineY2) + " ");
		retVal.append("L" + std::to_string(lineX2-1) + " " + std::to_string(lineY2) + " ");
		retVal.append("L" + std::to_string(lineX1-1) + " " + std::to_string(lineY1) + " ");
		retVal.append("L" + std::to_string(lineX1+1) + " " + std::to_string(lineY1) + " ");
	}
	if (lineX1 > lineX2 && lineY1 < lineY2) //4
	{
		retVal.append("d=\"M" + std::to_string(lineX1+1) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2+1) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2-1) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX1-1) + " " + std::to_string(lineY1 -1) + " ");
		retVal.append("L" + std::to_string(lineX1 + 1) + " " + std::to_string(lineY1 + 1) + " ");
	}
	if (lineX1 > lineX2 && lineY1 == lineY2)//5
	{
		retVal.append("d=\"M" + std::to_string(lineX1) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX1) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX1) + " " + std::to_string(lineY1 + 1) + " ");
	}
	if (lineX1 > lineX2 && lineY1 > lineY2)//6
	{
		retVal.append("d=\"M" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2 - 1) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX2 + 1) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX1 + 1) + " " + std::to_string(lineY1 - 1) + " ");
		retVal.append("L" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1 + 1) + " ");
	}
	if (lineX1 == lineX2 && lineY1 > lineY2)//7
	{
		retVal.append("d=\"M" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1) + " ");
		retVal.append("L" + std::to_string(lineX2 - 1) + " " + std::to_string(lineY2) + " ");
		retVal.append("L" + std::to_string(lineX2 + 1) + " " + std::to_string(lineY2) + " ");
		retVal.append("L" + std::to_string(lineX1 + 1) + " " + std::to_string(lineY1) + " ");
		retVal.append("L" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1) + " ");
	}
	if (lineX1 < lineX2 && lineY1 > lineY2)//8
	{
		retVal.append("d=\"M" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2 - 1) + " " + std::to_string(lineY2 - 1) + " ");
		retVal.append("L" + std::to_string(lineX2 + 1) + " " + std::to_string(lineY2 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1 + 1) + " " + std::to_string(lineY1 + 1) + " ");
		retVal.append("L" + std::to_string(lineX1 - 1) + " " + std::to_string(lineY1 - 1) + " ");
	}



	retVal.append("\" fill= \"none");
	retVal.append(this->tag[1]);

	return retVal;
}
#pragma endregion


#pragma region Rest
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
#pragma endregion


#pragma region Func
FunctionDraw::FunctionDraw() 
{
	this->params.push_back("x");
	this->params.push_back("-1,1");
	this->params.push_back("-1,1");
	this->params.push_back("960,540");
}

int FunctionDraw::setParams(std::vector<std::string> params)
{
	if (params.size() != 5)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" stroke=\"black\" stroke-width=\"1\" />\n";
	return 0;
}

std::string FunctionDraw::generateSvgTag()
{
	std::string retVal = "";
	std::string function = params[0];
	std::string xrange = params[1];
	std::string yrange = params[2];
	std::string center = params[3];

	int coma = xrange.find_first_of(',');
	int xmin = atoi((xrange.substr(0, coma)).c_str());
	int xmax = atoi((xrange.substr(coma + 1, xrange.size() - 1)).c_str());
	coma = yrange.find_first_of(',');
	int ymin = atoi((yrange.substr(0, coma)).c_str());
	int ymax = atoi((yrange.substr(coma + 1, yrange.size() - 1)).c_str());
	coma = center.find_first_of(',');
	int x = atoi((center.substr(0, coma)).c_str());
	int y = atoi((center.substr(coma + 1, center.size() - 1)).c_str());

	std::vector<double> data;
	std::vector<double> results;

	double variable = 0.0;

	exprtk::symbol_table<double> symbol_table;
	symbol_table.add_variable("x", variable);

	exprtk::expression<double> expression;
	expression.register_symbol_table(symbol_table);

	exprtk::parser<double>  parser;
	parser.compile(function, expression);

	for (int i = xmin; i < xmax; i++) {
		variable = (double)i / 100;
		if (expression.value() * 100 <= ResultHeight) {
			data.push_back((double)i / 100);
			results.push_back(expression.value());
		}
	}

	retVal.append(this->tag[0]);
	retVal.append("id=\"" + params[4] + "\" ");

	retVal.append("d=\"M" + std::to_string((int)round(x + data[0] * 100)) + " " + std::to_string((int)round(y - results[0] * 100 + 1)) + " ");
	for (int i = 1; i < results.size(); i++) {
		retVal.append("L" + std::to_string((int)round(x + data[i] * 100)) + " " + std::to_string((int)round(y - results[i] * 100 + 1)) + " ");
	}
	for (int i = results.size() - 1; i > 0; i--) {
		retVal.append("L" + std::to_string((int)round(x + data[i] * 100)) + " " + std::to_string((int)round(y - results[i] * 100 - 1)) + " ");
	}
	retVal.append("L" + std::to_string((int)round(x + data[0] * 100)) + " " + std::to_string((int)round(y - results[0] * 100 - 1)) + " Z");

	retVal.append("\" fill= \"none");

	retVal.append(this->tag[1]);
	return retVal;
}
#pragma endregion


#pragma region Cartesian
Cartesian::Cartesian()
{
	this->params.push_back("-1,1");
	this->params.push_back("-1,1");
	this->params.push_back("960,540");
}

int Cartesian::setParams(std::vector<std::string> params)
{
	if (params.size() != 4)
		return 1;
	this->params = params;
	this->tag[0] = "<path ";
	this->tag[1] = "\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" />\n";
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
	retVal.append("id=\"" + params[3] + "\" ");
	retVal.append("d=\"M" + std::to_string(x + xmin) + " " + std::to_string(y - 1) + " ");
	retVal.append("L" + std::to_string(x + xmin) + " " + std::to_string(y + 1) + " ");
	retVal.append("L" + std::to_string(x + xmax) + " " + std::to_string(y + 1) + " ");
	retVal.append("L" + std::to_string(x + xmax) + " " + std::to_string(y - 1) + " Z");
	retVal.append(this->tag[1]);
	for (int i = 0; i < xmax/100; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("d=\"M" + std::to_string(x + (i + 1) * 100 + 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 - 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 - 1) + " " + std::to_string(y - 20) + " ");
		retVal.append("L" + std::to_string(x + (i + 1) * 100 + 1) + " " + std::to_string(y - 20) + " Z");
		retVal.append(this->tag[1]);
	}
	for (int i = (xmin) / 100; i < 0; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("d=\"M" + std::to_string(x + (i) * 100 + 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 - 1) + " " + std::to_string(y + 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 - 1) + " " + std::to_string(y - 20) + " ");
		retVal.append("L" + std::to_string(x + (i) * 100 + 1) + " " + std::to_string(y - 20) + " Z");
		retVal.append(this->tag[1]);
	}
	retVal.append(this->tag[0]);
	retVal.append("d=\"M" + std::to_string(x + 1) + " " + std::to_string(y + ymin) + " ");
	retVal.append("L" + std::to_string(x - 1) + " " + std::to_string(y + ymin) + " ");
	retVal.append("L" + std::to_string(x - 1) + " " + std::to_string(y + ymax) + " ");
	retVal.append("L" + std::to_string(x + 1) + " " + std::to_string(y + ymax) + " Z");
	retVal.append(this->tag[1]);
	for (int i = 0; i < ymax / 100; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("d=\"M" + std::to_string(x + 20) + " " + std::to_string(y + (i + 1) * 100 + 1) + " ");
		retVal.append("L" + std::to_string(x + 20) + " " + std::to_string(y + (i + 1) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i + 1) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i + 1) * 100 + 1) + " Z");
		retVal.append(this->tag[1]);
	}
	for (int i = (ymin) / 100; i < 0; i++) { // -140, 140 -> 0,140 -> 1,
		retVal.append(this->tag[0]);
		retVal.append("d=\"M" + std::to_string(x + 20) + " " + std::to_string(y + (i) * 100 + 1) + " ");
		retVal.append("L" + std::to_string(x + 20) + " " + std::to_string(y + (i) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i) * 100 - 1) + " ");
		retVal.append("L" + std::to_string(x - 20) + " " + std::to_string(y + (i) * 100 + 1) + " Z");
		retVal.append(this->tag[1]);
	}
	return retVal;
}
#pragma endregion