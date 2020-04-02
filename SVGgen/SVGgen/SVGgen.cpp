#include "SVGgen.h"
#pragma comment (lib,"Gdiplus.lib")
UI * UI::me = NULL;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
// Initialize GDI+.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	MSG komunikat;
	UI okno = UI(hInstance, (LPSTR)"Klasa Okienka", 640, 480);
	if (RegisterClassEx(&okno.getWindow(true)) && RegisterClassEx(&okno.getWindow(false))) {
		okno.createView(hInstance, (LPSTR)"SVGgen");
		(okno.getControl(ADD))->setParams((LPSTR)"BUTTON", (LPSTR)"Add", 510, 390, 100, 40, ADD);
		(okno.getControl(ADD))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(SHOW))->setParams((LPSTR)"BUTTON", (LPSTR)"Show", 400, 390, 100, 40, SHOW);
		(okno.getControl(SHOW))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(GENERATING_SET))->setParams((LPSTR)"COMBOBOX", (LPSTR)"", 290, 400, 100, 40, GENERATING_SET);
		(okno.getControl(GENERATING_SET))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(FILENAME))->setParams((LPSTR)"EDIT", (LPSTR)"Enter file name", 10, 10, 600, 30, FILENAME);
		(okno.getControl(FILENAME))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(DESCRIPTION))->setParams((LPSTR)"EDIT", (LPSTR)"Enter description here", 250, 50, 360, 330, DESCRIPTION);
		(okno.getControl(DESCRIPTION))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(MODULES))->setParams((LPSTR)"COMBOBOX", (LPSTR)"", 10, 50, 230, 200, MODULES);
		(okno.getControl(MODULES))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_1))->setParams((LPSTR)"EDIT", (LPSTR)"", 70, 90, 170, 20, PARAM_1);
		(okno.getControl(PARAM_1))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_2))->setParams((LPSTR)"EDIT", (LPSTR)"", 70, 120, 170, 20, PARAM_2);
		(okno.getControl(PARAM_2))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_3))->setParams((LPSTR)"EDIT", (LPSTR)"", 70, 150, 170, 20, PARAM_3);
		(okno.getControl(PARAM_3))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_4))->setParams((LPSTR)"EDIT", (LPSTR)"", 70, 180, 170, 20, PARAM_4);
		(okno.getControl(PARAM_4))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_5))->setParams((LPSTR)"EDIT", (LPSTR)"", 70, 210, 170, 20, PARAM_5);
		(okno.getControl(PARAM_5))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		
		

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
	this->generate = Control();
	this->show = Control();
	this->description = Control();
	this->comboBoxText = 0;
	this->me = this;
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

	ChildWindow.cbSize = sizeof(WNDCLASSEX);
	ChildWindow.style = 0;
	ChildWindow.lpfnWndProc = CProc;
	ChildWindow.cbClsExtra = 0;
	ChildWindow.cbWndExtra = 0;
	ChildWindow.hInstance = instance;
	ChildWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	ChildWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	ChildWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ChildWindow.lpszMenuName = NULL;
	ChildWindow.lpszClassName = "Child";
	ChildWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

WNDCLASSEX UI::getWindow(bool parent)
{
	if (parent)
		return window;
	else
		return ChildWindow;
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
	case ADD:
		return &generate;
	case SHOW:
		return &show;
	case FILENAME:
		return &fileName;
	case DESCRIPTION:
		return &description;
	case MODULES:
		return &modules;
	case GENERATING_SET:
		return &set;
	case PARAM_1:
		return &param1;
	case PARAM_2:
		return &param2;
	case PARAM_3:
		return &param3;
	case PARAM_4:
		return &param4;
	case PARAM_5:
		return &param5;
	default:
		break;
	}
}

HWND UI::getView()
{
	return view;
}

//Wyœwietlanie kontrolek
void UI::stateChaged(generateType state)
{
	switch (state)
	{
	case CIRCLE:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "R");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case SQUARE:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case RECTANGLE:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "B");
		ShowWindow(hTextParam4, SW_SHOW);
		ShowWindow(hParam5, SW_SHOW);
		SetWindowText(hTextParam5, "Color");
		ShowWindow(hTextParam5, SW_SHOW);
		break;
	case TRIANGLE1:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "A");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "B");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "C");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case TRIANGLE2:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "H");
		ShowWindow(hTextParam4, SW_SHOW);
		ShowWindow(hParam5, SW_SHOW);
		SetWindowText(hTextParam5, "Color");
		ShowWindow(hTextParam5, SW_SHOW);
		break;
	default:
		break;
	}
}

void UI::hideControls()
{
	ShowWindow(hParam1, SW_HIDE);
	ShowWindow(hTextParam1, SW_HIDE);
	ShowWindow(hParam2, SW_HIDE);
	ShowWindow(hTextParam2, SW_HIDE);
	ShowWindow(hParam3, SW_HIDE);
	ShowWindow(hTextParam3, SW_HIDE);
	ShowWindow(hParam4, SW_HIDE);
	ShowWindow(hTextParam4, SW_HIDE);
	ShowWindow(hParam5, SW_HIDE);
	ShowWindow(hTextParam5, SW_HIDE);
}

LRESULT CALLBACK UI::Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return me->WndProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK UI::CProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return me->ChildProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK UI::ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	Gdiplus::Graphics *graphics;
	Gdiplus::Image *image;
	Gdiplus::Pen *pen;
	Gdiplus::Rect *destRect;
	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		remove("Results/dummy.svg");
		remove("Results/dummy.png");
		DestroyWindow(hwnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		graphics = new Gdiplus::Graphics(hdc);
		image = Gdiplus::Image::FromFile(L"Results/dummy.png");
		pen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0, 0), 2);
		destRect = new Gdiplus::Rect(0, 0, 1920, 1080);
		graphics->DrawImage(image, 0, 0);
		delete(graphics);
		delete(pen);
		delete(destRect);
		EndPaint(hwnd, &ps);
		break;
		
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
}
	return 0;
}

LRESULT CALLBACK UI::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int size_alloc, len, index,j;
	char text[100];
	LPSTR Buffer, Description, p1, p2, p3, p4, p5;
	HWND hStatic;
	DWORD error;
	HBITMAP bmpSource;

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
	//pobieranie wartoœci z parametrów
	case WM_COMMAND:
		if ((HWND)lParam == hAdd) {
			Generator generator = Generator();
			size_alloc = GetWindowTextLength(hFileName);
			Buffer = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hFileName, Buffer, size_alloc + 1);

			size_alloc = GetWindowTextLength(hDescription);
			Description = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hDescription, Description, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam1);
			p1 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam1, p1, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam2);
			p2 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam2, p2, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam3);
			p3 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam3, p3, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam4);
			p4 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam4, p4, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam5);
			p5 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam5, p5, size_alloc + 1);

			std::vector<std::string> params;
			if(IsWindowVisible(hParam1))
				params.push_back(p1);
			if (IsWindowVisible(hParam2))
				params.push_back(p2);
			if (IsWindowVisible(hParam3))
				params.push_back(p3);
			if (IsWindowVisible(hParam4))
				params.push_back(p4);
			if (IsWindowVisible(hParam5))
				params.push_back(p5);

			if (!generator.tryParams(params)) {
				MessageBox(NULL, "Enter color as color name and rest as numeric (only)!", "Error", 0);
				break;
			}
			if (1) 
			{
				if (figure == CIRCLE) {
					mem *tmp = generator.add(Description, CIRCLE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == SQUARE) {
					mem *tmp = generator.add(Description, SQUARE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == RECTANGLE) {
					mem *tmp = generator.add(Description, RECTANGLE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == TRIANGLE1) {
					mem *tmp = generator.add(Description, TRIANGLE1, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == TRIANGLE2) {
					mem *tmp = generator.add(Description, TRIANGLE2, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

			}
			else
				MessageBox(NULL, "ONLY ALPHANUMERIC CHARACTERS ARE ALLOWED IN FILE NAME (start with a-z or A-Z)","Error",0);
		}
		else if ((HWND)lParam == hShow) {
			Generator generator = Generator();
			generator.showFile(printSVG);
			dummy();			
			hShowView = CreateWindowEx(WS_EX_WINDOWEDGE, "Child", "Show", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1930, 1090, NULL, NULL, GetModuleHandle(NULL), NULL);
			ShowWindow(hShowView, SW_SHOWNORMAL);
			UpdateWindow(hShowView);
		}
		else if ((HWND)lParam == hModules) {
			switch (HIWORD(wParam))
			{
				case CBN_SELCHANGE:
					hideControls();
					index = SendMessage((HWND)lParam, CB_GETCURSEL, NULL, NULL);
					if (index == CB_ERR)
						break;
					len = (int)SendMessage((HWND)lParam, CB_GETLBTEXTLEN, (WPARAM)index, NULL);
					if (len == CB_ERR)
						break;
					SendMessageW((HWND)lParam, CB_GETLBTEXT, (WPARAM)index, (LPARAM)text);
					j = 0;
					for (int i = 0; text[i] != '\0'; i += 2, j+= 1) {
						text[j] = text[i];
					}
					text[j] = '\0';
					if (strcmp(text, "Circle") == 0) {
						stateChaged(CIRCLE);
						figure = CIRCLE;
					}
					else if (strcmp(text, "Square") == 0) {
						stateChaged(SQUARE);
						figure = SQUARE;
					}
					else if (strcmp(text, "Rectangle") == 0) {
						stateChaged(RECTANGLE);
						figure = RECTANGLE;
					}
					else if (strcmp(text, "Equilateral Triangle") == 0) {
						stateChaged(TRIANGLE1);
						figure = TRIANGLE1;
					}
					else if (strcmp(text, "Isosceles Triangle") == 0) {
						stateChaged(TRIANGLE2);
						figure = TRIANGLE2;
					}
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
	case ADD:
		hAdd = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case SHOW:
		hShow = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case GENERATING_SET:
		hGenerateSet = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
		SendMessage(hModules, CB_ADDSTRING, 1, (LPARAM)"Circle"); // 1 okno opisu
		break;
	case FILENAME:
		hFileName = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case DESCRIPTION:
		hDescription = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case MODULES:
		hModules = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
		SendMessage(hModules, CB_ADDSTRING, 1, (LPARAM)"Circle"); // 1 okno opisu
		SendMessage(hModules, CB_ADDSTRING, 2, (LPARAM)"Square"); // 1 okno opisu
		SendMessage(hModules, CB_ADDSTRING, 3, (LPARAM)"Rectangle"); // 2 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 4, (LPARAM)"Triangle");	// 3 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 5, (LPARAM)"Line"); // 1 okno opisu
		break;
	case PARAM_1:
		hParam1 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		hTextParam1 = CreateWindowEx(0, "STATIC", "X: ", WS_CHILD | WS_BORDER | SW_HIDE, x - 60, y, 50, 20, window, NULL, instance, NULL);
		break;
	case PARAM_2:
		hParam2 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		hTextParam2 = CreateWindowEx(0, "STATIC", "Y: ", WS_CHILD | WS_BORDER | SW_HIDE, x - 60, y, 50, 20, window, NULL, instance, NULL);
		break;
	case PARAM_3:
		hParam3 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		hTextParam3 = CreateWindowEx(0, "STATIC", "R: ", WS_CHILD | WS_BORDER | SW_HIDE, x - 60, y, 50, 20, window, NULL, instance, NULL);
		break;
	case PARAM_4:
		hParam4 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		hTextParam4 = CreateWindowEx(0, "STATIC", "G: ", WS_CHILD | WS_BORDER | SW_HIDE, x - 60, y, 50, 20, window, NULL, instance, NULL);
		break;
	case PARAM_5:
		hParam5 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		hTextParam5 = CreateWindowEx(0, "STATIC", "Color: ", WS_CHILD | WS_BORDER | SW_HIDE, x - 60, y, 50, 20, window, NULL, instance, NULL);
		break;
	default:
		break;
	}
}

LPSTR Control::getTitleAddress()
{
	return title;
}

