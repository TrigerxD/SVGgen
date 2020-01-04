#pragma once
#include <iostream>
#include <windows.h>
#include "Generator.h"

typedef enum Handles {
	GENERATE = 1,
	SHOW
} handles;

class Control {
public:
	Control();
	Control(LPSTR type, LPSTR title, int x, int y, int width, int height);
	void setParams(LPSTR type, LPSTR title, int x, int y, int width, int height);
	void initialize(HWND window, HINSTANCE instance);
	HWND getHandle();
	LPSTR getTitleAddress();
private:
	HWND control;
	LPSTR type, title;
	int x, y, width, height;
};

class UI {
public:
	UI();
	UI(HINSTANCE instance, LPSTR className, int width, int height);
	static LRESULT CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WNDCLASSEX getWindow();
	LPSTR getClassName();
	void createView(HINSTANCE instance, LPSTR title);
	Control *getControl(handles handle);
	HWND getView();
private:
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LPSTR className;
	WNDCLASSEX window;
	int width, height;
	HWND view; // g³óne okno widoku
	Control generate, show; // uchwyty do guzików
	static UI *me;
	Generator generator;
};

