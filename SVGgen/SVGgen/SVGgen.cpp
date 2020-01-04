#include "SVGgen.h"

UI * UI::me = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{

	MSG komunikat;
	UI okno = UI(hInstance, (LPSTR)"Klasa Okienka", 640, 480);

	if (RegisterClassEx(&okno.getWindow())) {
		okno.createView(hInstance, (LPSTR)"SVGgen");
		if (okno.getView()) {
			ShowWindow(okno.getView(), nCmdShow);
			UpdateWindow(okno.getView());

			while (GetMessage(&komunikat, NULL, 0, 0)) {
				//Pêtla zdarzeñ
				TranslateMessage(&komunikat);
				DispatchMessage(&komunikat);
			}
		}
	}
	return komunikat.wParam;
}

UI::UI() 
{
	generate = Control();
	show = Control();
	me = this;
}

UI::UI(HINSTANCE instance, LPSTR className, int width, int height) 
{
	UI();
	this->width = width;
	this->height = height;
	this->className = className;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = 0;
	window.lpfnWndProc = Proc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = instance;
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	window.lpszMenuName = NULL;
	window.lpszClassName = className;
	window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

WNDCLASSEX UI::getWindow()
{
	return window;
}

LPSTR UI::getClassName()
{
	return className;
}

void UI::createView(HINSTANCE instance, LPSTR title)
{
	view = CreateWindowEx(WS_EX_WINDOWEDGE, className, title, WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, instance, NULL);
}

HWND UI::getView()
{
	return view;
}

LRESULT CALLBACK UI::Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return me->WndProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK UI::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		if ((HWND)lParam == generate.getHandle()) {
			// generate
		}
		else if ((HWND)lParam == show.getHandle()) {

		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

Control::Control()
{
	type = (LPSTR)"STATIC";
	title = (LPSTR)"default";
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Control::Control(LPSTR type, LPSTR title, int x, int y, int width, int height)
{
	this->title = title;
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Control::setParams(LPSTR type, LPSTR title, int x, int y, int width, int height)
{
	this->title = title;
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Control::initialize(HWND handle, HINSTANCE instance)
{
	control = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, handle, NULL, instance, NULL);
}

HWND Control::getHandle()
{
	return control;
}
