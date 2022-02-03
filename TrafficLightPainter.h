#pragma once

enum TrafficLightType { Red, Green, RedYellow, Yellow };

void paintTrafficLight(HDC* hdcP, int startX, int startY, int width, TrafficLightType type);