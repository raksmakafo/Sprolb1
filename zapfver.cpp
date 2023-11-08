#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
HWND hWnd;
HMENU hMenu;
HICON hIcon;
HCURSOR hCursor;
LPCTSTR studentName = TEXT("Ilyin,Malakhov,Riznyk,Yelysey");
LPCTSTR szTitle = TEXT("First Program");

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
void HandleMenuCommand(HWND hWnd, WPARAM wParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define IDC_MENUCURSOR                     101
#define IDC_MENUICON                       101

enum MenuIDs {
    MENUCURSOR,
    MENUICON,
    MENUBACKGROUND,
    MENUSIZE,
    MENUPROGRAM
};
// ������� ��� ��������� ���������� ���� "��� ��������"
void ShowAboutDialog(HWND hWnd) {
    int result = MessageBox(hWnd, TEXT("��������� ���������� ��� ��������"), TEXT("��� ��������"), MB_OKCANCEL | MB_ICONINFORMATION);

    if (result == IDOK) {
        // ³������ ����������� �� ������ "��" ��� "�������"
        MessageBox(hWnd, TEXT("�� �������� ��������: Ilyin,Malakhov,Riznyk,Yelysey\n�����: ʲ�ʲ-22-3"), TEXT("���������"), MB_OK | MB_ICONINFORMATION);
    }
}

INT_PTR CALLBACK CursorDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        // ����������� ���������� ����
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            // ������� ���������� ������ "OK"
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }

    return (INT_PTR)FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    wcex.hCursor = LoadCursor(NULL, IDC_HAND);
    wcex.hbrBackground = CreateSolidBrush(RGB(64, 64, 64)); // �����-���� ���� ����
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = studentName;
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;
    hWnd = CreateWindow(studentName, szTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 700, 380, 550, 350, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, MENUCURSOR, TEXT("������ ������"));
    AppendMenu(hSubMenu, MF_STRING, MENUICON, TEXT("������ ������"));
    AppendMenu(hSubMenu, MF_STRING, MENUBACKGROUND, TEXT("������ ���"));
    AppendMenu(hSubMenu, MF_STRING, MENUSIZE, TEXT("������ �����"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, TEXT("������ ������"));

    AppendMenu(hMenu, MF_STRING, MENUPROGRAM, TEXT("��� ��������"));
    SetMenu(hWnd, hMenu);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: //����������� ����������� ��������� ��������� �����
        return TRUE;
        //���� ������� ���������� �������� �� ���� ���������� ����
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
            return TRUE;
        }
        break;

    }
    return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;

    switch (message) {
    case WM_CREATE:
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == MENUPROGRAM) {
            ShowAboutDialog(hWnd);

        }
        else {
            HandleMenuCommand(hWnd, wParam);
        }
        break;

    case WM_CLOSE: // ������� �������� ����
        if (MessageBox(hWnd, TEXT("�� �������?"), TEXT("ϳ����������� ��������"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
            DestroyWindow(hWnd);
        }
        break;

    case WM_LBUTTONDBLCLK:
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        RECT rect;
        GetClientRect(hWnd, &rect);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void HandleMenuCommand(HWND hWnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case MENUCURSOR:
        hCursor = LoadCursorFromFile(L"cursor1.cur");
        if (hCursor) {
            SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
        }
        break;

    case MENUICON:
    {
     
        hIcon = LoadCursorFromFile(L"icon1.ico");
        if (hIcon) {
            SetClassLongPtr(hWnd, GCLP_HICON, (LONG_PTR)hIcon);
        }
        break;
    }
    break;

    case MENUBACKGROUND:
    {
       HBITMAP hBitmap1 = (HBITMAP)LoadImage(hInst, L"bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        if (hBitmap1) {
            HBRUSH hBrush = CreatePatternBrush(hBitmap1);
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);

           
            SetLayeredWindowAttributes(hWnd, RGB(100, 150, 255), 0, LWA_COLORKEY);

          
            RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
        

        }
    }
    break;

    case MENUSIZE:
         // ������ ����� ���� �� 800x600 ������
    SetWindowPos(hWnd, NULL, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER);
    break;

    default:
        break;
    }
}