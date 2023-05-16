#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <fstream>
#include "Circle.h"

using namespace std;

HMENU hMenu;

void add_menu(HWND); //prototype


//shape color menu
int shape_color() {
    int c, color;
    cout << "choose the color of the shape" << endl;
    cout << "0 --> black" << endl;
    cout << "1 --> white" << endl;
    cout << "2 --> blue" << endl;
    cout << "3 --> red" << endl;
    cout << "4 --> yellow" << endl;
    cout << "5 --> green" << endl;
    cout << "6 --> purple" << endl;
    cout << "7 --> orange" << endl;
    cin >> c;
    switch (c) {
        case 0:
            color = RGB(0, 0, 0);
            break;
        case 1:
            color = RGB(255, 255, 255);
            break;
        case 2:
            color = RGB(18, 82, 255);
            break;
        case 3:
            color = RGB(255, 0, 0);
            break;
        case 4:
            color = RGB(255, 255, 0);
            break;
        case 5:
            color = RGB(40, 128, 34);
            break;
        case 6:
            color = RGB(160, 32, 240);
            break;
        case 7:
            color = RGB(255, 165, 0);
            break;
        default:
            color = RGB(0, 0, 0);
            break;
    }
    return color;
}


POINT p[4];
int cnt = 0;
COLORREF c = shape_color();




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

void save(HDC hdc) {
    ofstream out("file.txt");
    for (int i = 0; i < 529; ++i) {
        for (int j = 0; j < 336; ++j) {
            COLORREF col = GetPixel(hdc, i, j);
            if (col != 0x00FFFFFF) {
                out << i << ' ' << j << ' ' << col << ' ';
            }
        }

    }
    cout << "DONE" << endl;
    out.close();

}

void clear(HDC hdc) {
    for (int i = 0; i < 529; ++i) {
        for (int j = 0; j < 336; ++j) {
            COLORREF col = GetPixel(hdc, i, j);
            if (col != 0x00FFFFFF) {
                SetPixel(hdc, i, j, 0x00FFFFFF);
            }
        }
    }
    cout << "DONE" << endl;
}


void load(HDC hdc) {
    ifstream input("file.txt");
    int x, y;
    COLORREF col;
    while (input >> x) {
        input >> y;
        input >> col;
        SetPixel(hdc, x, y, col);
    }
    input.close();
}

int x1;
int y11;
int x2;
int y2;
int x3;
int y3;
int x4;
int y4;
int shape_no = 1;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE://create menu on top of screen
            add_menu(hwnd);
            break;
        case WM_COMMAND:// function of every button in menu
            switch (wParam) {
                case 1://shapes button
                    break;
                case 2://clear button
                    clear(hdc);
                    break;
                case 3:// save button
                    save(hdc);
                    break;
                case 4:// load button
                    load(hdc);
                    break;
                case 5://Exit button
                    exit(0);
                    break;
                case 6:
                    shape_no = 6;
                    break;
                case 7:
                    shape_no = 7;
                    break;
                case 8:
                    shape_no = 8;
                    break;

            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            switch (shape_no) {
                case 6:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt == 1) {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        int r = sqrt((y11 - y2) * (y11 - y2) + (x1 - x2) * (x1 - x2));
                        drawCircle_quarterlinefill(hdc, x1, y11, r, c);
                        cnt = 0;
                    }
                    break;
                case 7:
                    if (cnt % 2 == 0) {
                                        x1 = LOWORD(lParam);
                                        y11 = HIWORD(lParam);
                                        cnt++;
                                    }
                    else if (cnt % 2 == 1) {
                        quadX = LOWORD(lParam);
                        quadY = HIWORD(lParam);
                        int r = sqrt((y11 - quadY) * (y11 - quadY) + (x1 - quadX) * (x1 - quadX));

                        drawCircleWithCircles(hdc, x1, y11, r, c);
                        cnt= 0;
                    }
                    break;
                    //draw line with midpoint
                    case 8:
                        if (cnt == 0) {
                            x1 = LOWORD(lParam);
                            y11 = HIWORD(lParam);
                            cnt++;
                        } else if (cnt == 1) {
                            x2 = LOWORD(lParam);
                            y2 = HIWORD(lParam);
                            drawline(hdc, x1, y11, x2, y2, c);
                            cnt = 0;
                        }
                        break;
                        //draw hermite curve
                        case 11:
                            if (cnt == 3) {
                                p[cnt].x = LOWORD(lParam);
                                p[cnt].y = HIWORD(lParam);
                                hermite(hdc, p, c);
                                cnt = 0;

                            } else {
                                p[cnt].x = LOWORD(lParam);
                                p[cnt].y = HIWORD(lParam);
                                cnt++;
                            }
                            ReleaseDC(hwnd, hdc);
                            break;


            }

            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// the built in menu in window
void add_menu(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hshapemenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hshapemenu, "Shapes");
    AppendMenu(hMenu, MF_STRING, 2, "Clear");
    AppendMenu(hMenu, MF_STRING, 3, "save");
    AppendMenu(hMenu, MF_STRING, 4, "load");
    AppendMenu(hMenu, MF_STRING, 5, "Exit");
    AppendMenu(hshapemenu, MF_STRING, 6, "Circle with quad filled with lines");//
    AppendMenu(hshapemenu, MF_STRING, 7, "Circle with quad filled with circles");//
    AppendMenu(hshapemenu, MF_STRING, 8, "line");//
    AppendMenu(hshapemenu, MF_STRING, 9, "ellipse");
    AppendMenu(hshapemenu, MF_STRING, 10, "cardinal spline");
    AppendMenu(hshapemenu, MF_STRING, 11, "hermit curve");



    SetMenu(hWnd, hMenu);
}