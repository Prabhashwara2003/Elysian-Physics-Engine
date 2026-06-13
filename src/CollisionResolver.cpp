#include "CollisionResolver.h"
#include <cmath>

namespace elysian {

	void CollisionResolver::Resolve(CollisionInfo& info) noexcept {
		Rigidbody& rbA = *info.rigidbodyA;
		Rigidbody& rbB = *info.rigidbodyB;

		vec2 rA = info.collisionPoint - rbA.transform.position;
		vec2 rB = info.collisionPoint - rbB.transform.position;

		vec2 vA = rbA.velocity + Cross(rbA.angularVelocity, rA);
		vec2 vB = rbB.velocity + Cross(rbB.angularVelocity, rB);
		vec2 relativeVelocity = vB - vA;

		float velocityAlongNormal = Dot(relativeVelocity, info.normal);

		const float restitutionThreshold = 1.0f;
		float restitution = (std::abs(velocityAlongNormal) < restitutionThreshold)
			? 0.0f
			: fminf(rbA.bounciness, rbB.bounciness);

		if (velocityAlongNormal <= 0) {
			float moiA = (info.colliderA->momentOfInertia > 0.0f) ? info.colliderA->momentOfInertia : 1.0f;
			float moiB = (info.colliderB->momentOfInertia > 0.0f) ? info.colliderB->momentOfInertia : 1.0f;

			float rACrossN = rA.x * info.normal.y - rA.y * info.normal.x;
			float rBCrossN = rB.x * info.normal.y - rB.y * info.normal.x;

			float invMassSum = rbA.inverseMass + rbB.inverseMass;
			float angularTermA = (rbA.inverseMass > 0.0f) ? (rACrossN * rACrossN) / moiA : 0.0f;
			float angularTermB = (rbB.inverseMass > 0.0f) ? (rBCrossN * rBCrossN) / moiB : 0.0f;

			float impulseScalar = -(1.0f + restitution) * velocityAlongNormal;
			impulseScalar /= (invMassSum + angularTermA + angularTermB);
			vec2 normalImpulse = info.normal * impulseScalar;

			vec2 tangentialVelocity = relativeVelocity - (info.normal * velocityAlongNormal);
			float tangentSpeed = Magnitude(tangentialVelocity);
			vec2 frictionImpulse = vec2(0, 0);

			if (tangentSpeed > 0.001f) {
				vec2 tangent = tangentialVelocity * (1.0f / tangentSpeed);

				float rACrossT = rA.x * tangent.y - rA.y * tangent.x;
				float rBCrossT = rB.x * tangent.y - rB.y * tangent.x;
				float angularTermAT = (rACrossT * rACrossT) / moiA;
				float angularTermBT = (rBCrossT * rBCrossT) / moiB;

				float frictionCoeff = std::sqrt(rbA.friction * rbB.friction);
				float frictionImpulseScalar = -tangentSpeed / (invMassSum + angularTermAT + angularTermBT);
				float maxFriction = std::abs(impulseScalar) * frictionCoeff;
				frictionImpulseScalar = fmaxf(-maxFriction, fminf(frictionImpulseScalar, maxFriction));
				frictionImpulse = tangent * frictionImpulseScalar;
			}

			vec2 totalImpulse = normalImpulse + frictionImpulse;
			rbA.ApplyImpulseAtPosition(totalImpulse * -1.0f, info.collisionPoint, moiA);
			rbB.ApplyImpulseAtPosition(totalImpulse, info.collisionPoint, moiB);
		}

		const float percent = 0.2f;
		const float slop = 0.01f;
		float invMassSum = rbA.inverseMass + rbB.inverseMass;
		if (invMassSum > 0.0f) {
			float correctionMag = fmaxf(info.penetrationDepth - slop, 0.0f) / invMassSum * percent;
			vec2 correction = info.normal * correctionMag;
			rbA.transform.position = rbA.transform.position - correction * rbA.inverseMass;
			rbB.transform.position = rbB.transform.position + correction * rbB.inverseMass;
		}
	}

} // namespace elysian
