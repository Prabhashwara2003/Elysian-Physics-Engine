#include "Transform.h"

Transform::Transform(vec2 position, float rotation, vec2 scale)
	:position(position),rotation(rotation),scale(scale)
{}

void Transform::Translate(vec2 newPosition) {
	position = position + newPosition;
}

void Transform::Rotate(float angle) {
	rotation += angle;
}