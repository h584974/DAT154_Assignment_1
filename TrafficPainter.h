#pragma once

#include <vector>
#include "Car.h"

enum class TrafficLightType { Red, Green, RedYellow, Yellow };

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type);

void paintRoads(HDC* hdcP, int centreX, int centreY, int roadWidth, int wRight, int wBottom);

void paintCars(HDC* hdcP, std::vector<Car*> carsVert, std::vector<Car*> carsHor, int centreX, int centreY, int wRight, int wBottom, int roadWidth);