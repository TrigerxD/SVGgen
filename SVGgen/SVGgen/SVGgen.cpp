#include "SVGgen.h"
#pragma comment (lib,"Gdiplus.lib")
UI * UI::me = NULL;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
int index2;
int indexIncAfterErase;
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
		(okno.getControl(ERASE))->setParams((LPSTR)"BUTTON", (LPSTR)"Erase", 280, 390, 50, 40, ERASE);
		(okno.getControl(ERASE))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(EDIT))->setParams((LPSTR)"BUTTON", (LPSTR)"Edit", 340, 390, 50, 40, EDIT);
		(okno.getControl(EDIT))->initialize(okno.getView(), hInstance, okno.comboBoxText);
		(okno.getControl(GENERATING_SET))->setParams((LPSTR)"COMBOBOX", (LPSTR)"", 120, 400, 140, 200, GENERATING_SET);
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
		return &add;
	case GENERATE:
		return &generate;
	case SHOW:
		return &show;
	case EDIT:
		return &edit;
	case ERASE:
		return &erase;
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
	ShowWindow(hEdit, SW_HIDE);
	ShowWindow(hErase, SW_HIDE);
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

void UI::stateChangedGenerateSet(generateType state, int index)
{
	ShowWindow(hEdit, SW_SHOW);
	ShowWindow(hErase, SW_SHOW);
	std::string str;
	switch (state)
	{
	case CIRCLE:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "R");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case SQUARE:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case RECTANGLE:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "B");
		ShowWindow(hTextParam4, SW_SHOW);
		SetWindowText(hParam5, printSVG[index]->figure->getParams()[4].c_str());
		ShowWindow(hParam5, SW_SHOW);
		SetWindowText(hTextParam5, "Color");
		ShowWindow(hTextParam5, SW_SHOW);
		break;
	case TRIANGLE1:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "A");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "B");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "C");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "Color");
		ShowWindow(hTextParam4, SW_SHOW);
		break;
	case TRIANGLE2:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "X");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "Y");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "A");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
		ShowWindow(hParam4, SW_SHOW);
		SetWindowText(hTextParam4, "H");
		ShowWindow(hTextParam4, SW_SHOW);
		SetWindowText(hParam5, printSVG[index]->figure->getParams()[4].c_str());
		ShowWindow(hParam5, SW_SHOW);
		SetWindowText(hTextParam5, "Color");
		ShowWindow(hTextParam5, SW_SHOW);
		break;
	case CARTESIAN:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "rangeX");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "rangeY");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "center");
		ShowWindow(hTextParam3, SW_SHOW);
		break;
	case FUNCTION_DRAWER:
		SetWindowText(hParam1, printSVG[index]->figure->getParams()[0].c_str());
		ShowWindow(hParam1, SW_SHOW);
		SetWindowText(hTextParam1, "y = ");
		ShowWindow(hTextParam1, SW_SHOW);
		SetWindowText(hParam2, printSVG[index]->figure->getParams()[1].c_str());
		ShowWindow(hParam2, SW_SHOW);
		SetWindowText(hTextParam2, "rangeX");
		ShowWindow(hTextParam2, SW_SHOW);
		SetWindowText(hParam3, printSVG[index]->figure->getParams()[2].c_str());
		ShowWindow(hParam3, SW_SHOW);
		SetWindowText(hTextParam3, "rangeY");
		ShowWindow(hTextParam3, SW_SHOW);
		SetWindowText(hParam4, printSVG[index]->figure->getParams()[3].c_str());
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
	int size_alloc, len, index, j;
	char text[100];
	LPSTR Buffer, Description, p1, p2, p3, p4, p5;
	HWND hStatic;
	DWORD error;
	HBITMAP bmpSource;
	auto it = printSVG.begin();

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
		else if ((HWND)lParam == hEdit) {
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
			if (IsWindowVisible(hParam1))
				params.push_back(p1);
			if (IsWindowVisible(hParam2))
				params.push_back(p2);
			if (IsWindowVisible(hParam3))
				params.push_back(p3);
			if (IsWindowVisible(hParam4))
				params.push_back(p4);
			if (IsWindowVisible(hParam5))
				params.push_back(p5);

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
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == SQUARE) {
					mem *tmp = generator.add(Description, SQUARE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == RECTANGLE) {
					mem *tmp = generator.add(Description, RECTANGLE, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == TRIANGLE1) {
					mem *tmp = generator.add(Description, TRIANGLE1, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

				if (figure == TRIANGLE2) {
					mem *tmp = generator.add(Description, TRIANGLE2, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}
				if (figure == CARTESIAN) {
					mem *tmp = generator.add(Description, CARTESIAN, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}
				if (figure == FUNCTION_DRAWER) {
					mem *tmp = generator.add(Description, FUNCTION_DRAWER, params);
					if (tmp != nullptr) {
						SetWindowText(hFileName, "OK");
						printSVG.insert(it + index2 + 1, tmp);
						printSVG.erase(printSVG.cbegin() + index2);
					}
					else
						SetWindowText(hFileName, "To low number of parameters");
				}

			}
		}
		else if ((HWND)lParam == hErase) {
			printSVG.erase(printSVG.cbegin() + index2);
			SendMessage(hGenerateSet, CB_DELETESTRING, (WPARAM)index2, (LPARAM)0);
			prevPrintSVGSize = printSVG.size();
			indexIncAfterErase++;
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
					else if (strcmp(text, "Equilateral Triangle") == 0) {
						stateChaged(TRIANGLE1);
						figure = TRIANGLE1;
					}
					else if (strcmp(text, "Isosceles Triangle") == 0) {
						stateChaged(TRIANGLE2);
						figure = TRIANGLE2;
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
		else if ((HWND)lParam == hGenerateSet) {
			for (int i = prevPrintSVGSize; i < printSVG.size(); i++) {
				char buffer[8];
				itoa(i + 1 + indexIncAfterErase, buffer, 10);
				const char* figureName = printSVG[i]->figure->getName();
				char str[80];
				strcpy(str, figureName);
				strcat(str, " ");
				strcat(str, buffer);
				puts(str);
				SendMessage(hGenerateSet, CB_ADDSTRING, i + 1, (LPARAM)(str));
			}
			prevPrintSVGSize = printSVG.size();
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				hideControls();
				index2 = SendMessage((HWND)lParam, CB_GETCURSEL, NULL, NULL);
				if (index2 == CB_ERR)
					break;
				len = (int)SendMessage((HWND)lParam, CB_GETLBTEXTLEN, (WPARAM)index2, NULL);
				if (len == CB_ERR)
					break;
				SendMessageW((HWND)lParam, CB_GETLBTEXT, (WPARAM)index2, (LPARAM)text);
				j = 0;
				for (int i = 0; text[i] != ' '; i += 2, j += 1) {
					text[j] = text[i];
				}
				text[j] = '\0';
				if (strcmp(text, "Circle") == 0) {
					stateChangedGenerateSet(CIRCLE, index2);
					figure = CIRCLE;
				}
				else if (strcmp(text, "Square") == 0) {
					stateChangedGenerateSet(SQUARE, index2);
					figure = SQUARE;
				}
				else if (strcmp(text, "Rectangle") == 0) {
					stateChangedGenerateSet(RECTANGLE, index2);
					figure = RECTANGLE;
				}
				else if (strcmp(text, "Equilateral") == 0) {
					stateChangedGenerateSet(TRIANGLE1, index2);
					figure = TRIANGLE1;
				}
				else if (strcmp(text, "Isosceles") == 0) {
					stateChangedGenerateSet(TRIANGLE2, index2);
					figure = TRIANGLE2;
				}
				else if (strcmp(text, "Cartesian") == 0) {
					stateChangedGenerateSet(CARTESIAN, index2);
					figure = CARTESIAN;
				}
				else if (strcmp(text, "Function") == 0) {
					stateChangedGenerateSet(FUNCTION_DRAWER, index2);
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
	case EDIT:
		hEdit = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case ERASE:
		hErase = CreateWindowEx(0, type, title, WS_CHILD | WS_VISIBLE, x, y, width, height, window, NULL, instance, NULL);
		break;
	case GENERATING_SET:
		hGenerateSet = CreateWindowEx(WS_EX_STATICEDGE, type, title, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, window, (HMENU)IDC_COMBOBOX_TEXT, instance, NULL);
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
		SendMessage(hModules, CB_ADDSTRING, 6, (LPARAM)"Cartesian System"); // 2 okna opisu
		SendMessage(hModules, CB_ADDSTRING, 7, (LPARAM)"Function"); // ??? okna opisu
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

