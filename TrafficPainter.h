#pragma once

#include <vector>

enum class TrafficLightType { Red, Green, RedYellow, Yellow };

struct CAR {
	int x;
	int y;
	COLORREF color;
};

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type);

void paintRoads(HDC* hdcP, int centreX, int centreY, int roadWidth, int wRight, int wBottom);

void paintCars(HDC* hdcP, std::vector<CAR*>* carsVert, std::vector<CAR*>* carsHor, int centreX, int centreY, int wRight, int wBottom, int roadWidth);