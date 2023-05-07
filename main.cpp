#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

int quadX, quadY;


void draw8points(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc + b, yc + a, color);

    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - b, yc + a, color);

    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc - b, yc - a, color);

    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc - a, color);

}

void drawCircleDDA(HDC hdc, int xc, int yc, int r, COLORREF color) {

    int x = 0;
    int y = r;

    int d = 1 - r;

    while (x < y) {
        if (d <= 0) {
            d += 2 * x + 3;

        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        draw8points(hdc, xc, yc, x, y, color);
    }
}

int base = 0;
int base1;

void draw8pointsWithCircles(HDC hdc, int xc, int yc, int a, int b, int r, COLORREF color) {

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc + b, yc + a, color);

    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - b, yc + a, color);

    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc - b, yc - a, color);

    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc - a, color);

    if (xc + a >= (base + (r / 16))) {
        base = (xc + a) + (r / 16);
        for (int i = yc; i <= yc + b; i += (r / 8)) {
            if (quadX < xc && quadY < yc) {
                drawCircleDDA(hdc, xc - a, i - b, r / 16, RGB(128, 128, 128));
            } else if (quadX > xc && quadY < yc)
                drawCircleDDA(hdc, xc + a, i - b, r / 16, RGB(128, 128, 128));
            else if (quadX > xc && quadY > yc)
                drawCircleDDA(hdc, xc + a, i, r / 16, RGB(128, 128, 128));
            else if (quadX < xc && quadY > yc)
                drawCircleDDA(hdc, xc - a, i, r / 16, RGB(128, 128, 128));

        }
    }
    if (xc + b <= base1 - (r / 16)) {
        base1 = (xc + b) - (r / 16);
        for (int i = yc; i <= yc + a; i += (r / 8)) {
            if (quadX < xc && quadY < yc)
                drawCircleDDA(hdc, xc - b, i - a, r / 16, RGB(128, 128, 128));
            else if (quadX > xc && quadY < yc)
                drawCircleDDA(hdc, xc + b, i - a, r / 16, RGB(128, 128, 128));
            else if (quadX > xc && quadY > yc)
                drawCircleDDA(hdc, xc + b, i, r / 16, RGB(128, 128, 128));
            else if (quadX < xc && quadY > yc)
                drawCircleDDA(hdc, xc - b, i, r / 16, RGB(128, 128, 128));

        }
    }



}

// the quarter that is going to be filled is depending on the place of the second click
void drawCircleDDAWithCircles(HDC hdc, int xc, int yc, int r, COLORREF color) {

    base = xc;
    base1 = xc + r;
    int x = 0;
    int y = r;

    int d = 1 - r;

    while (x < y) {
        if (d <= 0) {
            d += 2 * x + 3;

        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        draw8pointsWithCircles(hdc, xc, yc, x, y, r, color);
    }


}


int x1, y11, x2, y2, cnt = 0;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
//    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
////// change the background color to WHITE
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            if (cnt % 2 == 0) {
                x1 = LOWORD(lParam);
                y11 = HIWORD(lParam);
                cnt++;
            } else if (cnt % 2 == 1) {
                quadX = LOWORD(lParam);
                quadY = HIWORD(lParam);
                int r = sqrt((y11 - quadY) * (y11 - quadY) + (x1 - quadX) * (x1 - quadX));

                drawCircleDDAWithCircles(hdc, x1, y11, r, RGB(128, 128, 128));
                cnt++;
            }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}