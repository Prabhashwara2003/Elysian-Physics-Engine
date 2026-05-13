#pragma once
#include "vector"
#include "Ball.h"
#include "Rectangle.h"


class Collision
{
public:
	void checkCollision(std::vector<Ball*>& balls);
	void checkBallRect(Ball* ball,Rectangle* rect);
};

