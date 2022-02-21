// Assignment 1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Assignment 1.h"
#include "Painter.h"
#include <vector>
#include <time.h>
#include "Car.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int lightState = 0;
std::vector<Car*> carsVert;
std::vector<Car*> carsHor;
const int MAX_CARS = 100;
float pw = 0.5;
float pn = 0.5;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSIGNMENT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSIGNMENT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_KEYDOWN:
        {
            switch (wParam) {
                case VK_UP:
                {
                    if (pn <= 0.9) pn += 0.1;
                }
                break;

                case VK_DOWN:
                {
                    if (pn >= 0.1) pn -= 0.1;
                }
                break;

                case VK_LEFT:
                {
                    if (pw >= 0.1) pw -= 0.1;
                }
                break;

                case VK_RIGHT:
                {
                    if (pw <= 0.9) pw += 0.1;
                }
                break;

                default: break;
            }
        }
        break;

    case WM_CREATE:
        {
            srand(time(NULL));
            SetTimer(hWnd, 1, 1500, NULL);
            SetTimer(hWnd, 2, 10, NULL);
            SetTimer(hWnd, 3, 1000, NULL);
            // DialogBox(hInst, MAKEINTRESOURCE(CONTROL), hWnd, DlgProc);
        }
        break;

    case WM_TIMER:
        {
            switch (wParam) {
                case 1:
                    {
                        lightState = (lightState + 1) % 4;
                    }
                    break;

                case 2:
                    {
                        RECT rect;
                        if (GetWindowRect(hWnd, &rect)) {

                            int windowWidth = rect.right - rect.left;
                            int windowHeight = rect.bottom - rect.top;
                            int roadWidth = windowWidth / 12;
                            int centreX = windowWidth / 2;
                            int centreY = windowHeight / 2;

                            int i = 0;
                            for (auto car : carsVert) {
                                if (car->y > rect.bottom) carsVert.erase(carsVert.begin() + i);
                                else if (lightState < 2 || car->y > centreY - roadWidth / 2) car->y += 2;
                                i++;
                            }

                            i = 0;
                            for (auto car : carsHor) {
                                if (car->x > rect.right) carsHor.erase(carsHor.begin() + i);
                                else if (lightState > 1 || car->x > centreX - roadWidth / 2) car->x += 2;
                                i++;
                            }

                        }
                    }
                    break;

                case 3:
                    {   
                        RECT rect;
                        if (GetWindowRect(hWnd, &rect)) {

                            int windowWidth = rect.right - rect.left;
                            int windowHeight = rect.bottom - rect.top;
                            int roadWidth = windowWidth / 12;

                            int numCars = carsVert.size() + carsHor.size();
                            if (numCars < MAX_CARS) {
                                int r = (rand() % 2) * 255;
                                int g = (rand() % 2) * 255;
                                int b = (rand() % 2) * 255;
                                Car* car = new Car(-roadWidth / 2, -roadWidth / 2, r, g, b);
                                bool vert = numCars % 2;

                                bool valid = true;
                                if (vert) {
                                    int odds = (int)(1.0 / pn);
                                    if (rand() % odds) break;

                                    for (auto car : carsVert) {
                                        if (car->y < 0) {
                                            valid = false;
                                            break;
                                        }
                                    }
                                    if (valid) carsVert.push_back(car);
                                }
                                else {
                                    int odds = (int)(1.0 / pw);
                                    if (rand() % odds) break;

                                    for (auto car : carsHor) {
                                        if (car->x < 0) {
                                            valid = false;
                                            break;
                                        }
                                    }
                                    if (valid) carsHor.push_back(car);
                                }
                            }

                        }
                    }
                    break;

                default: break;
            }

            InvalidateRect(hWnd, NULL, false);

        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // Drawing done here
            RECT rect;
            if (GetWindowRect(hWnd, &rect)) {
                // Initial setup of values
                int windowWidth = rect.right - rect.left;
                int windowHeight = rect.bottom - rect.top;
                int centreX = windowWidth / 2;
                int centreY = windowHeight / 2;
                int roadWidth = windowWidth / 12;

                // Create virtual device context and associated bitmap
                HDC vdc = CreateCompatibleDC(hdc);
                HBITMAP bmp = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
                SelectObject(vdc, bmp);

                // Draw background
                paintWhiteBackground(&vdc, windowWidth, windowHeight);
                paintCityBlocks(&vdc, hInst, windowWidth, windowHeight, roadWidth);

                // Drawing roads
                paintRoads(&vdc, centreX, centreY, roadWidth, rect.right, rect.bottom);

                // Drawing cars
                paintCars(&vdc, carsVert, carsHor, centreX, centreY, rect.right, rect.bottom, roadWidth);

                // Drawing traffic lights
                TrafficLightType typeHor = lightState == 0 ? TrafficLightType::Red : lightState == 1 ? TrafficLightType::RedYellow : lightState == 2 ? TrafficLightType::Green : TrafficLightType::Yellow;
                TrafficLightType typeVert = lightState == 0 ? TrafficLightType::Green : lightState == 1 ? TrafficLightType::Yellow : lightState == 2 ? TrafficLightType::Red : TrafficLightType::RedYellow;
                paintTrafficLight(&vdc, centreX + roadWidth * 0.75, centreY - roadWidth * 3, roadWidth / 2, typeVert);
                paintTrafficLight(&vdc, centreX + - roadWidth * 3, centreY - roadWidth * 2.2, roadWidth / 2, typeHor);

                // Copy from vdc to hdc
                BitBlt(hdc, 0, 0, windowWidth, windowHeight, vdc, 0, 0, SRCCOPY);

                // Delete objects
                DeleteDC(vdc);
                DeleteObject(bmp);
            }
            
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
