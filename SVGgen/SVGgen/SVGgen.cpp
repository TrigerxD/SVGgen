#include "SVGgen.h"

UI * UI::me = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{

	MSG komunikat;
	UI okno = UI(hInstance, (LPSTR)"Klasa Okienka", 640, 480);

	if (RegisterClassEx(&okno.getWindow())) {
		okno.createView(hInstance, (LPSTR)"SVGgen");
		(okno.getControl(GENERATE))->setParams((LPSTR)"BUTTON", (LPSTR)"Generate", 510, 390, 100, 40, GENERATE);
		(okno.getControl(GENERATE))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(FILENAME))->setParams((LPSTR)"EDIT", (LPSTR)"Enter file name", 10, 10, 600, 30, FILENAME);
		(okno.getControl(FILENAME))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(DESCRIPTION))->setParams((LPSTR)"EDIT", (LPSTR)"Enter description here", 250, 50, 360, 330, DESCRIPTION);
		(okno.getControl(DESCRIPTION))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(MODULES))->setParams((LPSTR)"COMBOBOX", (LPSTR)"", 10, 50, 230, 400, MODULES);
		(okno.getControl(MODULES))->initialize(okno.getView(), hInstance, okno.comboBoxText);

		if (okno.getView()) {
			ShowWindow(okno.getView(), nCmdShow);
			UpdateWindow(okno.getView());

			while (GetMessage(&komunikat, NULL, 0, 0)) {
				//P�tla zdarze�
				TranslateMessage(&komunikat);
				DispatchMessage(&komunikat);
			}
		}
	}
	return komunikat.wParam;
}		

UI::UI()
{
	this->generate = Control();
	this->show = Control();
	this->description = Control();
	this->me = this;
	this->comboBoxText = 0;
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

Control * UI::getControl(handles handle)
{
	switch (handle)
	{
	case GENERATE:
		return &generate;
	case SHOW:
		return &show;
	case FILENAME: 
		return &fileName;
	case DESCRIPTION:
		return &description;
	case MODULES:
		return &modules;
	default:
		break;
	}
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
	int size_alloc, len, index;
	char text[100];
	LPSTR Buffer, Description;

	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		if ((HWND)lParam == hGenerate) {
			Generator generator = Generator();
			size_alloc = GetWindowTextLength(hFileName);
			Buffer = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hFileName, Buffer, size_alloc + 1);
			size_alloc = GetWindowTextLength(hDescription);
			Description = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hDescription, Description, size_alloc + 1);
			if (generator.appendFileName((char*)Buffer)) {
				SetWindowText(hFileName, "OK");
				generator.generate(Description);
			}
			else
				MessageBox(NULL, "ONLY ALPHANUMERIC CHARACTERS ARE ALLOWED IN FILE NAME (start with a-z or A-Z)","Error",0);
		}
		else if ((HWND)lParam == hShow) {
			//podglad
		}
		else if ((HWND)lParam == hModules) {
			switch (HIWORD(wParam))
			{
				case CBN_SELCHANGE:
					index = SendMessage((HWND)lParam, CB_GETCURSEL, NULL, NULL);
					if (index == CB_ERR)
						break;
					len = (int)SendMessage((HWND)lParam, CB_GETLBTEXTLEN, (WPARAM)index, NULL);
					if (len == CB_ERR)
						break;
					SendMessageW((HWND)lParam, CB_GETLBTEXT, (WPARAM)index, (LPARAM)text);
					break;
				default:
					break;
			}
		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

Control::Control()
{
	name = DEFAULT;
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

void Control::setParams(LPSTR type, LPSTR title, int x, int y, int width, int height, handles name)
{
	this->name = name;
	this->title = title;
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Control::initialize(HWND window, HINSTANCE instance, int IDC_COMBOBOX_TEXT)
{
	switch (name) {
	case GENERATE:
		hGenerate = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case SHOW:
		hShow = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case FILENAME:
		hFileName = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case DESCRIPTION:
		hDescription = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case MODULES:
		hModules = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
		SendMessage(hModules, CB_ADDSTRING, 0, (LPARAM)"Item 1");
		SendMessage(hModules, CB_ADDSTRING, 0, (LPARAM)"Item 2");
		SendMessage(hModules, CB_ADDSTRING, 0, (LPARAM)"Item 3");
		break;
	default:
		break;
	}
}

LPSTR Control::getTitleAddress()
{
	return title;
}

