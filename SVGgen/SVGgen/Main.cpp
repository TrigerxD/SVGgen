#include "Logic.h"

/**
* Przedmiot : Jêzyki asemblerowe
* Autor : Jaros³aw Bobek
* Sekcja : 8
* Semestr : 5
* Rok : 3 (2017)
* Prowadz¹cy : Oleg Antemijczuk
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Potrzebne uchwyty do okna
HWND global_Time, global_lTime, global_lButton, global_p1Button, global_p2Button, global_m1Button, global_m2Button, global_asmButton, global_cppButton, global_wTextBox, global_aText, global_bText, global_dText, global_tText, global_wStatic, global_aStatic, global_bStatic, global_lFinal, global_dStatic, global_tStatic;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MSG komunikat;
	// Tworzenie okna wraz ze wszystkimi parametrami
	LPSTR NazwaKlasy = "Klasa Okienka";
	WNDCLASSEX okno;

	okno.cbSize = sizeof(WNDCLASSEX);
	okno.style = 0;
	okno.lpfnWndProc = WndProc;
	okno.cbClsExtra = 0;
	okno.cbWndExtra = 0;
	okno.hInstance = hInstance;
	okno.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	okno.hCursor = LoadCursor(NULL, IDC_ARROW);
	okno.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	okno.lpszMenuName = NULL;
	okno.lpszClassName = NazwaKlasy;
	okno.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Rejestracja okna
	if (RegisterClassEx(&okno)) {
		// Tworzenie okna (do narysowania)
		HWND window = CreateWindowEx(WS_EX_WINDOWEDGE, NazwaKlasy, "Ca³kowanie Metod¹ Trapezów", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 350, NULL, NULL, hInstance, NULL);
		global_lButton = CreateWindowEx(0, "Button", "Licz", WS_CHILD | WS_VISIBLE, 10, 270, 60, 30, window, NULL, hInstance, NULL);
		global_p1Button = CreateWindowEx(0, "Button", "+", WS_CHILD | WS_VISIBLE, 340, 170, 30, 30, window, NULL, hInstance, NULL);
		global_p2Button = CreateWindowEx(0, "Button", "+", WS_CHILD | WS_VISIBLE, 340, 210, 30, 30, window, NULL, hInstance, NULL);
		global_m1Button = CreateWindowEx(0, "Button", "-", WS_CHILD | WS_VISIBLE, 380, 170, 30, 30, window, NULL, hInstance, NULL);
		global_m2Button = CreateWindowEx(0, "Button", "-", WS_CHILD | WS_VISIBLE, 380, 210, 30, 30, window, NULL, hInstance, NULL);
		global_asmButton = CreateWindowEx(0, "BUTTON", "Asm Dll", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 500, 170, 80, 30, window, NULL, hInstance, NULL);
		global_cppButton = CreateWindowEx(0, "BUTTON", "C++ Dll", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 500, 210, 80, 30, window, NULL, hInstance, NULL);
		global_lFinal = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 270, 300, 30, window, NULL, hInstance, NULL);
		global_Time = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 400, 270, 100, 30, window, NULL, hInstance, NULL);
		global_lTime = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 510, 270, 100, 30, window, NULL, hInstance, NULL);
		global_wTextBox = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 600, 30, window, NULL, hInstance, NULL);
		global_wStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 10, 600, 30, window, NULL, hInstance, NULL);
		global_aText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 90, 100, 30, window, NULL, hInstance, NULL);
		global_bText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 130, 100, 30, window, NULL, hInstance, NULL);
		global_dText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 170, 50, 30, window, NULL, hInstance, NULL);
		global_tText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 210, 50, 30, window, NULL, hInstance, NULL);
		global_aStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 90, 260, 30, window, NULL, hInstance, NULL);
		global_bStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 130, 260, 30, window, NULL, hInstance, NULL);
		global_dStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 170, 260, 30, window, NULL, hInstance, NULL);
		global_tStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 210, 260, 30, window, NULL, hInstance, NULL);
		SetWindowText(global_wTextBox, "F:\\!Studia!\\Kierunek_Informatyka\\JA\\!Workspace\\CMT\\x64\\Debug\\wielomian.txt");
		SetWindowText(global_aText, "-500");
		SetWindowText(global_Time, "Czas trwania");
		SetWindowText(global_bText, "500");
		SetWindowText(global_dText, "10");
		SetWindowText(global_tText, "64");
		SetWindowText(global_tStatic, "Szybkoœæ dzia³ania (1-64 co 1)");
		SetWindowText(global_wStatic, "Scie¿ka dostêpu do pliku z wielomianem (maksymalny stopieñ wielominu : 99)");
		SetWindowText(global_aStatic, "Dolna granica przedzia³u ca³kowania");
		SetWindowText(global_bStatic, "Górna granica przedzia³u ca³kowania");
		SetWindowText(global_dStatic, "Dok³adnoœæ ca³kowania (10-10000 co 1)");
		Button_SetCheck(global_cppButton, BST_CHECKED);
		if (window) {
			// Wyœwietlanie okna
			ShowWindow(window, nCmdShow);
			// Odœwie¿anie okna
			UpdateWindow(window);

			while (GetMessage(&komunikat, NULL, 0, 0)) {
				//Pêtla zdarzeñ
				TranslateMessage(&komunikat);
				DispatchMessage(&komunikat);
			}
		}
	}

	return komunikat.wParam;
}

// Funkcja odpowiedzialna za obs³ugê komunikatów
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	DWORD dlugosc;
	LPSTR Bufor, a, b, dok, thr;

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		if ((HWND)lParam == global_lButton) {
			dlugosc = GetWindowTextLength(global_wTextBox);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_wTextBox, Bufor, dlugosc + 1);
			dlugosc = GetWindowTextLength(global_aText);
			a = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_aText, a, dlugosc + 1);
			dlugosc = GetWindowTextLength(global_bText);
			b = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_bText, b, dlugosc + 1);
			dlugosc = GetWindowTextLength(global_dText);
			dok = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_dText, dok, dlugosc + 1);
			dlugosc = GetWindowTextLength(global_tText);
			thr = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_tText, thr, dlugosc + 1);
			std::string s;
			std::string time;
			if (Button_GetCheck(global_asmButton) == BST_CHECKED) {
				s = rots(Bufor, a, b, dok, "AsmDLL", thr, &time);
			}
			else {
				s =	rots(Bufor, a, b, dok, "CppDLL", thr, &time);
			}
			SetWindowText(global_lFinal, &s[0]);
			SetWindowText(global_lTime, &time[0]);
			GlobalFree(Bufor);
			break;

		}
		else if ((HWND)lParam == global_p1Button) {
			dlugosc = GetWindowTextLength(global_dText);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_dText, Bufor, dlugosc + 1);

			int i = atoi(Bufor);
			i+=200;
			if (i > 10000)
				SetWindowText(global_dText, "10000");
			else {
				std::string s = std::to_string(i);
				Bufor = (LPSTR)s.c_str();

				SetWindowText(global_dText, Bufor);
			}
		}
		else if ((HWND)lParam == global_p2Button) {
			dlugosc = GetWindowTextLength(global_tText);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_tText, Bufor, dlugosc + 1);

			int i = atoi(Bufor);
			i++;
			if (i > 64)
				SetWindowText(global_tText, "64");
			else {
				std::string s = std::to_string(i);
				Bufor = (LPSTR)s.c_str();

				SetWindowText(global_tText, Bufor);
			}
		}
		else if ((HWND)lParam == global_m1Button) {
			dlugosc = GetWindowTextLength(global_dText);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_dText, Bufor, dlugosc + 1);

			int i = atoi(Bufor);
			i--;
			if (i < 10)
				SetWindowText(global_dText, "10");
			else {
				std::string s = std::to_string(i);
				Bufor = (LPSTR)s.c_str();

				SetWindowText(global_dText, Bufor);
			}
		}
		else if ((HWND)lParam == global_m2Button) {
			dlugosc = GetWindowTextLength(global_tText);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(global_tText, Bufor, dlugosc + 1);

			int i = atoi(Bufor);
			i--;
			if (i < 1) 
				SetWindowText(global_tText, "1");
			else {
				std::string s = std::to_string(i);
				Bufor = (LPSTR)s.c_str();

				SetWindowText(global_tText, Bufor);
			}
		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}	

	return 0;
}

