#include "framework.h"
#include "TrafficLightPainter.h"

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type) {
    HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
    HGDIOBJ hOrg = SelectObject(*hdcP, hBrushBlack);
    Rectangle(*hdcP, startX, startY, startX + width, startY + (3 * width));
    SelectObject(*hdcP, hOrg);
    DeleteObject(hBrushBlack);

    HBRUSH hBrushGrey = CreateSolidBrush(RGB(160, 160, 160));
    switch (type) {
        case Red:
        {
            HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
            hOrg = SelectObject(*hdcP, hBrushRed);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);
            DeleteObject(hBrushRed);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);

            break;
        }

        case Green:
        {
            hOrg = SelectObject(*hdcP, hBrushGrey);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            HBRUSH hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
            hOrg = SelectObject(*hdcP, hBrushGreen);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);
            DeleteObject(hBrushGreen);

            break;
        }

        case RedYellow:
        {
            HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
            hOrg = SelectObject(*hdcP, hBrushRed);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);
            DeleteObject(hBrushRed);

            HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(*hdcP, hBrushYellow);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);
            DeleteObject(hBrushYellow);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);

            break;
        }

        case Yellow:
        {
            hOrg = SelectObject(*hdcP, hBrushGrey);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(*hdcP, hBrushYellow);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);
            DeleteObject(hBrushYellow);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            SelectObject(*hdcP, hOrg);

            break;
        }

        default: break;
    }

    DeleteObject(hBrushGrey);
}