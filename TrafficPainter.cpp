#include "framework.h"
#include "TrafficPainter.h"
#include "Car.h"

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type) {
    // Create brushes
    HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hBrushGrey = CreateSolidBrush(RGB(160, 160, 160));
    HBRUSH hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));

    HGDIOBJ hOrg = SelectObject(*hdcP, hBrushBlack);
    RoundRect(*hdcP, startX, startY, startX + width, startY + (3 * width), width / 5, width / 5);

    switch (type) {
        case TrafficLightType::Red:
        {
            hOrg = SelectObject(*hdcP, hBrushRed);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);
            
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

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

            hOrg = SelectObject(*hdcP, hBrushGreen);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            break;
        }

        case TrafficLightType::RedYellow:
        {
            hOrg = SelectObject(*hdcP, hBrushRed);
            int lightWidth = width * 0.9;
            int left = startX + width - lightWidth;
            int top = startY + width - lightWidth;
            int right = startX + lightWidth;
            int bottom = startY + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            hOrg = SelectObject(*hdcP, hBrushYellow);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

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

            hOrg = SelectObject(*hdcP, hBrushYellow);
            top = startY + (2 * width) - lightWidth;
            bottom = startY + width + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            hOrg = SelectObject(*hdcP, hBrushGrey);
            top = startY + (3 * width) - lightWidth;
            bottom = startY + (2 * width) + lightWidth;
            Ellipse(*hdcP, left, top, right, bottom);

            break;
        }

        default: break;
    }

    // Delete brushes
    SelectObject(*hdcP, hOrg);
    DeleteObject(hBrushGrey);
    DeleteObject(hBrushBlack);
    DeleteObject(hBrushRed);
    DeleteObject(hBrushGreen);
    DeleteObject(hBrushYellow);
}

void paintRoads(HDC* hdcP, int centreX, int centreY, int roadWidth, int wRight, int wBottom) {
    int hWidth = roadWidth / 2;

    // Create brushes
    HBRUSH hBrushRoad = CreateSolidBrush(RGB(100, 100, 100));
    HBRUSH hBrushLines = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH hBrushIntersect = CreateSolidBrush(RGB(120, 120, 120));

    // Draw roads
    HGDIOBJ hOrg = SelectObject(*hdcP, hBrushRoad);
    Rectangle(*hdcP, centreX - hWidth, 0, centreX + hWidth, wBottom);
    Rectangle(*hdcP, 0, centreY - hWidth, wRight, centreY + hWidth);

    // Draw road lines
    hOrg = SelectObject(*hdcP, hBrushLines);
    int hLineWidth = roadWidth / 20;
    int lineLength = hWidth;
    for (int y = 0; y <= wBottom - lineLength; y += lineLength * 1.5) {
        Rectangle(*hdcP, centreX - hLineWidth, y, centreX + hLineWidth, y + lineLength);
    }
    for (int x = 0; x <= wRight - lineLength; x += lineLength * 1.5) {
        Rectangle(*hdcP, x, centreY - hLineWidth, x + lineLength, centreY + hLineWidth);
    }

    // Draw intersection
    hOrg = SelectObject(*hdcP, hBrushIntersect);
    Rectangle(*hdcP, centreX - hWidth, centreY - hWidth, centreX + hWidth, centreY + hWidth);

    // Delete brushes
    SelectObject(*hdcP, hOrg);
    DeleteObject(hBrushRoad);
    DeleteObject(hBrushLines);
    DeleteObject(hBrushIntersect);
}

void paintCars(HDC* hdcP, std::vector<Car*> carsVert, std::vector<Car*> carsHor, int centreX, int centreY, int wRight, int wBottom, int roadWidth) {
    int hLineWidth = roadWidth / 20;
    int laneWidth = roadWidth / 2 - 2*hLineWidth;
    int carWidth = laneWidth * 0.9;
    int margin = (laneWidth - carWidth) / 2;
    int baseX = centreX + hLineWidth + margin;
    int baseY = centreY + hLineWidth + margin;
    HGDIOBJ hOrg;

    // Drawing horisontal driving cars
    for (auto car : carsHor) {
        HBRUSH hBrush = CreateSolidBrush(RGB(car->r, car->g, car->b));
        hOrg = SelectObject(*hdcP, hBrush);
        int x = car->x;
        RoundRect(*hdcP, x, baseY, x + laneWidth, baseY + laneWidth, laneWidth / 3, laneWidth / 3);
        SelectObject(*hdcP, hOrg);
        DeleteObject(hBrush);
    }

    // Drawing vertical driving cars
    for (auto car : carsVert) {
        HBRUSH hBrush = CreateSolidBrush(RGB(car->r, car->g, car->b));
        hOrg = SelectObject(*hdcP, hBrush);
        int y = car->y;
        RoundRect(*hdcP, baseX, y, baseX + laneWidth, y + laneWidth, laneWidth / 3, laneWidth / 3);
        SelectObject(*hdcP, hOrg);
        DeleteObject(hBrush);
    }
}