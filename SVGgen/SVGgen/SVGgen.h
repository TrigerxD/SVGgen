#pragma once
#include "Generator.h"
#include "SVGren.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <gdiplus.h>

typedef double(*MYPROC)();
WNDCLASSEX ChildWindow;
HWND hAdd, hGenerate, hShow, hEdit, hErase, hFileName, hDescription, hModules, hGenerateSet, hShowView;
HWND hTextParam1, hParam1, hTextParam2, hParam2, hTextParam3, hParam3, hTextParam4, hParam4, hTextParam5, hParam5;
int figure = 0;
std::vector<mem*> printSVG = {};
int prevPrintSVGSize = 0;

typedef enum Handles {
	ADD = 1,
	GENERATE,
	SHOW,
	FILENAME,
	DESCRIPTION,
	MODULES,
	GENERATING_SET,
	PARAM_1,
	PARAM_2,
	PARAM_3,
	PARAM_4,
	PARAM_5,
	EDIT,
	ERASE,
	DEFAULT
} handles;



class Control {
public:
	Control();
	Control(LPSTR type, LPSTR title, int x, int y, int width, int height);
	void setParams(LPSTR type, LPSTR title, int x, int y, int width, int height, handles name);
	void initialize(HWND window, HINSTANCE instance, int IDC_COMBOBOX_TEXT);
	LPSTR getTitleAddress();
private:
	handles name;
	LPSTR type, title;
	int x, y, width, height;
};

class UI {
public:
	UI();
	UI(HINSTANCE instance, LPSTR className, int width, int height);
	static LRESULT CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK CProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WNDCLASSEX getWindow(bool parent);
	LPSTR getClassName();
	void createView(HINSTANCE instance, LPSTR title);
	Control *getControl(handles handle);
	HWND getView();
	int comboBoxText;
	void stateChaged(generateType state);
	void stateChangedGenerateSet(generateType state, int index);
	void hideControls();
private:
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LPSTR className;
	WNDCLASSEX window, ChildWindow;
	int width, height;
	HWND view; // g³ówne okno widoku
	Control add, generate, show, edit, erase; // uchwyty do guzików
	Control fileName;
	Control description;
	Control modules, set;
	Control param1, param2, param3, param4, param5;
	static UI *me;
};

