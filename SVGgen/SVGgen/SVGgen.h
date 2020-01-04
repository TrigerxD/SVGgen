#pragma once
#include <iostream>
#include <windows.h>

typedef enum Handles {

} handles;

class Control {
public:
	Control();
	Control(LPSTR type, LPSTR title, int x, int y, int width, int height);
	void setParams(LPSTR type, LPSTR title, int x, int y, int width, int height);
	void initialize(HWND handle, HINSTANCE instance);
	HWND getHandle();
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
	HWND getView();
private:
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LPSTR className;
	WNDCLASSEX window;
	int width, height;
	HWND view; // g³óne okno widoku
	Control generate, show; // uchwyty do guzików
	static UI *me;
};

