#include "Transform.h"

namespace elysian {

void Transform::Translate(vec2 delta) noexcept {
	position = position + delta;
}

void Transform::Rotate(float angle) noexcept {
	rotation += angle;
}

} // namespace elysian
