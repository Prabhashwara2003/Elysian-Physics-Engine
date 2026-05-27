#include "Circle.h"
#include "matrices.h"

Circle::Circle(vec2 origin, float radius, float angle)
	:origin(origin),radius(radius),angle(angle)
{
	Translation = createTranslation(origin);
	Rotation = createRotation(angle);
	Scale = createScale({ 2 * radius,2 * radius });

	Transform = Translation * Rotation * Scale;

}

void Circle::update() {

	Transform = Translation * Rotation * Scale;
	
}

