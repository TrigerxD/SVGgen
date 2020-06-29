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
		(okno.getControl(GENERATE))->setParams((LPSTR)"BUTTON", (LPSTR)"Generate", 10, 390, 100, 40, GENERATE);
		(okno.getControl(GENERATE))->initialize(okno.getView(), hInstance, okno.comboBoxText);
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
		(okno.getControl(PARAM_5))->setParams((LPSTR)"BUTTON", (LPSTR)"FILL", 10, 210, 230, 20, PARAM_5);
		(okno.getControl(PARAM_5))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_6))->setParams((LPSTR)"EDIT", (LPSTR)"Enter description A here", 250, 50, 360, 100, PARAM_6);
		(okno.getControl(PARAM_6))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_7))->setParams((LPSTR)"EDIT", (LPSTR)"Enter description B here", 250, 160, 360, 100, PARAM_7);
		(okno.getControl(PARAM_7))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(PARAM_8))->setParams((LPSTR)"EDIT", (LPSTR)"Enter description C here", 250, 270, 360, 100, PARAM_8);
		(okno.getControl(PARAM_8))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		

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
		return &add;
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
	case PARAM_6:
		return &param6;
	case PARAM_7:
		return &param7;
	case PARAM_8:
		return &param8;
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
		ShowWindow(hParam5, SW_SHOW);
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
		ShowWindow(hParam5, SW_SHOW);
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
		ShowWindow(hParam7, SW_SHOW);
		break;
	case TRIANGLE:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "A (X,Y)");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "B (X,Y)");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "C (X,Y)");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam5, SW_SHOW);
		ShowWindow(hParam7, SW_SHOW);
		ShowWindow(hParam8, SW_SHOW);
		break;
	case LINE:
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X1");
		ShowWindow(hTextParam1, SW_SHOW);
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y1");
		ShowWindow(hTextParam2, SW_SHOW);
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "X2");
		ShowWindow(hTextParam3, SW_SHOW);
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Y2");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case CARTESIAN:
		SetWindowText(hParam1, "-500,500");
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "rangeX");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, "-500,500");
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "rangeY");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, "960,540");
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "center");
		ShowWindow(hTextParam3, SW_SHOW);
		break;
	case FUNCTION_DRAWER:
		SetWindowText(hParam1, "x");
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "y = ");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, "-500,500");
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "rangeX");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, "-500,500");
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "rangeY");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, "960,540");
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "center");
		ShowWindow(hTextParam4, SW_SHOW);
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
	ShowWindow(hParam7, SW_HIDE);
	ShowWindow(hParam8, SW_HIDE);
	SendMessage(hParam5, BM_SETCHECK, BST_UNCHECKED, 0);
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
		pen = new Gdiplus::Pen(Gdiplus::Color(255, 0, 0, 0), 2);
		graphics->DrawRectangle(pen, Gdiplus::Rect(10, 10, image->GetWidth() / 2, image->GetHeight() / 2));
		graphics->DrawImage(image, Gdiplus::Rect(10, 10, image->GetWidth() / 2, image->GetHeight() / 2));
		delete(graphics);
		delete(pen);
		delete(image);
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
	LPSTR Buffer, Description, p1, p2, p3, p4, p5, p6, p7, p8;
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

			size_alloc = GetWindowTextLength(hParam6);
			p6 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam6, p6, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam7);
			p7 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam7, p7, size_alloc + 1);

			size_alloc = GetWindowTextLength(hParam8);
			p8 = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hParam8, p8, size_alloc + 1);

			std::vector<std::string> params;
			if(IsWindowVisible(hParam1))
				params.push_back(p1);
			if (IsWindowVisible(hParam2))
				params.push_back(p2);
			if (IsWindowVisible(hParam3))
				params.push_back(p3);
			if (IsWindowVisible(hParam4))
				params.push_back(p4);
			//Tu zmiana
			if (IsWindowVisible(hParam5))
			{
				if (checked == BST_UNCHECKED)
				params.push_back("none");
				else
					params.push_back("black");
			}
			if (IsWindowVisible(hParam6))
				params.push_back(p6);

			

			/*if (!generator.tryParams(params)) {
				MessageBox(NULL, "Enter color as color name and rest as numeric (only)!", "Error", 0);
				break;
			}*/
			
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
					params.push_back(p7);											
					mem *tmp = generator.add(Description, RECTANGLE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == TRIANGLE) {
					params.push_back(p7);
					params.push_back(p8);
					mem *tmp = generator.add(Description, TRIANGLE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == LINE) {
					mem *tmp = generator.add(Description, LINE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}
				if (figure == CARTESIAN) {
					mem *tmp = generator.add(Description, CARTESIAN, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}
				if (figure == FUNCTION_DRAWER) {
					mem *tmp = generator.add(Description, FUNCTION_DRAWER, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.push_back(tmp);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

			}
		}
		//Tu zmniana
		else if ((HWND)lParam == hParam5) {
		//obs³uga checkboxa

			if (checked == BST_UNCHECKED)
			{
				SendMessage(hParam5, BM_SETCHECK, BST_CHECKED, 0);	
				checked = BST_CHECKED;

																					//Tutaj ukrywanie dodatkowego opsiu dla kontrolek
				ShowWindow(hParam7, SW_HIDE);
				ShowWindow(hParam8, SW_HIDE);
			}
			else 
			{
				SendMessage(hParam5, BM_SETCHECK, BST_UNCHECKED, 0);
				checked = BST_UNCHECKED;

				if (figure == RECTANGLE || figure == TRIANGLE)
				{
					ShowWindow(hParam7, SW_SHOW);
					if (figure == TRIANGLE)
						ShowWindow(hParam8, SW_SHOW);
				}
				// Tu ustawianie parametru
			}

			 
		}
		else if ((HWND)lParam == hShow) {
			Generator generator = Generator();
			generator.showFile(printSVG);
			dummy();			
			hShowView = CreateWindowEx(WS_EX_WINDOWEDGE, "Child", "Show", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, (ResultWidth+80)/2, (ResultHeight+120)/2, NULL, NULL, GetModuleHandle(NULL), NULL);
			ShowWindow(hShowView, SW_SHOWNORMAL);
			UpdateWindow(hShowView);
		}
		else if ((HWND)lParam == hGenerate) {
			size_alloc = GetWindowTextLength(hFileName);
			Buffer = (LPSTR)GlobalAlloc(GPTR, size_alloc + 1);
			GetWindowText(hFileName, Buffer, size_alloc + 1);
			
			Generator generator = Generator();

			if(generator.appendFileName(Buffer))
				generator.fileSave(printSVG);
			else
				MessageBox(NULL, "ONLY ALPHANUMERIC CHARACTERS ARE ALLOWED IN FILE NAME (start with a-z or A-Z)", "Error", 0);
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
					else if (strcmp(text, "Triangle") == 0) {
						stateChaged(TRIANGLE);
						figure = TRIANGLE;
					}
					else if (strcmp(text, "Line") == 0) {
						stateChaged(LINE);
						figure = LINE;
					}
					else if (strcmp(text, "Cartesian System") == 0) {
						stateChaged(CARTESIAN);
						figure = CARTESIAN;
					}
					else if (strcmp(text, "Function") == 0) {
						stateChaged(FUNCTION_DRAWER);
						figure = FUNCTION_DRAWER;
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
	case GENERATE:
		hGenerate = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case SHOW:
		hShow = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case GENERATING_SET:
		hGenerateSet = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
		break;
	case FILENAME:
		hFileName = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case DESCRIPTION:
		//Tu zmnina WS_VISABLE -> SW_HIDE
		hDescription = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | SW_HIDE | WS_BORDER, x, y, width, height, window, NULL, instance, NULL);
		break;
	case MODULES:
		hModules = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
		SendMessage(hModules, CB_ADDSTRING, 1, (LPARAM)"Circle"); // 1 okno opisu
		SendMessage(hModules, CB_ADDSTRING, 2, (LPARAM)"Square"); // 1 okno opisu
		SendMessage(hModules, CB_ADDSTRING, 3, (LPARAM)"Rectangle"); // 2 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 4, (LPARAM)"Triangle");	// 3 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 5, (LPARAM)"Line"); // 1 okno opisu
		SendMessage(hModules, CB_ADDSTRING, 6, (LPARAM)"Cartesian System"); // 2 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 7, (LPARAM)"Function"); // 1 okno opisu
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
		//Tu zmiana
		hParam5 = CreateWindowEx(WS_EX_STATICEDGE, type, title, BS_RIGHTBUTTON | BS_CHECKBOX | WS_CHILD | WS_BORDER | SW_HIDE, x , y, width, height, window, NULL, instance, NULL);		
		break;
	case PARAM_6:
		hParam6 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case PARAM_7:
		hParam7 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case PARAM_8:
		hParam8 = CreateWindowEx(WS_EX_CLIENTEDGE, type, title, WS_CHILD | WS_BORDER | SW_HIDE, x, y, width, height, window, NULL, instance, NULL);
		break;
	default:
		break;
	}
}

LPSTR Control::getTitleAddress()
{
	return title;
}

