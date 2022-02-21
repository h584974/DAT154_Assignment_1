#pragma once

#include <vector>
#include "Car.h"

enum class TrafficLightType { Red, Green, RedYellow, Yellow };

void paintCityBlocks(HDC* dcP, HINSTANCE hInst, int windowWidth, int windowHeight, int roadWidth);

void paintWhiteBackground(HDC* dcP, int windowWidth, int windowHeight);

void paintTrafficLight(HDC* dcP, int startX, int startY, int width, TrafficLightType type);

void paintRoads(HDC* dcP, int centreX, int centreY, int roadWidth, int wRight, int wBottom);

void paintCars(HDC* dcP, std::vector<Car*> carsVert, std::vector<Car*> carsHor, int centreX, int centreY, int wRight, int wBottom, int roadWidth);