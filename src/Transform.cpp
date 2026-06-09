#include "Transform.h"

namespace elysian {

Transform::Transform(vec2 position, float rotation, vec2 scale)
	:position(position),rotation(rotation),scale(scale)
{}

void Transform::Translate(vec2 delta) {
	position = position + delta;
}

void Transform::Rotate(float angle) {
	rotation += angle;
}

} // namespace elysian