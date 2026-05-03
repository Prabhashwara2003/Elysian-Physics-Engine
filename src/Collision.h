#pragma once
#include "vector"
#include "Ball.h"


class Collision
{
public:
	void addCollision(std::vector<Ball*>& balls);
	void checkCollision(std::vector<Ball*>& balls);
};

