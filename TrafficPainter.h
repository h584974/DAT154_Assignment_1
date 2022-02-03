#pragma once

enum class TrafficLightType { Red, Green, RedYellow, Yellow };

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type);

int paintRoads(HDC* hdcP, int centreX, int centreY, int width, int windowRight, int windowBottom);