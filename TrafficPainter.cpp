#include "framework.h"
#include "TrafficPainter.h"

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type) {
    HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
    HGDIOBJ hOrg = SelectObject(*hdcP, hBrushBlack);
    RoundRect(*hdcP, startX, startY, startX + width, startY + (3 * width), width / 5, width / 5);
    SelectObject(*hdcP, hOrg);
    DeleteObject(hBrushBlack);

    HBRUSH hBrushGrey = CreateSolidBrush(RGB(160, 160, 160));
    switch (type) {
        case TrafficLightType::Red:
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

        case TrafficLightType::Green:
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

        case TrafficLightType::RedYellow:
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

        case TrafficLightType::Yellow:
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

void paintRoads(HDC* hdcP, int centreX, int centreY, int roadWidth, int wRight, int wBottom) {
    int hWidth = roadWidth / 2;

    // Draw roads
    HBRUSH hBrushRoad = CreateSolidBrush(RGB(100, 100, 100));
    HGDIOBJ hOrg = SelectObject(*hdcP, hBrushRoad);
    Rectangle(*hdcP, centreX - hWidth, 0, centreX + hWidth, wBottom);
    Rectangle(*hdcP, 0, centreY - hWidth, wRight, centreY + hWidth);
    SelectObject(*hdcP, hOrg);
    DeleteObject(hBrushRoad);

    // Draw road lines
    HBRUSH hBrushLines = CreateSolidBrush(RGB(255, 255, 255));
    hOrg = SelectObject(*hdcP, hBrushLines);
    int lineWidth = roadWidth / 20;
    int lineLength = hWidth;
    for (int y = 0; y <= wBottom - lineLength; y += lineLength * 1.5) {
        Rectangle(*hdcP, centreX - lineWidth, y, centreX + lineWidth, y + lineLength);
    }
    for (int x = 0; x <= wRight - lineLength; x += lineLength * 1.5) {
        Rectangle(*hdcP, x, centreY - lineWidth, x + lineLength, centreY + lineWidth);
    }
    SelectObject(*hdcP, hBrushLines);

    // Draw intersection
    HBRUSH hBrushIntersect = CreateSolidBrush(RGB(120, 120, 120));
    hOrg = SelectObject(*hdcP, hBrushIntersect);
    Rectangle(*hdcP, centreX - hWidth, centreY - hWidth, centreX + hWidth, centreY + hWidth);
}

void paintCars(HDC* hdcP, std::vector<CAR*>* carsVert, std::vector<CAR*>* carsHor, int centreX, int centreY, int wRight, int wBottom, int roadWidth) {
    int lineWidth = roadWidth / 20;
    int offset = lineWidth / 2;
    int laneWidth = roadWidth / 2 - offset;
    int hWidth = laneWidth / 2;
    HGDIOBJ hOrg;

    // Drawing vertical driving cars
    for (auto car : *carsVert) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        hOrg = SelectObject(*hdcP, hBrush);
        int x = 0;// car->x;
        RoundRect(*hdcP, x, centreY - hWidth, x + laneWidth, centreY + hWidth, laneWidth / 3, laneWidth / 3);
        SelectObject(*hdcP, hOrg);
        DeleteObject(hBrush);
    }

    // Drawing horisontal driving cars
    for (auto car : *carsHor) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        hOrg = SelectObject(*hdcP, hBrush);
        int y = 0;//car->y;
        RoundRect(*hdcP, centreX - hWidth, y, centreX + hWidth, y + laneWidth, laneWidth / 3, laneWidth / 3);
        SelectObject(*hdcP, hOrg);
        DeleteObject(hBrush);
    }
}