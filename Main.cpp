#include "Header.h"


// ����� ���������� � �������� ��������� �������� 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	hInstGlobal = hInst;

	// ������� ����� ��� �������� ���������� ��������������� ����
	WNDCLASS WelcomeClass = NewWindClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"WelcomeClass", WelcomeProcedure);

	// ����������� ������ 
	if (!RegisterClassW(&WelcomeClass))
		return -1;

	// ��������� ���������� ������
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN) - 45;

	// ���� �������� � ����������� �����������
	hWelcomeWnd = CreateWindow(L"WelcomeClass", L"���� ������������", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, screenWidth, screenHeight, NULL, NULL, NULL, NULL);

	// �������� ���� ������ ����������
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

// ������� ����� ���� ����������
WNDCLASS NewWindClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK WelcomeProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(L"button", L"������� 1", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, (HMENU)1, NULL, NULL);
		CreateWindow(L"button", L"������� 2", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, (HMENU)2, NULL, NULL);
		CreateWindow(L"BUTTON", L"�����", WS_VISIBLE | WS_CHILD, 20, 150, 150, 30, hWnd, (HMENU)3, NULL, NULL);

		break;

	case WM_COMMAND:
		if (LOWORD(wp) == 1 || LOWORD(wp) == 2)
		{
			ShowWindow(hWnd, SW_HIDE);
			if (!hMainWnd)
			{
				CreateMainWindow(hInstGlobal);
			}
			else
			{
				ShowWindow(hMainWnd, SW_SHOW);
			}
		}
		else if (LOWORD(wp) == 3)
		{
			PostQuitMessage(0);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}

// �������� ��������� ����
void CreateMainWindow(HINSTANCE hInst)
{
	// ������� ����� ��� �������� ���������� ��������� ����
	WNDCLASS MainWindClass = NewWindClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainClass", SoftwareMainProcedure);

	// ����������� ������ 
	if (!RegisterClassW(&MainWindClass))
		return;

	// ��������� ���������� ������
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN) - 45;

	// ������������ ���������
	MSG SoftawareMainMessage = { 0 };

	// ���� �������� � ����������� �����������
	hMainWnd = CreateWindow(L"MainClass", L"���� ������������", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, screenWidth, screenHeight, NULL, NULL, NULL, NULL);
	
	

}

// �������� ���� ���������
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		MainWndAddMenus(hWnd);
		MainWndAddWidget(hWnd);
		SetOpenFileParams(hWnd);
		ButtonFlags.reset();
		hBrush = CreateSolidBrush(RGB(220, 220, 220)); // ��� ���� (Gainsboro)
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);

		// �������� ������ ��� ������
		hBrushRed = CreateSolidBrush(RGB(255, 129, 129));
		hBrushGreen = CreateSolidBrush(RGB(129, 255, 129));
		hBrushBlue = CreateSolidBrush(RGB(178, 178, 178));
		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wp) == ButBack)
		{
			SetWindowTextA(hBackButton, "");
			InvalidateRect(hBackButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hBackButton);

			ShowWindow(hMainWnd, SW_HIDE);
			ShowWindow(hWelcomeWnd, SW_SHOW);
		}
		else if (LOWORD(wp) == OnToggleButtonClicked)
		{
			ButtonFlags.flip(6);
			SetWindowTextA(hToggleButton, "");
			InvalidateRect(hToggleButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hToggleButton);
		}
		else if (LOWORD(wp) == ButVerb)
		{
			ButtonFlags.flip(0);
			SetWindowTextA(hVerbButton, "");
			InvalidateRect(hVerbButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hVerbButton);
		}
		else if (LOWORD(wp) == ButAdverb)
		{
			ButtonFlags.flip(1);
			SetWindowTextA(hAdverbButton, "");
			InvalidateRect(hAdverbButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hAdverbButton);
		}
		else if (LOWORD(wp) == ButAdjective)
		{
			ButtonFlags.flip(2);
			SetWindowTextA(hAdjectiveButton, "");
			InvalidateRect(hAdjectiveButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hAdjectiveButton);
		}
		else if (LOWORD(wp) == ButNoun)
		{
			ButtonFlags.flip(3);
			SetWindowTextA(hNounButton, "");
			InvalidateRect(hNounButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hNounButton);
		}
		else if (LOWORD(wp) == ButParticiple)
		{
			ButtonFlags.flip(4);
			SetWindowTextA(hParticipleButton, "");
			InvalidateRect(hParticipleButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hParticipleButton);
		}
		else if (LOWORD(wp) == ButAdverbial)
		{
			ButtonFlags.flip(5);
			SetWindowTextA(hAdverbialButton, "");
			InvalidateRect(hAdverbialButton, NULL, TRUE); // �������������� ������
			UpdateWindow(hAdverbialButton);
		}
		else if (LOWORD(wp) == OnExitSoftware)
		{
			PostQuitMessage(0);
		}
		else if (LOWORD(wp) == ClearRhymes)
		{
			SetWindowTextA(hEditRhymes, "");
			InvalidateRect(hEditRhymes, NULL, TRUE); // �������������� ������
			UpdateWindow(hEditRhymes);
		}
		else if (LOWORD(wp) == ClearText)
		{
			SetWindowTextA(hEditText, "");
			InvalidateRect(hEditText, NULL, TRUE); // �������������� ������
			UpdateWindow(hEditText);
		}
		else if (LOWORD(wp) == EnterWord)
		{
			// ��������
		}
		else if (LOWORD(wp) == OnReadFile)
		{
			if (GetOpenFileNameA(&OFN)) // ��������� ����� GetOpenFileNameA ��� ������
			{
				read_data(filename);
			}
		}
		else if (LOWORD(wp) == OnSaveFile)
		{
			if (GetSaveFileNameA(&OFN))
			{
				save_data(filename);
			}
		}
		else if (LOWORD(wp) == OnInfoClicked)
		{
			MessageBox(hWnd, L"���������� � ��������� � �� �������������:", L"����", MB_OK | MB_ICONINFORMATION);
		}
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wp;
		SetBkColor(hdcStatic, RGB(220, 220, 220)); // ������������� ���� ����
		SetTextColor(hdcStatic, RGB(0, 0, 0)); // ������������� ���� ������
		return (INT_PTR)hBrush;
	}
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lp;
		MakeRoundButton(lpDrawItem);
		break;
	}
	case WM_DESTROY:
		ExitSoftware();
		DeleteObject(hBrushRed);
		DeleteObject(hBrushGreen);
		DeleteObject(hBrushBlue);
		DeleteObject(hBrush);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}

BOOL MakeRoundButton(LPDRAWITEMSTRUCT lpDrawItem)
{
	HDC hdc = lpDrawItem->hDC;  // ���������� ��������� ���������� HDC
	RECT rect = lpDrawItem->rcItem;

	// ������� ����� ����� ���� ���� (����� ������ ������ �������)
	HBRUSH hBgBrush = CreateSolidBrush(RGB(220, 220, 220)); // ���� ���� ����
	FillRect(hdc, &rect, hBgBrush);
	DeleteObject(hBgBrush); // ������� ����� ����� �������������

	// �������� ������ ����� ��� ������
	HBRUSH hBrush;
	BOOL isActive = FALSE;
	const char* buttonText;
	if (lpDrawItem->hwndItem == hBackButton)
	{
		hBrush = hBrushBlue;
		buttonText = "�����";
	}
	else if (lpDrawItem->hwndItem == hToggleButton)
	{
		isActive = ButtonFlags.test(6);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = isActive ? "����� �� ����� �������" : "����� �� ����� ��������";
	}
	else if (lpDrawItem->hwndItem == hVerbButton)
	{
		isActive = ButtonFlags.test(0);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "������";
	}
	else if (lpDrawItem->hwndItem == hAdverbButton)
	{
		isActive = ButtonFlags.test(1);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "�������";
	}
	else if (lpDrawItem->hwndItem == hAdjectiveButton)
	{
		isActive = ButtonFlags.test(2);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "��������������";
	}
	else if (lpDrawItem->hwndItem == hNounButton)
	{
		isActive = ButtonFlags.test(3);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "���������������";
	}
	else if (lpDrawItem->hwndItem == hParticipleButton)
	{
		isActive = ButtonFlags.test(4);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "���������";
	}
	else if (lpDrawItem->hwndItem == hAdverbialButton)
	{
		isActive = ButtonFlags.test(5);
		hBrush = isActive ? hBrushGreen : hBrushRed;
		buttonText = "������������";
	}
	else if (lpDrawItem->hwndItem == hClearRhymes)
	{
		hBrush = hBrushBlue;
		buttonText = "�������� ���� ����";
	}
	else if (lpDrawItem->hwndItem == hClearText)
	{
		hBrush = hBrushBlue;
		buttonText = "�������� ���� ������";
	}

	else
	{
		return FALSE;  // ����������� ������
	}

	HPEN hPen = NULL;
	HPEN hOldPen = NULL;
	HBRUSH hOldBrush = NULL;

	if (lpDrawItem->hwndItem == hBackButton || lpDrawItem->hwndItem == hClearRhymes || lpDrawItem->hwndItem == hClearText)
	{
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 210, 210)); // ����� ���������� ��� ������� ������
	}
	else
	{
		hPen = CreatePen(PS_SOLID, 1, isActive ? RGB(0, 200, 0) : RGB(200, 0, 0));
	}
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		SetTextColor(hdc, RGB(0, 0, 0));
	


	// ���� ������ ������, ������� ������������� � �������� ���� ����
	if (lpDrawItem->itemState & ODS_SELECTED)
	{
		OffsetRect(&rect, 4, 4);
		rect.right -= 4;
		rect.bottom -= 4;
	}

	// ������ ������������ �������������
	RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, 25, 25);

	// ��������� ����������� ��� � ������������� ���� ������
	SetBkMode(hdc, TRANSPARENT);

	// ���������� ����� ������ ������
	DrawTextA(hdc, buttonText, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ������� �������� ������� GDI
	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	return TRUE;
}
void SetEditBackgroundColor(HWND hEdit, COLORREF color) {
	if (hEditBackgroundBrush) {
		DeleteObject(hEditBackgroundBrush); // ������� ������ �����, ���� ��� ����������
	}
	hEditBackgroundBrush = CreateSolidBrush(color); // ������� ����� ����� � ������ ������
	InvalidateRect(hEdit, NULL, TRUE); // �������������� Edit
	UpdateWindow(hEdit); // ��������� ����
}

// ���������� ������ ����������
void ExitSoftware()
{
	IsConnected = false;
	PostQuitMessage(0);
}

// �������� ������� ����
void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();



	// �������� ��������� ���� 
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"����");
	AppendMenu(RootMenu, MF_STRING, OnReadFile, L"������ �����");
	AppendMenu(RootMenu, MF_STRING, OnSaveFile, L"������ �����");
	

	// �������� ������� ����
	AppendMenu(SubMenu, MF_STRING, OnInfoClicked, L"����");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"��������� ������");


	SetMenu(hWnd, RootMenu);
}

// �������� ��������
void MainWndAddWidget(HWND hWnd)
{
	/* �������� ���� 1) ����� ����
	2) ����� 
	3) ����� ���� 
	4) � 5) ������������ �������� ������ ����  ������� � ����
	6) � 7) ������ � ������ ������� � ����
	8) ������� ����
	*/
	// ������ ����������

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN) - 45;

	hClearRhymes = CreateWindowA("BUTTON", "�������� ���� ����", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 195, 20, 150, 40, hWnd, (HMENU)ClearRhymes, NULL, NULL);
	hClearText = CreateWindowA("BUTTON", "��������� ���� ������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 350, 20, 150, 40, hWnd, (HMENU)ClearText, NULL, NULL);
	//hEditWord = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 20, 30, 200, 30, hWnd, (HMENU)EnterWord, NULL, NULL);

	hBackButton = CreateWindowA("BUTTON", "�����", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, screenHeight-150, 154, 34, hWnd, (HMENU)ButBack, NULL, NULL);

	hVerbButton = CreateWindowA("BUTTON", "������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 82, 150, 30, hWnd, (HMENU)ButVerb, NULL, NULL);
	hAdjectiveButton = CreateWindowA("BUTTON", "��������������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 130, 150, 30, hWnd, (HMENU)ButAdjective, NULL, NULL);
	hNounButton = CreateWindowA("BUTTON", "���������������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 180, 150, 30, hWnd, (HMENU)ButNoun, NULL, NULL);
	hAdverbialButton = CreateWindowA("BUTTON", "������������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 230, 150, 30, hWnd, (HMENU)ButAdverbial, NULL, NULL);
	hParticipleButton = CreateWindowA("BUTTON", "���������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 280, 150, 30, hWnd, (HMENU)ButParticiple, NULL, NULL);
	hAdverbButton = CreateWindowA("BUTTON", "�������", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 330, 150, 30, hWnd, (HMENU)ButAdverb, NULL, NULL);
	

	// ������� ������ � ������ BS_OWNERDRAW ��� ��������� ���������
	hToggleButton = CreateWindowA("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 505, 20, 200, 40, hWnd, (HMENU)OnToggleButtonClicked, NULL, NULL);
	
	// ���������� ���� � �� �������
	hOutputStatusText = CreateWindowA("static", "������ ����������: ", WS_VISIBLE | WS_CHILD | ES_CENTER, 20, 5, 150, 30, hWnd, NULL, NULL, NULL);
	hOutputStatus = CreateWindowA("static", "������ ������", WS_VISIBLE | WS_CHILD | ES_CENTER, 20, 30, 150, 30, hWnd, NULL, NULL, NULL);

	
	// ���� �������� ������
	hOutputRhymes = CreateWindowA("static", "��������� �����", WS_VISIBLE | WS_CHILD | ES_CENTER, 195, 80, screenWidth - 215, 15, hWnd, NULL, NULL, NULL);
	hEditRhymes = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 195, 100, screenWidth - 215, screenHeight /2 - 100, hWnd, NULL, NULL, NULL);
	 
	// ���� ������ ������
	hOutputText = CreateWindowA("static", "����� � ���������� �������", WS_VISIBLE | WS_CHILD | ES_CENTER, 195, screenHeight / 2 + 10, screenWidth - 215, 15, hWnd, NULL, NULL, NULL);
	hEditText = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 195, screenHeight / 2 + 30, screenWidth - 215, screenHeight / 2 - 100, hWnd, NULL, NULL, NULL);
}

// ������ � ����
void save_data(LPCSTR path)
{
	HANDLE SAVEfile = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	int SAVElength = GetWindowTextLength(hEditWord) + 1;
	char* data = new char[SAVElength];
	
	SAVElength = GetWindowTextA(hEditWord, data, SAVElength);

	DWORD bytesIterated;

	WriteFile(SAVEfile, data, SAVElength, &bytesIterated, NULL);
	CloseHandle(SAVEfile);
	delete[] data;
}

// ������ �� �����
void read_data(LPCSTR path)
{
	HANDLE READfile = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	DWORD bytesIterated;

	ReadFile(READfile, BufferReceive, TextBufferSize, &bytesIterated, NULL);

	CloseHandle(READfile);
}

// ��������� ��������� ���������� �� �������� ������ ��� ������ � ������
void SetOpenFileParams(HWND hWnd)
{
	ZeroMemory(&OFN, sizeof(OFN));
	OFN.lStructSize = sizeof(OFN);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFile = filename;
	OFN.nMaxFile = sizeof(filename);
	OFN.lpstrFilter = "*.txt";
	OFN.lpstrFileTitle = NULL;
	OFN.nMaxFileTitle = 0;
	OFN.lpstrInitialDir = "D:\\������� ����\\WindowProjectTEst";
	OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

// �������� � ������ ���������
void SetWinStatus(string status)
{
	SetWindowTextA(hOutputStatus, status.c_str());
}