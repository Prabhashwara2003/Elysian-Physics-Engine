#include "Collision.h"

void Collision::addCollision(std::vector<Ball*>& balls)
{
	float distance = (balls[0]->midpoint.x - balls[1]->midpoint.x) * (balls[0]->midpoint.x - balls[1]->midpoint.x) + (balls[0]->midpoint.y - balls[1]->midpoint.y) * (balls[0]->midpoint.y - balls[1]->midpoint.y);

	if (distance < 50.f * 50.f) {
		balls[0]->velocity = -(balls[0]->velocity);
		balls[1]->velocity = -(balls[1]->velocity);
	}
}

void Collision::checkCollision(std::vector<Ball*>& balls)
{
	for (int i = 0; i < balls.size(); i++)
	{
		for (int j = i + 1 ; j < balls.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			float distance = (balls[i]->midpoint.x - balls[j]->midpoint.x) * (balls[i]->midpoint.x - balls[j]->midpoint.x) + (balls[i]->midpoint.y - balls[j]->midpoint.y) * (balls[i]->midpoint.y - balls[j]->midpoint.y);

			if (distance < 50.f * 50.f) {
				balls[i]->velocity = -(balls[i]->velocity);
				balls[j]->velocity = -(balls[j]->velocity);
			}


		}
	}
}