#pragma once
#include "vector"
#include "Ball.h"
#include "Rectangle.h"


class Collision
{
public:
	void checkCollision(std::vector<Ball*>& balls);
	void checkBallRect(std::vector<Ball*>& balls, std::vector<Rectangle*>& rectangles);
	void checkRectRect(std::vector<Rectangle*>& rectangles);
};

